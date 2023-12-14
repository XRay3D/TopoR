#pragma once

#include "pfr.hpp"
#include "treeitem.h"
#include <set>
#include <source_location>

#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <QRegularExpression>

#include "TopoR_PCB_File.h"
using namespace TopoR;

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
template <typename T>
inline QString typeName(const T& = {}) {
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

inline constexpr auto match1 = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">;
inline constexpr auto match2 = ctre::match<R"(.+:XmlAttr<(?:.+:)?(\w+)>)">;
inline constexpr auto match3 = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">;
inline constexpr auto match4 = ctre::match<R"(.+:(\w+))">;

template <typename T>
inline QString typeName(const T& = {}) {
    QString ret{typeid(T).name()};
    QByteArray realname{ret.toUtf8()};
    if(auto&& [whole, stl, name] = match1(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if(auto&& [whole, name] = match2(realname); whole)
        ret = QString::fromStdString(name.to_string());
    else if(auto&& [whole, stl, name] = match3(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if(auto&& [whole, name] = match4(realname); whole)
        ret = QString::fromStdString(name.to_string());
    return ret;
}
#endif

using sl = std::source_location;

QTextStream& operator<<(QTextStream& d, std::string_view sv);

QDebug operator<<(QDebug d, std::string_view sv);

QDebug operator<<(QDebug d, std::set<QString> c);

struct Xml;

namespace ImplXml {

template <typename T>
bool read(Xml& xml, XmlAttr<T>& attr);

template <typename T>
    requires(std::is_class_v<T> && std::is_aggregate_v<T>)
bool read(Xml& xml, T& str);

template <typename T, size_t... Is>
bool read(Xml& xml, T& str, std::index_sequence<Is...>);

template <size_t Is, typename T>
bool readField(Xml& xml, T& str);

template <typename T>
bool read(Xml& xml, T& str);

template <typename T>
    requires std::is_enum_v<T>
inline bool read(Xml& xml, T& e);

template <typename T>
    requires std::is_arithmetic_v<T>
inline bool read(Xml& xml, T& e);

} // namespace ImplXml

struct Xml {
    QDomDocument doc{"mydocument"};
    TreeItem* const item{new TreeItem};
    Xml(const QString& name = "../МАН2_МСИС_V2.1.fst");

    // QByteArray byteArray;
    // QBuffer buffer{&byteArray};
    // QTextStream out{&buffer};

    TreeItem* tree{item};
    QDomNode node;
    int depth{};
    int fieldNum{};

    bool isArray{};
    bool isVariant{};
    bool isAarrayElem{};

    QString fieldName;

    template <typename T>
    bool read(T& str) {
        return ImplXml::read(*this, str);
    }
};

enum {
    Name,
    Value,
    IsAttr,
    FLine,
    Type,
};

namespace ImplXml {

struct loger {
    static inline int i;
    loger(Xml& xml) {
        auto type = [](QDomNode& node) {
            switch(node.nodeType()) {
            case QDomNode::ElementNode: return "Element Node";
            case QDomNode::AttributeNode: return "Attribute Node";
            case QDomNode::TextNode: return "Text Node";
            case QDomNode::CDATASectionNode: return "CDATASection Node";
            case QDomNode::EntityReferenceNode: return "EntityReference Node";
            case QDomNode::EntityNode: return "Entity Node";
            case QDomNode::ProcessingInstructionNode: return "ProcessingInstruction Node";
            case QDomNode::CommentNode: return "Comment Node";
            case QDomNode::DocumentNode: return "Document Node";
            case QDomNode::DocumentTypeNode: return "DocumentType Node";
            case QDomNode::DocumentFragmentNode: return "DocumentFragment Node";
            case QDomNode::NotationNode: return "Notation Node";
            case QDomNode::BaseNode: return "Base Node";
            case QDomNode::CharacterDataNode: return "CharacterData Node";
            }
            return "";
        };

        qInfo() << QByteArray{i++ * 4, ' '}.data() << type(xml.node) << xml.node.nodeName() << xml.node.nodeValue() << xml.node.lineNumber();
    }
    ~loger() { --i; }
};

template <>
inline bool read(Xml& xml, QString& str) {
    if(xml.node.isElement()) {
        xml.node = xml.node.firstChildElement(xml.fieldName);
        loger log{xml};
        str = xml.node.toElement().text();
        xml.node = xml.node.parentNode();

        auto tree = xml.tree->addItem(new TreeItem);
        tree->itemData[Name] = xml.fieldName;
        tree->itemData[Value] = str;
        // tree->itemData[IsAttr] = "Tag";
        tree->itemData[Type] = typeid(QString).name();
        tree->itemData[FLine] = xml.node.lineNumber();
    } else if(xml.node.isAttr()) {
        str = xml.node.nodeValue();
        loger log{xml};

        auto tree = xml.tree->addItem(new TreeItem);
        tree->itemData[Name] = xml.node.toAttr().name();
        tree->itemData[Value] = str;
        tree->itemData[IsAttr] = "Attr";
        tree->itemData[Type] = typeid(QString).name();
        tree->itemData[FLine] = xml.node.parentNode().lineNumber();
    }

    return str.size();
}

template <typename T>
    requires std::is_arithmetic_v<T>
inline bool read(Xml& xml, T& value) {
    QString text;
    if(xml.node.isElement()) {
        if(text = xml.node.toElement().attribute(typeName<T>()); text.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = typeName<T>();
            tree->itemData[Value] = text;
            // tree->itemData[IsAttr] = "Tag";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.lineNumber();
        } else if(text = xml.node.toElement().attribute(xml.fieldName); text.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = xml.fieldName;
            tree->itemData[Value] = text;
            // tree->itemData[IsAttr] = "Tag";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.lineNumber();
        }
    } else if(xml.node.isAttr()) {
        if(text = xml.node.nodeValue(); text.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = xml.node.toAttr().name();
            tree->itemData[Value] = text;
            tree->itemData[IsAttr] = "Attr";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.parentNode().lineNumber();
        }
    }
    value = QVariant{text}.value<T>();
    return text.size();
}

template <typename T>
    requires std::is_enum_v<T>
inline bool read(Xml& xml, T& e) {
    QString value;
    if(xml.node.isElement()) {
        if(value = xml.node.toElement().attribute(typeName<T>()); value.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = xml.fieldName;
            tree->itemData[Value] = value;
            // tree->itemData[IsAttr] = "Tag";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.lineNumber();
        } else if(value = xml.node.toElement().attribute(xml.fieldName); value.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = xml.fieldName;
            tree->itemData[Value] = value;
            // tree->itemData[IsAttr] = "Tag";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.lineNumber();
        }
    } else if(xml.node.isAttr()) {
        if(value = xml.node.nodeValue(); value.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[Name] = xml.node.toAttr().name();
            tree->itemData[Value] = value;
            tree->itemData[IsAttr] = "Attr";
            tree->itemData[Type] = typeName<T>();
            tree->itemData[FLine] = xml.node.parentNode().lineNumber();
        }
    }
    e = stringToEnum<T>(value.toStdString());

    return value.size();
}

template <typename T>
inline bool read(Xml& xml, std::optional<T>& optional) { // FIXME check contains tag/attribute
    T val;
    if(read(xml, val)) optional = val;
    return optional.has_value();
}

template <typename T>
inline bool read(Xml& xml, XmlAttr<T>& attr) {
    auto attributes = xml.node.attributes();
    if(attributes.contains(typeName<T>())) {
        xml.node = attributes.namedItem(typeName<T>());
        loger log{xml};
        bool ok = read(xml, attr.value);
        xml.node = xml.node.parentNode();
        return ok;
    } else if(attributes.contains(xml.fieldName)) {
        xml.node = attributes.namedItem(xml.fieldName);
        loger log{xml};
        bool ok = read(xml, attr.value);
        xml.node = xml.node.parentNode();
        return ok;
    }
    return {};
}

template <typename... Ts>
inline bool read(Xml& xml, XmlVariant<Ts...>& variant) { // FIXME variant
    int ctr{};
    if(!xml.node.isElement()) return {};
    auto reader = [&]<typename T>(T&& val) {
        if(ctr) return;
        qWarning() << xml.node.toElement().tagName() << typeName<T>();
        if(xml.node.toElement().tagName() == typeName<T>()) {
            if(read(xml, val))
                ++ctr, variant = std::move(val);
        } else {
            auto copy = xml.node;
            xml.node = xml.node.firstChildElement(typeName<T>());
            if(!xml.node.isNull())
                if(xml.isVariant = true; read(xml, val)) ++ctr, variant = std::move(val);
            xml.node = copy;
        }
    };
    (reader(Ts{}), ...);
    assert(ctr < 2);
    return ctr > 0;
}

template <typename T>
inline bool read(Xml& xml, XmlArrayElem<T>& vector) { // FIXME vector

    QDomNode node = xml.node.firstChildElement(xml.fieldName);
    if(node.isNull())
        return false;

    auto copy = xml.node;
    xml.isAarrayElem = true;
    xml.node = node; //->log

    loger log{xml};

    auto childNodes = node.childNodes();
    if(!childNodes.size())
        return false;

    {
        xml.tree = xml.tree->addItem(new TreeItem);
        xml.tree->itemData[Name] = xml.fieldName;
        xml.tree->itemData[Value] = childNodes.size();
        xml.tree->itemData[Type] = typeName<T>();
        xml.tree->itemData[FLine] = xml.node.parentNode().lineNumber();
    }

    vector.resize(childNodes.size());

    bool ok{true};

    // node = node.firstChild();
    // for (auto&& var: vector) {
    //     xml.isArray = true;
    //     xml.node = childNodes.at(index);
    //     read(xml, var);
    //     // xml.node = node.nextSibling();
    // }

    for(int index{}; auto&& var: vector) {
        xml.isArray = true;
        xml.node = childNodes.at(index++);
        ok &= read(xml, var);
    }

    // for (int index{}; index < childNodes.size(); ++index) {
    //     xml.isArray = true;
    //     xml.node = childNodes.at(index);
    //     ok &= read(xml, vector[index]);
    // }

    xml.isAarrayElem = false;
    xml.node = copy;

    {
        xml.tree = xml.tree->parent();
    }

    return ok;
}

template <typename T>
inline bool read(Xml& xml, XmlArray<T>& vector) {
    if(xml.node.isNull())
        return false;

    auto childNodes = xml.node.childNodes();

    auto find = [&]<typename Ty>(Ty&&) -> int {
        auto node = xml.node.firstChildElement(typeName<Ty>());
        if(!node.isNull())
            for(int i{}; i < childNodes.size(); ++i)
                if(childNodes.at(i) == node) return i;
        return 999999;
    };

    auto index = Overload{
        [&]<typename... Ts>(XmlVariant<Ts...>&&) -> int {
            std::array arr{find(Ts{})...};
            return *std::ranges::min_element(arr);
        },
        find}(T{});

    if(index == 999999)
        return false;

    vector.resize(childNodes.size() - index);

    if(vector.empty())
        return false;

    const auto copy = xml.node;

    bool ok{true};

    for(auto&& var: vector) {
        xml.isArray = true;
        xml.node = childNodes.at(index++);
        ok &= read(xml, var);
    }

    xml.node = copy;
    return ok;
}

template <typename T>
    requires(std::is_class_v<T> && std::is_aggregate_v<T>)
inline bool read(Xml& xml, T& str) { // pod structures
    if(!xml.isArray && !xml.isVariant)
        xml.node = (xml.node.isNull() ? xml.doc : xml.node).firstChildElement(typeName<T>());
    xml.isArray = xml.isVariant = false;

    loger log{xml};
    {
        xml.tree = xml.tree->addItem(new TreeItem);
        xml.tree->itemData[Name] = typeName<T>();
        // xml.tree->itemData[Value] = value;
        // xml.tree->itemData[IsAttr] = "Tag";
        xml.tree->itemData[Type] = typeName<T>();
        xml.tree->itemData[FLine] = xml.node.lineNumber();
    }

    bool ok = read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
    xml.node = xml.node.parentNode();
    {
        xml.tree = xml.tree->parent();
    }
    return ok;
}

template <typename T, size_t... Is>
inline bool read(Xml& xml, T& str, std::index_sequence<Is...>) {
    int ok{};
    ((ok += readField<Is>(xml, str)), ...);
    return ok;
}

template <size_t Is, typename T>
inline bool readField(Xml& xml, T& str) {
    xml.fieldName = pfr::get_name<Is, T>().data();
    xml.fieldNum = Is;
    auto copy = xml.node;
    bool ok = read(xml, pfr::get<Is>(str));
    xml.node = copy;
    return ok;
}

template <typename T>
    requires(!std::is_class_v<T> && !std::is_aggregate_v<T>)
inline bool read(Xml& xml, T& str) {
    qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>();
    return false;
}

template <typename T>
    requires(std::is_polymorphic_v<T>)
inline bool read(Xml& xml, T& str) {
    qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>();
    return false;
}

} // namespace ImplXml
