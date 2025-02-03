#pragma once

#include "TopoR_PCB_File.h"

#include "treeitem.h"

#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <QRegularExpression>

#if __has_include(<boost/pfr.hpp>)
#include <boost/pfr.hpp>
#else
#include <pfr/config.hpp>
#include <pfr/core.hpp>
#include <pfr/core_name.hpp>
#include <pfr/functions_for.hpp>
#include <pfr/functors.hpp>
#include <pfr/io.hpp>
#include <pfr/io_fields.hpp>
#include <pfr/ops.hpp>
#include <pfr/ops_fields.hpp>
#include <pfr/traits.hpp>
#include <pfr/traits_fwd.hpp>
#include <pfr/tuple_size.hpp>
#endif
#include <set>
#include <source_location>

namespace pfr = boost::pfr;

template <typename R> concept Range = requires(R& r) { std::begin(r); std::end(r); };
template <typename T> concept Struct = !Range<T> && pfr::is_implicitly_reflectable_v<T, T>; //&& pfr::tuple_size_v<T>;
template <typename T> concept Numbers = std::is_arithmetic_v<T>;
template <typename T> concept Enums = std::is_enum_v<T>;
template <typename T> concept To = std::is_base_of_v<std::initializer_list<typename T::value_type>, T> == false || Struct<T>;

using namespace TopoR;

using sl = std::source_location;

QTextStream& operator<<(QTextStream& d, std::string_view sv);

QDebug operator<<(QDebug d, std::string_view sv);

QDebug operator<<(QDebug d, std::set<QString> c);

struct Xml {
    QDomDocument doc{"mydocument"};
    TreeItem* const item{new TreeItem};
    Xml(const QString& name = "../МАН2_МСИС_V2.1.fst");

    TreeItem* dbgTree{item};
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

    void save(const QString& dir);

private:
    template <typename T> struct Tag { };
    static constexpr auto ArrayNull = std::numeric_limits<int>::max();

    /// QString
    bool read(QString& str) {
        if(node.isElement()) {
            node = node.firstChildElement(fieldName);
            str = node.toElement().text();
            node = node.parentNode();
            dbgTree->addItem(new TreeItem{
                fieldName, "QString", str, "",
                node.lineNumber()});
        } else if(node.isAttr()) {
            str = node.nodeValue();
            dbgTree->addItem(new TreeItem{
                node.toAttr().name(), "QString", str, "Attr",
                node.parentNode().lineNumber()});
        }
        return str.size();
    }

    bool write(const QString& str) const {
        if(isAttribute) {
            isAttribute = false;
            if(str.size()) outNode.toElement().setAttribute(fieldName, str);
            // auto node = outDoc.createAttribute(fieldName);
            // node.toCharacterData().setData(str);
            // outNode.toElement().setAttributeNode(node);
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str));
            outNode.appendChild(element);
        }
        return true;
    }
    /// Numbers
    template <Numbers T> bool read(T& value) { // float`ы int`ы
        QString text;
        if(node.isElement()) {
            auto element = node.toElement();
            if(text = element.attribute(TypeName<T>); text.size()) {
                dbgTree->addItem(new TreeItem{
                    TypeName<T>, TypeName<T>, text, "", // TAG
                    node.lineNumber()});
            } else if(text = element.attribute(fieldName); text.size()) {
                dbgTree->addItem(new TreeItem{
                    fieldName, TypeName<T>, text, "", // TAG
                    node.lineNumber()});
            }
        } else if(node.isAttr()) {
            if(text = node.nodeValue(); text.size()) {
                dbgTree->addItem(new TreeItem{
                    node.toAttr().name(), TypeName<T>, text, "Attr",
                    node.parentNode().lineNumber()});
            }
        }
        value = QVariant{text}.value<T>();
        return text.size();
    }

    template <Numbers T> bool write(const T& value) const { // float`ы int`ы
        auto str = QVariant{value}.toString();
        // if constexpr(std::is_floating_point_v<T>) {
        //     static QRegularExpression re{R"((.\d+\.\d+)(00|01|99)(\d+))"};
        //     auto match = re.match(str);
        //     if(match.captured(2) == "99") {
        //         str = match.captured(1);
        //         str.back() = str.back().toLatin1() + 1;
        //     } else {
        //         str = match.captured(0);
        //     }
        // }

        if(isAttribute) {
            isAttribute = false;
            outNode.toElement().setAttribute(fieldName, str /*value*/);
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str /*QVariant{value}.toString()*/)); // NOTE without rounding
            outNode.appendChild(element);
        }
        return true;
    }

    /// Enums
    template <Enums T> bool read(T& e) { // enum`ы
        QString value;
        if(node.isElement()) {
            if(value = node.toElement().attribute(TypeName<T>); value.size()) {
                dbgTree->addItem(new TreeItem{
                    fieldName, TypeName<T>, value, "",
                    node.lineNumber()});
            } else if(value = node.toElement().attribute(fieldName); value.size()) {
                dbgTree->addItem(new TreeItem{
                    fieldName, TypeName<T>, value, "",
                    node.lineNumber()});
            }
        } else if(node.isAttr()) {
            if(value = node.nodeValue(); value.size()) {
                dbgTree->addItem(new TreeItem{
                    node.toAttr().name(), TypeName<T>, value, "Attr",
                    node.parentNode().lineNumber()});
            }
        }
        e = stringToEnum<T>(value.toStdString());
        return value.size();
    }

    template <Enums T> bool write(const T& e) const { // enum`ы
        auto str = enumToString(e);
        if(!str.size()) return false;
        if(isAttribute) {
            isAttribute = false;
            outNode.toElement().setAttribute(fieldName, str.data());
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str.data()));
            outNode.appendChild(element);
        }
        return true;
    }

    /// std::optional
    template <typename T> bool read(std::optional<T>& optional) { // перенаправление ↑↑↑
        if(T val; read(val)) optional = std::move(val);
        return optional.has_value();
    }

    template <typename T> bool write(const std::optional<T>& optional) const { // перенаправление ↑↑↑
        if(optional) return write(*optional);
        return optional.has_value();
    }

    /// XmlAttr<T>
    template <typename T> bool read(XmlAttr<T>& attr) { // перенаправление ↑↑↑
        auto attributes = node.attributes();
        if(attributes.contains(TypeName<T>)) {
            node = attributes.namedItem(TypeName<T>);
            bool ok = read(attr.value);
            node = node.parentNode();
            return ok;
        } else if(attributes.contains(fieldName)) {
            node = attributes.namedItem(fieldName);
            bool ok = read(attr.value);
            node = node.parentNode();
            return ok;
        }
        return false;
    }

    template <typename T> bool write(const XmlAttr<T>& attr) const { // перенаправление ↑↑↑
        isAttribute = true;
        // if(attr.value == T{}) return false;
        return write(attr.value);
    }

    /// XmlVariant<Ts...>
    template <typename... Ts> bool read(XmlVariant<Ts...>& variant) { // перенаправление ↑↑↑
        int ctr{};
        if(!node.isElement()) return false;
        QStringList list;
        auto reader = [&]<typename T>() {
            if(ctr) return;
            if(TypeName<T> == "FilledCircle")
                qDebug();
            if(T val{}; node.toElement().tagName() == TypeName<T> && read(val)) {
                {
                    ++ctr, variant = std::move(val);
                    list.append(TypeName<T>);
                }
            } else {
                auto copy = node;
                node = node.firstChildElement(TypeName<T>);
                if(!node.isNull())
                    if(isVariant = true; read(val)) {
                        ++ctr, variant = std::move(val);
                        list.append(TypeName<T>);
                    }
                node = copy;
            }
        };
        (reader.template operator()<Ts>(), ...);
        qWarning() << list;
        assert(ctr < 2);
        return ctr > 0;
    }

    template <typename... Ts> bool write(const XmlVariant<Ts...>& variant) const { // перенаправление ↑↑↑
        if(!variant.has_value()) return false;
        return variant.visit([this](auto&& val) { return write(val); });
    }

    /// XmlArrayElem<T>
    template <typename T> bool read(XmlArrayElem<T>& vector) { // перенаправление ↑↑↑
        QDomNode node_ = node.firstChildElement(fieldName);
        if(node_.isNull())
            return false;
        isAarrayElem = true;
        auto childNodes = node_.childNodes();
        if(!childNodes.size())
            return true /*false*/; // NOTE Force add emty tag
        dbgTree = dbgTree->addItem(new TreeItem{
            fieldName, TypeName<T>,
            QString::number(childNodes.size()),
            "ArrObj", node.lineNumber()});
        vector.resize(childNodes.size());

        bool ok{true};

        for(int index{}; auto&& var: vector) {
            isArray = true;
            node = childNodes.at(index++);
            ok &= read(var);
        }

        isAarrayElem = false;
        dbgTree = dbgTree->parent();

        return ok;
    }

    template <typename T> bool write(const XmlArrayElem<T>& vector) const { // перенаправление ↑↑↑
        if(vector.empty()) return false;                                    // NOTE maybe true
        bool ok{true};
        outNode = outNode.appendChild(outDoc.createElement(fieldName));
        for(auto&& var: vector)
            ok &= write(var);
        outNode = outNode.parentNode();
        return ok;
    }

    /// XmlArray<T>
    template <typename T> bool read(XmlArray<T>& vector) { // перенаправление ↑↑↑
        if(node.isNull())
            return false;
        auto childNodes = node.childNodes();
        auto find = [&]<typename Type>(Tag<Type>) -> int {
            auto node_ = node.firstChildElement(TypeName<Type>);
            if(!node_.isNull())
                for(int index{}; index < childNodes.size(); ++index)
                    if(childNodes.at(index) == node_) return index;
            return ArrayNull;
        };
        auto index = Overload{
            [&]<typename... Ts>(Tag<XmlVariant<Ts...>>) -> int {
                std::array arr{find(Tag<Ts>{})...};
                return *std::ranges::min_element(arr);
            },
            find}(Tag<T>{});
        if(index == ArrayNull)
            return false;
        vector.resize(childNodes.size() - index);
        if(vector.empty())
            return false;

        bool ok{true};
        dbgTree->itemData[TreeItem::IsAttr] = "Array";
        for(auto&& var: vector) {
            isArray = true;
            node = childNodes.at(index++);
            ok &= read(var);
        }
        return ok;
    }

    template <typename T> bool write(const XmlArray<T>& vector) const { // перенаправление ↑↑↑
        bool ok{true};
        for(auto&& var: vector)
            ok &= write(var);
        return ok;
    }

    /// Skip<T>
    template <typename T> bool read(Skip<T>&) { // пропуск поля
        return true;
    }

    template <typename T> bool write(const Skip<T>&) const { // пропуск поля
        return true;
    }

public:
    template <Struct T> bool read(T& str) { // чтение полей структуры
        if(!isArray && !isVariant)
            node = (node.isNull() ? doc : node).firstChildElement(TypeName<T>);
        isArray = isVariant = false;

        dbgTree = dbgTree->addItem(new TreeItem{TypeName<T>, TypeName<T>,
            "", "", node.lineNumber()});

        int ok{};
        pfr::for_each_field_with_name(str, [this, &ok](auto name, auto&& field, auto index) {
            fieldName = QString::fromUtf8(name.data());
            if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
            fieldNum = index;
            auto copy = node;
            ok += read(field);
            node = copy;
        });

        node = node.parentNode();
        dbgTree = dbgTree->parent();
        return ok;
    }

    template <Struct T> bool write(const T& str) const { // чтение полей структуры
        outNode = outNode.isNull()
            ? outDoc.appendChild(outDoc.createElement(TypeName<T>))
            : outNode.appendChild(outDoc.createElement(TypeName<T>));

        int ok{};
        pfr::for_each_field_with_name(str, [this, &ok](auto name, auto&& field, auto index) {
            fieldName = QString::fromUtf8(name.data());
            if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
            fieldNum = index;
            auto copy = outNode;
            ok += write(field);
            outNode = copy;
        });

        outNode = outNode.parentNode();
        return ok;
    }
};
