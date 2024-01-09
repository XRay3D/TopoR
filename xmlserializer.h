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

using sl = std::source_location;

QTextStream& operator<<(QTextStream& d, std::string_view sv);

QDebug operator<<(QDebug d, std::string_view sv);

QDebug operator<<(QDebug d, std::set<QString> c);

struct Xml {
    QDomDocument doc{"mydocument"};
    TreeItem* const item{new TreeItem};
    Xml(const QString& name = "../МАН2_МСИС_V2.1.fst");

    TreeItem* tree{item};
    QDomNode node;
    int depth{};
    mutable int fieldNum{};
    bool isRead{};
    bool isArray{};
    bool isVariant{};
    bool isAarrayElem{};

    mutable bool isAttribute{};
    mutable QString fieldName;
    mutable QDomDocument outDoc;
    mutable QDomNode outNode;

private:
    template <typename T> struct Tag { };
    static constexpr auto ArrayNull = std::numeric_limits<int>::max();

    enum {
        Name,
        Value,
        IsAttr,
        FLine,
        Type,
    };

    bool read(QString& str) {
        if (node.isElement()) {
            node = node.firstChildElement(fieldName);
            str = node.toElement().text();
            node = node.parentNode();
            auto tree_ = tree->addItem(new TreeItem);
            tree_->itemData[Name] = fieldName;
            tree_->itemData[Value] = str;
            // tree_->itemData[IsAttr] = "Tag";
            tree_->itemData[Type] = typeid(QString).name();
            tree_->itemData[FLine] = node.lineNumber();
        } else if (node.isAttr()) {
            str = node.nodeValue();
            auto tree_ = tree->addItem(new TreeItem);
            tree_->itemData[Name] = node.toAttr().name();
            tree_->itemData[Value] = str;
            tree_->itemData[IsAttr] = "Attr";
            tree_->itemData[Type] = typeid(QString).name();
            tree_->itemData[FLine] = node.parentNode().lineNumber();
        }
        return str.size();
    }

    template <typename T> bool read(T& value) // float`ы int`ы
        requires std::is_arithmetic_v<T>
    {
        QString text;
        if (node.isElement()) {
            auto element = node.toElement();
            if (text = element.attribute(TypeName<T>); text.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = TypeName<T>;
                tree_->itemData[Value] = text;
                // tree->itemData[IsAttr] = "Tag";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.lineNumber();
            } else if (text = element.attribute(fieldName); text.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = fieldName;
                tree_->itemData[Value] = text;
                // tree->itemData[IsAttr] = "Tag";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.lineNumber();
            }
        } else if (node.isAttr()) {
            if (text = node.nodeValue(); text.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = node.toAttr().name();
                tree_->itemData[Value] = text;
                tree_->itemData[IsAttr] = "Attr";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.parentNode().lineNumber();
            }
        }
        value = QVariant{text}.value<T>();
        return text.size();
    }

    template <typename T> bool read(T& e) // enum`ы
        requires std::is_enum_v<T>
    {
        QString value;
        if (node.isElement()) {
            if (value = node.toElement().attribute(TypeName<T>); value.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = fieldName;
                tree_->itemData[Value] = value;
                // tree_->itemData[IsAttr] = "Tag";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.lineNumber();
            } else if (value = node.toElement().attribute(fieldName); value.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = fieldName;
                tree_->itemData[Value] = value;
                // tree_->itemData[IsAttr] = "Tag";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.lineNumber();
            }
        } else if (node.isAttr()) {
            if (value = node.nodeValue(); value.size()) {
                auto tree_ = tree->addItem(new TreeItem);
                tree_->itemData[Name] = node.toAttr().name();
                tree_->itemData[Value] = value;
                tree_->itemData[IsAttr] = "Attr";
                tree_->itemData[Type] = TypeName<T>;
                tree_->itemData[FLine] = node.parentNode().lineNumber();
            }
        }
        e = stringToEnum<T>(value.toStdString());
        return value.size();
    }

    template <typename T> bool read(std::optional<T>& optional) { // перенаправление ↑↑↑
        T val;
        if (read(val)) optional = val;
        return optional.has_value();
    }

    template <typename T> bool read(XmlAttr<T>& attr) { // перенаправление ↑↑↑
        auto attributes = node.attributes();
        if (attributes.contains(TypeName<T>)) {
            node = attributes.namedItem(TypeName<T>);
            bool ok = read(attr.value);
            node = node.parentNode();
            return ok;
        } else if (attributes.contains(fieldName)) {
            node = attributes.namedItem(fieldName);
            bool ok = read(attr.value);
            node = node.parentNode();
            return ok;
        }
        return false;
    }

    template <typename... Ts> bool read(XmlVariant<Ts...>& variant) { // перенаправление ↑↑↑
        int ctr{};
        if (!node.isElement()) return false;
        auto reader = [&]<typename T>(T&& val) {
            if (ctr) return;
            if (node.toElement().tagName() == TypeName<T> && read(val)) {
                ++ctr, variant = std::move(val);
            } else {
                auto copy = node;
                node = node.firstChildElement(TypeName<T>);
                if (!node.isNull())
                    if (isVariant = true; read(val)) ++ctr, variant = std::move(val);
                node = copy;
            }
        };
        (reader(Ts{}), ...);
        assert(ctr < 2);
        return ctr > 0;
    }

    template <typename T> bool read(XmlArrayElem<T>& vector) { // перенаправление ↑↑↑
        QDomNode node_ = node.firstChildElement(fieldName);
        if (node_.isNull())
            return false;
        isAarrayElem = true;
        auto childNodes = node_.childNodes();
        if (!childNodes.size())
            return false;
        tree = tree->addItem(new TreeItem);
        tree->itemData[Name] = fieldName;
        tree->itemData[Value] = childNodes.size();
        tree->itemData[Type] = TypeName<T>;
        tree->itemData[FLine] = node.lineNumber();

        vector.resize(childNodes.size());

        bool ok{true};

        for (int index{}; auto&& var: vector) {
            isArray = true;
            node = childNodes.at(index++);
            ok &= read(var);
        }

        isAarrayElem = false;
        tree = tree->parent();

        return ok;
    }

    template <typename T> bool read(XmlArray<T>& vector) { // перенаправление ↑↑↑
        if (node.isNull())
            return false;
        auto childNodes = node.childNodes();
        auto find = [&]<typename Type>(Tag<Type>) -> int {
            auto node_ = node.firstChildElement(TypeName<Type>);
            if (!node_.isNull())
                for (int index{}; index < childNodes.size(); ++index)
                    if (childNodes.at(index) == node_) return index;
            return ArrayNull;
        };
        auto index = Overload{
            [&]<typename... Ts>(Tag<XmlVariant<Ts...>>) -> int {
                std::array arr{find(Tag<Ts>{})...};
                return *std::ranges::min_element(arr);
            },
            find}(Tag<T>{});
        if (index == ArrayNull)
            return false;
        vector.resize(childNodes.size() - index);
        if (vector.empty())
            return false;

        bool ok{true};
        for (auto&& var: vector) {
            isArray = true;
            node = childNodes.at(index++);
            ok &= read(var);
        }
        return ok;
    }
    ///////////////////////////////////////////////////////////////////////////
    bool write(const QString& str) const {
        if (isAttribute) {
            isAttribute = false;
            // outNode.toElement().setAttribute(fieldName, str);
            auto node = outDoc.createAttribute(fieldName);
            node.toCharacterData().setData(str);
            outNode.toElement().setAttributeNode(node);
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str));
            outNode.appendChild(element);
        }
        return true;
    }

    template <typename T> bool write(const T& value) const // float`ы int`ы
        requires std::is_arithmetic_v<T>
    {
        if (isAttribute) {
            isAttribute = false;
            outNode.toElement().setAttribute(fieldName, value);
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(QString::number(value)));
            outNode.appendChild(element);
        }
        return true;
    }

    template <typename T> bool write(const T& e) const // enum`ы
        requires std::is_enum_v<T>
    {
        auto str = enumToString(e);
        if (!str.size()) return false;
        if (isAttribute) {
            isAttribute = false;
            outNode.toElement().setAttribute(fieldName, str.data());
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str.data()));
            outNode.appendChild(element);
        }
        return true;
    }

    template <typename T> bool write(const std::optional<T>& optional) const { // перенаправление ↑↑↑
        if (optional) return write(optional.value());
        return optional.has_value();
    }

    template <typename T> bool write(const XmlAttr<T>& attr) const { // перенаправление ↑↑↑
        isAttribute = true;
        return write(attr.value);
    }

    template <typename... Ts> bool write(const XmlVariant<Ts...>& variant) const { // перенаправление ↑↑↑
        if (!variant.has_value()) return false;
        return variant.visit([this](auto&& val) { return write(val); });
    }

    template <typename T> bool write(const XmlArrayElem<T>& vector) const { // перенаправление ↑↑↑
        if (vector.empty()) return false;                                   // NOTE maybe true
        bool ok{true};
        outNode = outNode.appendChild(outDoc.createElement(fieldName));
        for (auto&& var: vector)
            ok &= write(var);
        outNode = outNode.parentNode();
        return ok;
    }

    template <typename T> bool write(const XmlArray<T>& vector) const { // перенаправление ↑↑↑
        bool ok{true};
        for (auto&& var: vector)
            ok &= write(var);
        return ok;
    }

public:
    template <typename T> bool read(T& str)
        requires(std::is_class_v<T> && std::is_aggregate_v<T>)
    { // чтение полей структуры
        if (!isArray && !isVariant)
            node = (node.isNull() ? doc : node).firstChildElement(TypeName<T>);
        isArray = isVariant = false;

        tree = tree->addItem(new TreeItem);
        tree->itemData[Name] = TypeName<T>;
        // tree->itemData[Value] = value;
        // tree->itemData[IsAttr] = "Tag";
        tree->itemData[Type] = TypeName<T>;
        tree->itemData[FLine] = node.lineNumber();

        auto readStr = [this]<typename Ty, size_t... Is>(Ty& str, std::index_sequence<Is...>) {
            auto readField = [this]<size_t Index, typename FTy>(FTy& str, std::integral_constant<size_t, Index>) {
                fieldName = pfr::get_name<Index, FTy>().data();
                if (fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
                fieldNum = Index;
                auto copy = node;
                bool ok = read(pfr::get<Index>(str));
                node = copy;
                return ok;
            };
            int ok{};
            ((ok += readField(str, std::integral_constant<size_t, Is>{})), ...);
            return ok;
        };

        bool ok = readStr(str, std::make_index_sequence<pfr::tuple_size_v<T>>{});

        node = node.parentNode();
        tree = tree->parent();
        return ok;
    }

    template <typename T> bool write(const T& str) const
        requires(std::is_class_v<T> && std::is_aggregate_v<T>)
    { // чтение полей структуры
        outNode = outNode.isNull()
            ? outDoc.appendChild(outDoc.createElement(TypeName<T>))
            : outNode.appendChild(outDoc.createElement(TypeName<T>));

        auto writeStr = [this]<typename Ty, size_t... Is>(Ty& str, std::index_sequence<Is...>) {
            auto writeField = [this]<size_t Index, typename FTy>(FTy& str, std::integral_constant<size_t, Index>) {
                fieldName = pfr::get_name<Index, FTy>().data();
                if (fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
                fieldNum = Index;
                auto copy = outNode;
                bool ok = write(pfr::get<Index>(str));
                outNode = copy;
                return ok;
            };
            int ok{};
            ((ok += writeField(str, std::integral_constant<size_t, Is>{})), ...);
            return ok;
        };

        bool ok = writeStr(str, std::make_index_sequence<pfr::tuple_size_v<T>>{});

        outNode = outNode.parentNode();
        return ok;
    }
};
