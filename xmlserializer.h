#pragma once

#include "TopoR_PCB_File.h"

#include "treeitem.h"

#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <QRegularExpression>

#include <boost/pfr.hpp>
#include <set>
#include <source_location>

namespace pfr = boost::pfr;
using namespace TopoR;
using sl = std::source_location;

template <typename R> concept Range = requires(R& r) { std::begin(r); std::end(r); };
template <typename T> concept Struct = !Range<T> && pfr::is_implicitly_reflectable_v<T, T>; //&& pfr::tuple_size_v<T>;
template <typename T> concept Numbers = std::is_arithmetic_v<T>;
template <typename T> concept Enums = std::is_enum_v<T>;
template <typename T> concept To = std::is_base_of_v<std::initializer_list<typename T::value_type>, T> == false || Struct<T>;

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
    mutable int fieldIndex{};
    bool isRead{};
    bool isArray{};
    bool isVariant{};
    bool isAarrayElem{};

    mutable bool isAttribute{};
    mutable QString fieldName;
    mutable QDomDocument outDoc;
    mutable QDomNode outNode;

    void save(const QString& dir);
    void debugNode() const;

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
            outNode.toElement().setAttribute(fieldName, str);
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
        value.replace(' ', '_'); // NOTE workaround for enumerations with spaces
        e = stringToEnum<T>(value.toStdString());
        return value.size();
    }

    template <Enums T> bool write(const T& e) const { // enum`ы
        auto str = QString::fromStdString(std::string{enumToString(e)});
        str.replace('_', ' '); // NOTE workaround for enumerations with spaces
        if(!str.size()) return false;
        if(isAttribute) {
            isAttribute = false;
            outNode.toElement().setAttribute(fieldName, str);
        } else {
            auto element = outDoc.createElement(fieldName);
            element.appendChild(outDoc.createTextNode(str));
            outNode.appendChild(element);
        }
        return true;
    }

    /// Optional
    template <typename T> bool read(Optional<T>& optional) { // перенаправление ↑↑↑
        if(T val; read(val)) optional = std::move(val);
        return optional.has_value();
    }

    template <typename T> bool write(const Optional<T>& optional) const { // перенаправление ↑↑↑
        if(optional) return write(*optional);
        return optional.has_value();
    }

    /// XmlAttr<T>
    template <typename T, bool Opt> bool read(XmlAttr<T, Opt>& attr) { // перенаправление ↑↑↑
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

    template <typename T, bool Opt> bool write(const XmlAttr<T, Opt>& attr) const { // перенаправление ↑↑↑
        if(!attr) return false;
        isAttribute = true;
        return write(attr.value);
    }

    /// XmlVariant<Ts...>
    template <typename... Ts> bool read(XmlVariant<Ts...>& variant) { // перенаправление ↑↑↑
        if(!node.isElement()) return false;
        // debugNode();
        int ctr{};
        auto reader = [&]<typename T>() {
            if(ctr) return;
            if(T val{}; node.toElement().tagName() == TypeName<T> && read(val)) {
                ++ctr, variant = std::move(val);
            } else {
                auto copy = node;
                node = node.firstChildElement(TypeName<T>);
                if(isVariant = true; !node.isNull() && read(val))
                    ++ctr, variant = std::move(val);
                isVariant = false;
                node = copy;
            }
        };
        (reader.template operator()<Ts>(), ...);
        assert(ctr < 2);
        return ctr > 0;
    }

    template <typename... Ts> bool write(const XmlVariant<Ts...>& variant) const { // перенаправление ↑↑↑
        if(!variant.has_value()) return false;
        return variant.visit([this](auto&& val) { return write(val); });
    }

    /// XmlArrayElem<T>
    template <typename T, typename CanSkip> bool read(XmlArrayElem<T, CanSkip>& vector) { // перенаправление ↑↑↑
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

    template <typename T, typename CanSkip> bool write(const XmlArrayElem<T, CanSkip>& vector) const { // перенаправление ↑↑↑
        if(vector.canSkip()) return false;                                                             // NOTE maybe true
        bool ok{true};
        outNode = outNode.appendChild(outDoc.createElement(fieldName));
        for(auto&& var: vector)
            ok &= write(var);
        outNode = outNode.parentNode();
        return ok;
    }

    /// XmlArray<T>
    template <typename T, typename CanSkip> bool read(XmlArray<T, CanSkip>& vector) { // перенаправление ↑↑↑
        if(node.isNull())
            return false;
        auto childNodes = node.childNodes();

        struct Range {
            int min{}, max{};
        };

        auto find = [this, &childNodes]<typename Type>(Tag<Type>) -> int {
            auto node_ = node.firstChildElement(TypeName<Type>);
            if(!node_.isNull())
                for(int index{}; index < childNodes.size(); ++index)
                    if(childNodes.at(index) == node_) return index;
            return ArrayNull;
        };

        auto index = Overload{
            [find]<typename... Ts>(Tag<XmlVariant<Ts...>>) -> int {
                std::array arr{find(Tag<Ts>{})...};
                return *std::ranges::min_element(arr);
            },
            find}(Tag<T>{});

        if(index == ArrayNull)
            return false;
        vector.resize(childNodes.size() - index);// FIXME range overflow попытка чтения в массив других типроы не принадлежащих ему
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

    template <typename T, typename CanSkip> bool write(const XmlArray<T, CanSkip>& vector) const { // перенаправление ↑↑↑
        if(vector.canSkip()) return false;                                                         // NOTE maybe true
        int ok{};
        for(auto&& var: vector) ok += write(var);
        return ok == vector.size();
    }

    /// Skip<T> пропуск поля
    template <typename T> bool read(Skip<T>&) { return true; }
    template <typename T> bool write(const Skip<T>&) const { return true; }

    /// Named<T>
    template <typename T, Name NAME> bool read(Named<T, NAME>& named) { // пропуск поля
        return read(*named, NAME);
    }

    template <typename T, Name NAME> bool write(const Named<T, NAME>& named) const { // пропуск поля
        return write(*named, NAME);
    }

public:
    template <Struct T> bool read(T& str, const QString& name = {}) { // чтение полей структуры
        if(TypeName<T> == "PlaneLayerNets") {
            // debugNode();
            qDebug();
        }
        const QString tagName = name.size() ? name : TypeName<T>;

        if(!isArray && !isVariant)
            node = (node.isNull() ? doc : node).firstChildElement(tagName);
        isArray = isVariant = false;

        dbgTree = dbgTree->addItem(new TreeItem{tagName, TypeName<T>, "", "", node.lineNumber()});
        int ok{};
        if constexpr(pfr::tuple_size_v<T>)
            pfr::for_each_field_with_name(str, [this, &ok](auto name, auto&& field, auto index) {
                fieldName = QString::fromUtf8(name.data());
                if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
                fieldIndex = index;
                auto copy = node;
                ok += read(field);
                node = copy;
            });
        else ok = 1;

        node = node.parentNode();
        dbgTree = dbgTree->parent();
        return ok;
    }

    template <Struct T> bool write(const T& str, const QString& name = {}) const { // чтение полей структуры
        if constexpr(requires { str.canSkip(); })
            if(str.canSkip()) return false;

        const QString tagName = name.size() ? name : TypeName<T>;

        outNode = outNode.isNull()
            ? outDoc.appendChild(outDoc.createElement(tagName))
            : outNode.appendChild(outDoc.createElement(tagName));

        int ok{};
        pfr::for_each_field_with_name(str, [this, &ok](auto name, auto&& field, auto index) {
            fieldName = QString::fromUtf8(name.data());
            if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
            fieldIndex = index;
            auto copy = outNode;
            ok += write(field);
            outNode = copy;
        });

        outNode = outNode.parentNode();
        return ok;
    }
};
