#pragma once

#include "TopoR_PCB_File.h"
#include "pfr.hpp"
#include "treeitem.h"
#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <set>
#include <source_location>
#include <stack>

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
inline QString demangle(const std::type_info& ti) {
    QString ret{ti.name()};
    return ret;
}
#endif

using sl = std::source_location;

QTextStream& operator<<(QTextStream& d, std::string_view sv);

QDebug operator<<(QDebug d, std::string_view sv);

QDebug operator<<(QDebug d, std::set<QString> c);

using namespace TopoR_PCB_Classes;

struct Xml;

namespace ImplXml {

template <typename T>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
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

    bool isArray{};
    QString fieldName;

    template <typename T>
    bool read(T& str) {
        return ImplXml::read(*this, str);
    }
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
        tree->itemData[0] = xml.fieldName;
        tree->itemData[1] = str;

    } else if(xml.node.isAttr()) {
        str = xml.node.nodeValue();

        auto tree = xml.tree->addItem(new TreeItem);
        tree->itemData[0] = xml.node.toAttr().name();
        tree->itemData[1] = str;
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
            tree->itemData[0] = typeName<T>();
            tree->itemData[1] = text;
        } else if(text = xml.node.toElement().attribute(xml.fieldName); text.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[0] = xml.fieldName;
            tree->itemData[1] = text;
        }
    } else if(xml.node.isAttr()) {
        if(text = xml.node.nodeValue(); text.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[0] = xml.node.toAttr().name();
            tree->itemData[1] = text;
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
            tree->itemData[0] = typeName<T>();
            tree->itemData[1] = value;
        } else if(value = xml.node.toElement().attribute(xml.fieldName); value.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[0] = xml.fieldName;
            tree->itemData[1] = value;
        }
    } else if(xml.node.isAttr()) {
        if(value = xml.node.nodeValue(); value.size()) {
            auto tree = xml.tree->addItem(new TreeItem);
            tree->itemData[0] = xml.node.toAttr().name();
            tree->itemData[1] = value;
        }
    }
    e = stringToEnum<T>(value.toStdString());

    return value.size();
}

template <typename T>
inline bool read(Xml& xml, std::optional<T>& optional) {
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
        if(xml.node.toElement().tagName() == typeName<T>()) {
            if(read(xml, val))
                ++ctr, variant = std::move(val);
        } else if(read(xml, val))
            ++ctr, variant = std::move(val);
    };
    (reader(Ts{}), ...);
    // assert(ctr < 2);
    return {};
}

template <typename T>
inline bool read(Xml& xml, std::vector<T>& vector) { // FIXME vector
    auto node = xml.node.firstChildElement(xml.fieldName);
    if(node.isNull())
        return false;
    auto copy = xml.node;

    xml.node = node; //->log
    loger log{xml};

    auto childNodes = node.childNodes();
    vector.resize(childNodes.size());
    for(int index{}; index < childNodes.size(); ++index) {
        xml.isArray = true;
        xml.node = childNodes.at(index);
        read(xml, vector[index]);
    }
    xml.isArray = false;
    xml.node = copy;
    return true;
}

template <typename T>
inline bool read(Xml& xml, XmlArray<T>& vector) {
    auto node = xml.node;
    if(node.isNull())
        return false;
    auto copy = xml.node;

    xml.node = node; //->log
    loger log{xml};

    auto childNodes = node.childNodes();
    vector.resize(childNodes.size());
    for(int index{}; index < childNodes.size(); ++index) {
        xml.isArray = true;
        xml.node = childNodes.at(index);
        read(xml, vector[index]);
    }
    xml.isArray = false;
    xml.node = copy;
    return true;
}

template <typename T>
    requires(std::is_standard_layout_v<T> && std::is_aggregate_v<T>)
inline bool read(Xml& xml, T& str) { // pod structures
    if(!xml.isArray)
        xml.node = (xml.node.isNull() ? xml.doc : xml.node).firstChildElement(typeName<T>());
    xml.isArray = false;
    loger log{xml};
    xml.tree = xml.tree->addItem(new TreeItem);
    xml.tree->itemData[0] = typeName<T>();
    bool ok = read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
    xml.node = xml.node.parentNode();
    xml.tree = xml.tree->parent();
    return ok;
}

template <typename T, size_t... Is>
inline bool read(Xml& xml, T& str, std::index_sequence<Is...>) {
    int ok{};
    ((ok |= readField<Is>(xml, str)), ...);
    return ok;
}

template <size_t Is, typename T>
inline bool readField(Xml& xml, T& str) {
    xml.fieldName = pfr::get_name<Is, T>().data();
    return read(xml, pfr::get<Is>(str));
}

template <typename T>
// requires(!std::is_standard_layout_v<T> && !std::is_aggregate_v<T>)
inline bool read(Xml& xml, T& str) {
    qCritical() << "!!!ERR!!!" << __PRETTY_FUNCTION__ << typeName<T>();
    return false;
}

} // namespace ImplXml
