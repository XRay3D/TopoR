#include "xmlserializer.h"
#include "TopoR_PCB_File.h"

#include "Commons.h"
#include "pfr.hpp"
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <set>

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
QString demangle(const std::type_info& ti) {
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
QString demangle(const std::type_info& ti) {
    QString ret{ti.name()};
    return ret;
}
#endif

// #define out qInfo().nospace()

// template <class Stream, class T>
// inline void print(Stream&, T&&);

Xml::Xml(const QString& name) {
    buffer.open(QIODevice::WriteOnly);

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

QDomElement Xml::top() const {
    if(!stack.size()) throw names;
    return stack.top().toElement();
}

bool Xml::push(sl sl_) {
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

void Xml::push(const QDomNode& node, sl sl_) {
    skipPushArray = true;
    if(loging) qWarning() << "F> stack" << stack.size() << names << sl_.function_name();
    stack.push(node);
}

void Xml::pop(sl sl_) {
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

auto Xml::value(sl sl_) -> QString {
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

QString i(int i = {}) {
    static int indent;
    if(i > 0)
        return QString{indent++ * 4, QChar{' '}};
    if(i < 0)
        return QString{--indent * 4, QChar{' '}};
    return QString{indent * 4, QChar{' '}};
}

QTextStream& operator<<(QTextStream& d, std::string_view sv) {
    return d << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

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

template <typename T>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
void read(Xml& xml, T& str) {
    xml.names = {demangle(typeid(T))};
    if(!xml.push()) return;

    // qWarning() << xml.top().nodeName() << xml.top().nodeValue();
    xml.out << demangle(typeid(T)) << " {\n";
    i(+1);
    read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
    xml.out << i(-1) << "}";
    xml.pop();
}

inline void read(Xml& xml, QString& str) {
    if(!xml.push()) return;
    xml.out << '"' << (str = xml.value()) << '"';
    xml.pop();
}

inline void read(Xml& xml, std::string& sv) {
    xml.out << '"' << QByteArray{sv.data(), static_cast<int>(sv.size())} << '"';
}

template <typename T>
    requires std::is_arithmetic_v<T>
void read(Xml& xml, T& value) {
    xml.out << '"' << (value = QVariant{xml.value()}.value<T>()) << '"';
}

namespace TopoR_PCB_Classes {

template <size_t Is, typename T>
void readField(Xml& xml, T& str) {
    auto name = pfr::get_name<Is, T>();
    xml.names = {QString::fromUtf8(name.data(), name.size()), demangle(typeid(pfr::get<Is>(str)))};
    auto it = xml.names.begin();
    xml.out << i() << *it++ << "<" << *it << ">";
    xml.out << " = ";
    read(xml, pfr::get<Is>(str));
    xml.out << '\n';
}

template <typename T, size_t... Is>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
void read(Xml& xml, T& str, std::index_sequence<Is...>) {
    (readField<Is>(xml, str), ...);
}

template <typename Enum>
    requires std::is_enum_v<Enum> // isEnum<Enum>
void read(Xml& xml, Enum& e) {
    e = stringToEnum<Enum>(xml.value().toStdString());
    xml.out << enumToString(e) << "{" << +e << "}";
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
void read(Xml& xml, std::variant<Ts...>& variant) { // FIXME variant
    auto reader = [&xml, &variant]<typename T>(T&& val) {
        if(xml.top().tagName() == demangle(typeid(T))) {
            qInfo() << xml.top().tagName();
            read(xml, val);
            variant = val;
        }
    };
    (reader(Ts{}), ...);
}

template <typename T>
void read(Xml& xml, std::vector<T>& vector) { // FIXME vector
    // loging = true;
    xml.out << "{";
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
    xml.out << "}";
}

template <typename T>
    requires(!std::is_standard_layout_v<T> && !std::is_aggregate_v<T>)
void read(Xml& xml, T& str) {
    xml.out << "<<ERR>>: " << demangle(typeid(T));
}

} // namespace TopoR_PCB_Classes

template <typename T>
// requires(std::is_enum_v<T> == 0 && std::is_standard_layout_v<T> && std::is_trivial_v<T>)
void read(Xml& xml, T& str) {
    xml.out << "ERR: " << demangle(typeid(T));
}

template <>
void Xml::read(TopoR_PCB_Classes::TopoR_PCB_File* val) {
    ::read(*this, *val);
}
