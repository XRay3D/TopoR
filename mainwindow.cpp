#include "mainwindow.h"
#include "TopoR_PCB_File.h"
#include "pfr.hpp"
#include <QDebug>
#include <QDomComment>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <iostream>
#include <set>
#include <source_location>
#include <stack>
#include <string>

using sl = std::source_location;

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
inline QString demangle(const std::type_info& ti) {
    int status;
    char* const realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    QString ret{realname};
    if(auto&& [whole, stl, name] = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if(auto&& [whole, name] = ctre::match<R"(\S+:XmlAttr<.+:(\w+)>)">(realname); whole)
        ret = QString::fromStdString(name.to_string());
    else if(auto&& [whole, stl, name] = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if(auto&& [whole, name] = ctre::match<R"(.+:(\w+))">(realname); whole)
        ret = QString::fromStdString(name.to_string());
    std::free(realname);
    return ret;
}
#else
inline QString demangle(const std::type_info& ti) {
    QString ret{ti.name()};
    return ret;
}
#endif

QString i(int i = {}) {
    static int indent;
    if(i > 0)
        return QString{indent++ * 4, QChar{' '}};
    if(i < 0)
        return QString{--indent * 4, QChar{' '}};
    return QString{indent * 4, QChar{' '}};
}

bool loging{1};
QByteArray data;
QTextStream out{stdout}; //&data, QIODevice::WriteOnly};

// #define out qInfo().nospace()

// template <class Stream, class T>
// inline void print(Stream&, T&&);

QDebug operator<<(QDebug d, std::string_view sv) {
    return d << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

QDebug operator<<(QDebug d, std::set<QString> c) {
    const bool oldSetting = d.autoInsertSpaces();
    d.nospace() << "set" << '(';
    auto it = c.begin(), end = c.end();
    if(it != end) {
        d << *it;
        ++it;
    }
    while(it != end) {
        d << ", " << *it;
        ++it;
    }
    d << ')';
    d.setAutoInsertSpaces(oldSetting);
    return d.maybeSpace();
}

QTextStream& operator<<(QTextStream& d, std::string_view sv) {
    return d << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

struct Xml {
    QDomDocument doc{"mydocument"};

    Xml(const QString& name = "../МАН2_МСИС_V2.1.fst") {
        QFile file{name};
        if(!file.open(QIODevice::ReadOnly)) {
            qWarning() << file.errorString();
            return;
        }

        QString errorMsg{};
        int errorLine{};
        int errorColumn{};
        if(!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
            qWarning() << errorMsg << errorLine << errorColumn;
            return;
        }
        file.close();
    }

    auto top() const {
        if(!stack.size()) throw names;
        return stack.top().toElement();
    }

    bool push(sl sl_ = sl::current()) {
        // if(loging) qWarning() << "1> stack" << stack.size() << names << sl_.function_name();
        if(skipPushArray || isAttr) {
            skipPushArray = false;
            return true;
        }

        auto getNode = [this](const QDomNode& node_) {
            QDomNode node;
            for(auto&& name: names) {
                node = /*isAttr ? node_.attributes().namedItem(name) :*/ node_.firstChildElement(name);
                if(!node.isNull()) break;
            }
            return node;
        };
        QDomNode node = getNode(stack.empty() ? doc : stack.top());
        if(node.isNull()) {
            qCritical() << names << sl_.function_name();
            return skipPop = names.contains(top().tagName());
        } else
            stack.push(node);
        if(loging) qWarning() << "R> stack" << stack.size() << names << sl_.function_name();
        return !node.isNull();
    }

    void push(const QDomNode& node, sl sl_ = sl::current()) {
        skipPushArray = true;
        if(loging) qWarning() << "F> stack" << stack.size() << names << sl_.function_name();
        stack.push(node);
    }

    void pop(sl sl_ = sl::current()) {
        // if(loging) qWarning() << "3> stack" << stack.size() << names << sl_.function_name();
        if(isAttr) return;
        if(skipPop) {
            skipPop = false;
            return;
        }
        if(!stack.size()) throw names;
        stack.pop();
        if(loging) qWarning() << "-< stack" << stack.size() << names << sl_.function_name();
    }

    auto value(sl sl_ = sl::current()) -> QString {
        QString str;
        if(isAttr) {
            for(auto&& name: names)
                if(str = top().attribute(name); str.size())
                    break;
        } else if(top().isElement())
            str = top().text();

        // qWarning() << str << isAttr << sl_.function_name();
        hasValue = str.size();
        return str;
    }

    std::set<QString> names;
    bool isAttr{};
    bool skipPushArray{};
    bool skipPop{};
    bool isptional{};
    bool hasValue{};

    std::stack<QDomNode> stack;
};

void read(Xml& xml, QString& str) {
    if(!xml.push()) return;
    out << '"' << (str = xml.value()) << '"';
    xml.pop();
}

void read(Xml& xml, std::string& sv) {
    out << '"' << QByteArray{sv.data(), static_cast<int>(sv.size())} << '"';
}

template <typename T>
    requires std::is_arithmetic_v<T>
void read(Xml& xml, T& value) {
    out << '"' << (value = QVariant{xml.value()}.value<T>()) << '"';
}

template <typename T>
    requires std::is_base_of_v<std::any, T>
void read(Xml& xml, T& value) {
    out << "std::any";
}

namespace TopoR_PCB_Classes {

template <size_t Is, typename T>
void readField(Xml& xml, T& str) {
    auto name = pfr::get_name<Is, T>();
    xml.names = {QString::fromUtf8(name.data(), name.size()), demangle(typeid(pfr::get<Is>(str)))};
    auto it = xml.names.begin();
    out << i() << *it++ << "<" << *it << ">";
    out << " = ";
    read(xml, pfr::get<Is>(str));
    out << '\n';
}

template <typename T, size_t... Is>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
void read(Xml& xml, T& str, std::index_sequence<Is...>) {
    (readField<Is>(xml, str), ...);
}

template <typename T>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
void read(Xml& xml, T& str) {
    xml.names = {demangle(typeid(T))};
    if(!xml.push()) return;
    // qWarning() << xml.top().nodeName() << xml.top().nodeValue();
    out << demangle(typeid(T)) << " {\n";
    i(+1);
    read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
    out << i(-1) << "}";
    xml.pop();
}

template <typename Enum>
    requires std::is_enum_v<Enum> // isEnum<Enum>
void read(Xml& xml, Enum& e) {
    e = stringToEnum<Enum>(xml.value().toStdString());
    out << enumToString(e) << "{" << +e << "}";
}

template <typename T>
    requires std::is_base_of_v<std::any, T>
void read(Xml& xml, T& value) {
    out << "std::any";
}

template <typename T>
void read(Xml& xml, std::optional<T>& optional) {
    T value{};
    read(xml, value);
    if(xml.hasValue)
        optional = value;
}

template <typename T>
void read(Xml& xml, XmlAttr<T>& optional) {
    xml.isAttr = true;
    // if(!xml.push()) return;
    read(xml, optional.value);
    // xml.pop();
    xml.isAttr = false;
}

template <typename... Ts>
void read(Xml& xml, std::variant<Ts...>& optional) { // FIXME variant
    out << "<<ERR>>: " << __PRETTY_FUNCTION__;
}

template <typename T>
void read(Xml& xml, std::vector<T>& vector) { // FIXME vector
    // loging = true;
    out << "{";
    if(!xml.push()) return;
    std::stack<QDomNode> stack;
    // std::swap(stack, xml.stack);
    auto childNodes = xml.top().childNodes();
    vector.resize(childNodes.size());
    for(int index{}; index < childNodes.size(); ++index) {
        // xml.skipPushArray = true; // skip push in read(struct) because force pushed in this for
        xml.push(childNodes.at(index));
        read(xml, vector[index]);
        // xml.pop(); // skip pop because read(struct) pop it
    }
    // std::swap(stack, xml.stack);
    xml.pop();
    out << "}";
}

template <typename T>
    requires(!std::is_standard_layout_v<T> && !std::is_aggregate_v<T>)
void read(Xml& xml, T& str) {
    out << "<<ERR>>: " << demangle(typeid(T));
}

} // namespace TopoR_PCB_Classes

template <typename T>
// requires(std::is_enum_v<T> == 0 && std::is_standard_layout_v<T> && std::is_trivial_v<T>)
void read(Xml& xml, T& str) {
    out << "ERR: " << demangle(typeid(T));
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent} {

    using T = TopoR_PCB_Classes::TopoR_PCB_File;
    // using T = TopoR_PCB_Classes::PadCircle;
    T t{};

    Xml xml;
    try {
        read(xml, t);
    } catch(const std::set<QString>& names) {
        qCritical() << names;
    } catch(...) {
    }

    if(0) {
        qInfo() << std::is_abstract_v<T> << "is_abstract";
        qInfo() << std::is_aggregate_v<T> << "is_aggregate";
        qInfo() << std::is_arithmetic_v<T> << "is_arithmetic";
        qInfo() << std::is_array_v<T> << "is_array";
        qInfo() << std::is_class_v<T> << "is_class";
        qInfo() << std::is_compound_v<T> << "is_compound";
        qInfo() << std::is_const_v<T> << "is_const";
        qInfo() << std::is_constructible_v<T> << "is_constructible";
        qInfo() << std::is_copy_assignable_v<T> << "is_copy_assignable";
        qInfo() << std::is_copy_constructible_v<T> << "is_copy_constructible";
        qInfo() << std::is_default_constructible_v<T> << "is_default_constructible";
        qInfo() << std::is_destructible_v<T> << "is_destructible";
        qInfo() << std::is_empty_v<T> << "is_empty";
        qInfo() << std::is_enum_v<T> << "is_enum";
        qInfo() << std::is_final_v<T> << "is_final";
        qInfo() << std::is_floating_point_v<T> << "is_floating_point";
        qInfo() << std::is_function_v<T> << "is_function";
        qInfo() << std::is_fundamental_v<T> << "is_fundamental";
        qInfo() << std::is_integral_v<T> << "is_integral";
        qInfo() << std::is_lvalue_reference_v<T> << "is_lvalue_reference";
        qInfo() << std::is_member_function_pointer_v<T> << "is_member_function_pointer";
        qInfo() << std::is_member_object_pointer_v<T> << "is_member_object_pointer";
        qInfo() << std::is_member_pointer_v<T> << "is_member_pointer";
        qInfo() << std::is_move_assignable_v<T> << "is_move_assignable";
        qInfo() << std::is_move_constructible_v<T> << "is_move_constructible";
        qInfo() << std::is_nothrow_constructible_v<T> << "is_nothrow_constructible";
        qInfo() << std::is_nothrow_copy_assignable_v<T> << "is_nothrow_copy_assignable";
        qInfo() << std::is_nothrow_copy_constructible_v<T> << "is_nothrow_copy_constructible";
        qInfo() << std::is_nothrow_default_constructible_v<T> << "is_nothrow_default_constructible";
        qInfo() << std::is_nothrow_destructible_v<T> << "is_nothrow_destructible";
        qInfo() << std::is_nothrow_move_assignable_v<T> << "is_nothrow_move_assignable";
        qInfo() << std::is_nothrow_move_constructible_v<T> << "is_nothrow_move_constructible";
        qInfo() << std::is_null_pointer_v<T> << "is_null_pointer";
        qInfo() << std::is_object_v<T> << "is_object";
        qInfo() << std::is_pointer_v<T> << "is_pointer";
        qInfo() << std::is_polymorphic_v<T> << "is_polymorphic";
        qInfo() << std::is_reference_v<T> << "is_reference";
        qInfo() << std::is_rvalue_reference_v<T> << "is_rvalue_reference";
        qInfo() << std::is_scalar_v<T> << "is_scalar";
        qInfo() << std::is_signed_v<T> << "is_signed";
        qInfo() << std::is_standard_layout_v<T> << "is_standard_layout";
        qInfo() << std::is_trivial_v<T> << "is_trivial";
        qInfo() << std::is_trivially_constructible_v<T> << "is_trivially_constructible";
        qInfo() << std::is_trivially_copy_assignable_v<T> << "is_trivially_copy_assignable";
        qInfo() << std::is_trivially_copy_constructible_v<T> << "is_trivially_copy_constructible";
        qInfo() << std::is_trivially_copyable_v<T> << "is_trivially_copyable";
        qInfo() << std::is_trivially_default_constructible_v<T> << "is_trivially_default_constructible";
        qInfo() << std::is_trivially_destructible_v<T> << "is_trivially_destructible";
        qInfo() << std::is_trivially_move_assignable_v<T> << "is_trivially_move_assignable";
        qInfo() << std::is_trivially_move_constructible_v<T> << "is_trivially_move_constructible";
        qInfo() << std::is_union_v<T> << "is_union";
        qInfo() << std::is_unsigned_v<T> << "is_unsigned";
        qInfo() << std::is_void_v<T> << "is_void";
        qInfo() << std::is_volatile_v<T> << "is_volatile";
    }
    exit(0);
}

MainWindow::~MainWindow() { }
