#include "xmlserializer.h"
#include "TopoR_PCB_File.h"

#include "Commons.h"
#include "pfr.hpp"
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <set>

using namespace TopoR_PCB_Classes;

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
template <typename T>
QString typeName(const T& = {}) {
    int status;
    char* const realname = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
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

Xml::Xml(const QString& name) {
    buffer.open(QIODevice::WriteOnly);
    item->itemData[0] = "Name";
    item->itemData[1] = "Value";
    item->itemData[2] = "IsAttr";
    item->itemData[3] = "Type";
    item->itemData[4] = "Line #";
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
    return;
    file.setFileName(file.fileName().replace("/", "/formated_"));
    qWarning() << file.fileName();
    if(!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
        return;
    }
    file.write(doc.toString(4).toUtf8());
}

QDomElement Xml::top() const {
    if(!stack.size()) throw names;
    return stack.top().toElement();
}

auto Xml::value(sl sl_) -> QString {
    QString str;
    auto item = new TreeItem;

    if(isAttr) {
        for(auto&& name: names)
            if(str = top().attribute(name); str.size()) {
                tree->addItem(new TreeItem);
                tree->childItems.back()->itemData[0] = name;
                tree->childItems.back()->itemData[1] = str;
                tree->childItems.back()->itemData[2] = "Attribute";
                tree->childItems.back()->itemData[3] = names.front();
                tree->childItems.back()->itemData[4] = top().lineNumber();
                break;
            }
    } else {
        str = top().text();
        tree->itemData[0] = top().tagName();
        tree->itemData[1] = str;
        tree->itemData[2] = "Element";
        tree->itemData[3] = names.front();
        tree->itemData[4] = top().lineNumber();
    }
    hasValue = str.size();
    return str;
}

void Xml::pop(sl sl_) {

    if(isAttr) return;
    if(skipPop) {
        skipPop = false;
        return;
    }
    if(!stack.size()) throw names;

    stack.pop();
    tree = tree->parent();
}

bool Xml::push(sl sl_) {
    if(skipPushArray || isAttr) {
        skipPushArray = false;
        return true;
    }

    auto getNode = [this](const QDomNode& node) {
        QDomNode retNode;
        for(auto&& name: names) {
            retNode = node.firstChildElement(name);
            if(!retNode.isNull()) break;
        }
        return retNode;
    };
    QDomNode node = getNode(stack.empty() ? doc : stack.top());
    if(node.isNull()) {
        qWarning() << "not found line#" << top().lineNumber() << names; //<< sl_.function_name();
        return hasElem = skipPop = std::ranges::find(names, top().tagName()) != names.end();
    } else {
        stack.push(node);
        tree = tree->addItem(new TreeItem);
        tree->itemData[0] = top().tagName();
        tree->itemData[4] = top().lineNumber();
    }
    return hasElem = !node.isNull();
}

void Xml::push(const QDomNode& node, sl sl_) {
    skipPushArray = true;
    stack.push(node);
    tree = tree->addItem(new TreeItem);
    tree->itemData[0] = top().tagName();
    tree->itemData[4] = top().lineNumber();
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
bool read(Xml& xml, T& str) {
    xml.names = {typeName<T>()};
    if(!xml.push()) return false;
    //  qWarning() << xml.top().nodeName() << xml.top().nodeValue();
    xml.out << typeName<T>() << " {\n";
    i(+1);
    bool ok = read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
    xml.out << i(-1) << "}";
    xml.pop();
    return ok;
}

template <size_t Is, typename T>
bool readField(Xml& xml, T& str) {
    auto name = pfr::get_name<Is, T>();
    xml.names = {
        typeName(typeid(pfr::get<Is>(str))),
        QString::fromUtf8(name.data(), name.size()),
    };
    auto it = xml.names.begin();
    xml.out << i() << *it++ << "<" << *it << ">";
    xml.out << " = ";
    bool ok = read(xml, pfr::get<Is>(str));
    xml.out << '\n';
    return ok;
}

template <typename T, size_t... Is>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
bool read(Xml& xml, T& str, std::index_sequence<Is...>) {
    int ok{};
    ((ok |= readField<Is>(xml, str)), ...);
    return ok;
}

inline bool read(Xml& xml, QString& str) {
    if(!xml.push()) return false;
    xml.out << '"' << (str = xml.value()) << '"';
    xml.pop();
    return xml.hasValue;
}

// inline bool read(Xml& xml, std::string& sv) {
//     xml.out << '"' << QByteArray{sv.data(), static_cast<int>(sv.size())} << '"';
//     return true;
// }

template <typename T>
    requires std::is_arithmetic_v<T>
bool read(Xml& xml, T& value) {
    xml.out << '"' << (value = QVariant{xml.value()}.value<T>()) << '"';
    return xml.hasValue;
}

template <typename Enum>
    requires std::is_enum_v<Enum> // isEnum<Enum>
bool read(Xml& xml, Enum& e) {
    e = stringToEnum<Enum>(xml.value().toStdString());
    xml.out << enumToString(e) << "{" << +e << "}";
    return xml.hasValue;
}

template <typename T>
bool read(Xml& xml, std::optional<T>& optional) {
    T value{};
    xml.names.front() = typeName<T>();
    bool ok = read(xml, value);
    if(ok && xml.hasValue)
        optional = value;
    return ok && xml.hasValue;
}

template <typename T>
bool read(Xml& xml, XmlAttr<T>& optional) {
    xml.isAttr = true;
    xml.names.front() = typeName<T>();
    bool ok = read(xml, optional.value);
    xml.isAttr = false;
    return ok;
}

template <typename... Ts>
bool read(Xml& xml, XmlVariant<Ts...>& variant) { // FIXME variant

    int ctr{};
    auto reader = [&]<typename T>(T&& val) {
        qInfo() << "line#" << xml.top().lineNumber() << xml.top().tagName();
        if(xml.top().tagName() == typeName<T>() && read(xml, val))
            ++ctr, variant = val;
        else if(read(xml, val) /*; xml.hasElem*/)
            ++ctr, variant = val;
    };
    (reader(Ts{}), ...);
    qInfo() << ctr << xml.top().tagName() << xml.top().lineNumber();
    // assert(ctr < 2);
    return ctr;
}

template <typename T>
bool read(Xml& xml, std::vector<T>& vector) { // FIXME vector
    if(!xml.push()) return false;
    xml.out << "{";
    if(auto childNodes = xml.top().childNodes(); childNodes.size()) {
        vector.resize(childNodes.size());
        for(int index{}; index < childNodes.size(); ++index) {
            xml.push(childNodes.at(index));
            read(xml, vector[index]);
        }
    }
    xml.out << "}";
    xml.pop();
    return true;
}

template <typename T>
bool read(Xml& xml, XmlAarray<T>& vector) {
    xml.out << "{";
    if(auto childNodes = xml.top().childNodes(); childNodes.size()) {
        vector.resize(childNodes.size());
        for(int index{}; index < childNodes.size(); ++index) {
            xml.push(childNodes.at(index));
            read(xml, vector[index]);
        }
    }
    xml.out << "}";
    return true;
}

template <typename T>
// requires(std::is_enum_v<T> == 0 && std::is_standard_layout_v<T> && std::is_trivial_v<T>)
bool read(Xml& xml, T& str) {
    qCritical() << __PRETTY_FUNCTION__ << typeName<T>();
    xml.out << "ERR: " << typeName<T>();
    return false;
}

template <>
void Xml::read(TopoR_PCB_Classes::TopoR_PCB_File* val) {
    ::read(*this, *val);
}
