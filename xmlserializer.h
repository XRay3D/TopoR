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
    int fieldNum{};
    bool isRead{};
    bool isArray{};
    bool isVariant{};
    bool isAarrayElem{};

    QString fieldName;

private:
    template <typename T> struct Tag { };
    static constexpr auto ArrayNull = std::numeric_limits<int>::max();
#if 0
    inline auto overload() {
        return Overload{
            [this](QString& str) // Строки
            // [this]<typename T>(T& str)
            //     requires std::is_same_v<T, QString>
            {
                if(node.isElement()) {
                    node = node.firstChildElement(fieldName);
                    str = node.toElement().text();
                    node = node.parentNode();
                    auto tree_ = tree->addItem(new TreeItem);
                    tree_->itemData[Name] = fieldName;
                    tree_->itemData[Value] = str;
                    // tree_->itemData[IsAttr] = "Tag";
                    tree_->itemData[Type] = typeid(QString).name();
                    tree_->itemData[FLine] = node.lineNumber();
                } else if(node.isAttr()) {
                    str = node.nodeValue();
                    auto tree_ = tree->addItem(new TreeItem);
                    tree_->itemData[Name] = node.toAttr().name();
                    tree_->itemData[Value] = str;
                    tree_->itemData[IsAttr] = "Attr";
                    tree_->itemData[Type] = typeid(QString).name();
                    tree_->itemData[FLine] = node.parentNode().lineNumber();
                }
                return str.size();
            },
            [this]<typename T>(T& value) // float`ы int`ы
                requires std::is_arithmetic_v<T>
            {
                QString text;
                if(node.isElement()) {
                    auto element = node.toElement();
                    if(text = element.attribute(typeName<T>); text.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = typeName<T>;
                        tree_->itemData[Value] = text;
                        // tree->itemData[IsAttr] = "Tag";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.lineNumber();
                    } else if(text = element.attribute(fieldName); text.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = fieldName;
                        tree_->itemData[Value] = text;
                        // tree->itemData[IsAttr] = "Tag";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.lineNumber();
                    }
                } else if(node.isAttr()) {
                    if(text = node.nodeValue(); text.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = node.toAttr().name();
                        tree_->itemData[Value] = text;
                        tree_->itemData[IsAttr] = "Attr";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.parentNode().lineNumber();
                    }
                }
                value = QVariant{text}.value<T>();
                return text.size();
            },
            [this]<typename T>(T& e) // enum`ы
                requires std::is_enum_v<T>
            {
                QString value;
                if(node.isElement()) {
                    if(value = node.toElement().attribute(typeName<T>); value.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = fieldName;
                        tree_->itemData[Value] = value;
                        // tree_->itemData[IsAttr] = "Tag";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.lineNumber();
                    } else if(value = node.toElement().attribute(fieldName); value.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = fieldName;
                        tree_->itemData[Value] = value;
                        // tree_->itemData[IsAttr] = "Tag";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.lineNumber();
                    }
                } else if(node.isAttr()) {
                    if(value = node.nodeValue(); value.size()) {
                        auto tree_ = tree->addItem(new TreeItem);
                        tree_->itemData[Name] = node.toAttr().name();
                        tree_->itemData[Value] = value;
                        tree_->itemData[IsAttr] = "Attr";
                        tree_->itemData[Type] = typeName<T>;
                        tree_->itemData[FLine] = node.parentNode().lineNumber();
                    }
                }
                e = stringToEnum<T>(value.toStdString());
                return value.size();
            },
            [this]<typename T>(std::optional<T>& optional) { // перенаправление ↑↑↑
                T val;
                if(read(val)) optional = val;
                return optional.has_value();
            },
            [this]<typename T>(XmlAttr<T>& attr) { // перенаправление ↑↑↑
                auto attributes = node.attributes();
                if(attributes.contains(typeName<T>)) {
                    node = attributes.namedItem(typeName<T>);
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
            },
            [this]<typename... Ts>(XmlVariant<Ts...>& variant) { // перенаправление ↑↑↑
                int ctr{};
                if(!node.isElement()) return false;
                auto reader = [&]<typename T>(T&& val) {
                    if(ctr) return;
                    if(node.toElement().tagName() == typeName<T> && read(val)) {
                        ++ctr, variant = std::move(val);
                    } else {
                        auto copy = node;
                        node = node.firstChildElement(typeName<T>);
                        if(!node.isNull())
                            if(isVariant = true; read(val)) ++ctr, variant = std::move(val);
                        node = copy;
                    }
                };
                (reader(Ts{}), ...);
                assert(ctr < 2);
                return ctr > 0;
            },
            [this]<typename T>(XmlArrayElem<T>& vector) { // перенаправление ↑↑↑
                QDomNode node_ = node.firstChildElement(fieldName);
                if(node_.isNull())
                    return false;
                isAarrayElem = true;
                auto childNodes = node_.childNodes();
                if(!childNodes.size())
                    return false;
                tree = tree->addItem(new TreeItem);
                tree->itemData[Name] = fieldName;
                tree->itemData[Value] = childNodes.size();
                tree->itemData[Type] = typeName<T>;
                tree->itemData[FLine] = node.lineNumber();

                vector.resize(childNodes.size());

                bool ok{true};

                for(int index{}; auto&& var: vector) {
                    isArray = true;
                    node = childNodes.at(index++);
                    ok &= read(var);
                }

                isAarrayElem = false;
                tree = tree->parent();

                return ok;
            },
            [this]<typename T>(XmlArray<T>& vector) { // перенаправление ↑↑↑
                if(node.isNull())
                    return false;
                auto childNodes = node.childNodes();
                auto find = [&]<typename Type>(Tag<Type>) -> int {
                    auto node_ = node.firstChildElement(typeName<Type>());
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
                for(auto&& var: vector) {
                    isArray = true;
                    node = childNodes.at(index++);
                    ok &= read(var);
                }
                return ok;
            },

            [this]<typename T>(T& str)
                requires(std::is_class_v<T> && std::is_aggregate_v<T>)
            { // чтение полей структуры
                if(!isArray && !isVariant)
                    node = (node.isNull() ? doc : node).firstChildElement(typeName<T>);
                isArray = isVariant = false;

                tree = tree->addItem(new TreeItem);
                tree->itemData[Name] = typeName<T>;
                // tree->itemData[Value] = value;
                // tree->itemData[IsAttr] = "Tag";
                tree->itemData[Type] = typeName<T>;
                tree->itemData[FLine] = node.lineNumber();
#if 1
                auto readStr = [this]<typename Ty, size_t... Is>(Ty& str, std::index_sequence<Is...>) {
                    auto readField = [this]<size_t Index, typename FTy>(FTy& str, std::integral_constant<size_t, Index>) {
                        fieldName = pfr::get_name<Index, FTy>().data();
                        if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
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
#else
                bool ok = read(str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
#endif
                node = node.parentNode();
                tree = tree->parent();
                return ok;
            },
            };
    }
#else

    bool read(QString& str) // Строки
    // [this]<typename T>(T& str)
    //     requires std::is_same_v<T, QString>
    {
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
#if 1
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
#else
        bool ok = read(str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
#endif
        node = node.parentNode();
        tree = tree->parent();
        return ok;
    }

private:
#endif
#if 0
    template <size_t Index, typename T>
    bool readField(T& str) {
        fieldName = pfr::get_name<Index, T>().data();
        if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
        fieldNum = Index;
        auto copy = node;
        bool ok = read(pfr::get<Index>(str));
        node = copy;
        return ok;
    }

    template <typename T, size_t... Is>
    bool read(T& str, std::index_sequence<Is...>) {
        int ok{};
        ((ok += readField<Is>(str)), ...);
        return ok;
    }
#endif
    // template <typename T>
    // bool read(T& str) {
    //     return ImplXml::read(*this, str);
    // }

    enum {
        Name,
        Value,
        IsAttr,
        FLine,
        Type,
    };

public:
    // template <typename T>
    // bool read(T& str) { return read(str); }
    // bool read(T& str) { return overload()(str); }
};

// enum {
//     Name,
//     Value,
//     IsAttr,
//     FLine,
//     Type,
// };

// // template <typename T>
// // bool Xml::read(T& str) {
// //     return ImplXml::read(*this, str);
// // }

// template <typename T>
//     requires std::is_enum_v<T>
// inline bool Xml::read(T& e) {
//     QString value;
//     if(node.isElement()) {
//         if(value = node.toElement().attribute(typeName<T>); value.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = fieldName;
//             tree->itemData[Value] = value;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.lineNumber();
//         } else if(value = node.toElement().attribute(fieldName); value.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = fieldName;
//             tree->itemData[Value] = value;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.lineNumber();
//         }
//     } else if(node.isAttr()) {
//         if(value = node.nodeValue(); value.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = node.toAttr().name();
//             tree->itemData[Value] = value;
//             tree->itemData[IsAttr] = "Attr";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.parentNode().lineNumber();
//         }
//     }
//     e = stringToEnum<T>(value.toStdString());
//     return value.size();
// }

// template <typename T>
// inline bool Xml::read(std::optional<T>& optional) { // FIXME check contains tag/attribute
//     T val;
//     if(read(val)) optional = val;
//     return optional.has_value();
// }

// template <typename T>
// inline bool Xml::read(XmlAttr<T>& attr) {
//     auto attributes = node.attributes();
//     if(attributes.contains(typeName<T>)) {
//         node = attributes.namedItem(typeName<T>);
//         bool ok = read(attr.value);
//         node = node.parentNode();
//         return ok;
//     } else if(attributes.contains(fieldName)) {
//         node = attributes.namedItem(fieldName);
//         bool ok = read(attr.value);
//         node = node.parentNode();
//         return ok;
//     }
//     return {};
// }

// template <typename... Ts>
// inline bool Xml::read(XmlVariant<Ts...>& variant) { // FIXME variant
//     int ctr{};
//     if(!node.isElement()) return {};
//     auto reader = [&]<typename T>(T&& val) {
//         if(ctr) return;
//         if(node.toElement().tagName() == typeName<T> && read(val)) {
//             ++ctr, variant = std::move(val);
//         } else {
//             auto copy = node;
//             node = node.firstChildElement(typeName<T>);
//             if(!node.isNull())
//                 if(isVariant = true; read(val)) ++ctr, variant = std::move(val);
//             node = copy;
//         }
//     };
//     (reader(Ts{}), ...);
//     assert(ctr < 2);
//     return ctr > 0;
// }

// template <typename T>
// inline bool Xml::read(XmlArrayElem<T>& vector) { // FIXME vector
//     QDomNode node_ = node.firstChildElement(fieldName);
//     if(node_.isNull())
//         return false;
//     isAarrayElem = true;
//     auto childNodes = node_.childNodes();
//     if(!childNodes.size())
//         return false;

//     tree = this->tree->addItem(new TreeItem);
//     tree->itemData[Name] = fieldName;
//     tree->itemData[Value] = childNodes.size();
//     tree->itemData[Type] = typeName<T>;
//     tree->itemData[FLine] = node.lineNumber();

//     vector.resize(childNodes.size());

//     bool ok{true};

//     for(int index{}; auto&& var: vector) {
//         isArray = true;
//         node = childNodes.at(index++);
//         ok &= read(var);
//     }

//     isAarrayElem = false;
//     tree = this->tree->parent();

//     return ok;
// }

// constexpr auto ArrayNull = std::numeric_limits<int>::max();

// template <typename T>
// struct Tag { };

// template <typename T>
// inline bool Xml::read(XmlArray<T>& vector) {
//     if(node.isNull())
//         return false;

//     auto childNodes = node.childNodes();

//     auto find = [&]<typename Ty>(Tag<Ty>) -> int {
//         auto node_ = node.firstChildElement(typeName<Ty>());
//         if(!node_.isNull())
//             for(int index{}; index < childNodes.size(); ++index)
//                 if(childNodes.at(index) == node_) return index;
//         return ArrayNull;
//     };

//     auto index = Overload{
//         [&]<typename... Ts>(Tag<XmlVariant<Ts...>>) -> int {
//             std::array arr{find(Tag<Ts>{})...};
//             return *std::ranges::min_element(arr);
//         },
//         find}(Tag<T>{});

//     if(index == ArrayNull)
//         return false;

//     vector.resize(childNodes.size() - index);

//     if(vector.empty())
//         return false;

//     bool ok{true};

//     for(auto&& var: vector) {
//         isArray = true;
//         node = childNodes.at(index++);
//         ok &= read(var);
//     }

//     return ok;
// }

// template <>
// inline bool Xml::read(QString& str) {
//     if(node.isElement()) {
//         node = node.firstChildElement(fieldName);
//         str = node.toElement().text();
//         node = node.parentNode();
//         auto tree = this->tree->addItem(new TreeItem);
//         tree->itemData[Name] = fieldName;
//         tree->itemData[Value] = str;
//         // tree->itemData[IsAttr] = "Tag";
//         tree->itemData[Type] = typeid(QString).name();
//         tree->itemData[FLine] = node.lineNumber();
//     } else if(node.isAttr()) {
//         str = node.nodeValue();
//         auto tree = this->tree->addItem(new TreeItem);
//         tree->itemData[Name] = node.toAttr().name();
//         tree->itemData[Value] = str;
//         tree->itemData[IsAttr] = "Attr";
//         tree->itemData[Type] = typeid(QString).name();
//         tree->itemData[FLine] = node.parentNode().lineNumber();
//     }

//     return str.size();
// }

// template <typename T>
//     requires std::is_arithmetic_v<T>
// inline bool Xml::read(T& value) {
//     QString text;
//     if(node.isElement()) {
//         if(text = node.toElement().attribute(typeName<T>); text.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = typeName<T>;
//             tree->itemData[Value] = text;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.lineNumber();
//         } else if(text = node.toElement().attribute(fieldName); text.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = fieldName;
//             tree->itemData[Value] = text;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.lineNumber();
//         }
//     } else if(node.isAttr()) {
//         if(text = node.nodeValue(); text.size()) {
//             auto tree = this->tree->addItem(new TreeItem);
//             tree->itemData[Name] = node.toAttr().name();
//             tree->itemData[Value] = text;
//             tree->itemData[IsAttr] = "Attr";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = node.parentNode().lineNumber();
//         }
//     }
//     value = QVariant{text}.value<T>();
//     return text.size();
// }

// template <typename T>
//     requires(std::is_class_v<T> && std::is_aggregate_v<T>)
// inline bool Xml::read(T& str) { // pod structures
//     if(!isArray && !isVariant)
//         node = (node.isNull() ? doc : node).firstChildElement(typeName<T>);
//     isArray = isVariant = false;

//     tree = this->tree->addItem(new TreeItem);
//     tree->itemData[Name] = typeName<T>;
//     // tree->itemData[Value] = value;
//     // tree->itemData[IsAttr] = "Tag";
//     tree->itemData[Type] = typeName<T>;
//     tree->itemData[FLine] = node.lineNumber();

//     bool ok = read(str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
//     node = node.parentNode();
//     tree = this->tree->parent();
//     return ok;
// }

// template <typename T, size_t... Is>
// inline bool Xml::read(T& str, std::index_sequence<Is...>) {
//     int ok{};
//     ((ok += readField<Is>(str)), ...);
//     return ok;
// }

// template <size_t Is, typename T>
// inline bool Xml::readField(T& str) {
//     fieldName = pfr::get_name<Is, T>().data();
//     if(fieldName.endsWith('_')) fieldName.resize(fieldName.size() - 1);
//     fieldNum = Is;
//     auto copy = node;
//     bool ok = read(pfr::get<Is>(str));
//     node = copy;
//     return ok;
// }

// template <typename T>
//     requires(!std::is_class_v<T> && !std::is_aggregate_v<T>)
// inline bool Xml::read(T& str) {
//     qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>;
//     return false;
// }

// template <typename T>
//     requires(std::is_polymorphic_v<T>)
// inline bool Xml::read(T& str) {
//     qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>;
//     return false;
// }

// namespace ImplXml {

// template <>
// inline bool read(Xml& xml,QString& str) {
//     if(xml.node.isElement()) {
//         xml.node = xml.node.firstChildElement(xml.fieldName);
//         str = xml.node.toElement().text();
//         xml.node = xml.node.parentNode();
//         auto tree = xml.tree->addItem(new TreeItem);
//         tree->itemData[Name] = xml.fieldName;
//         tree->itemData[Value] = str;
//         // tree->itemData[IsAttr] = "Tag";
//         tree->itemData[Type] = typeid(QString).name();
//         tree->itemData[FLine] = xml.node.lineNumber();
//     } else if(xml.node.isAttr()) {
//         str = xml.node.nodeValue();
//         auto tree = xml.tree->addItem(new TreeItem);
//         tree->itemData[Name] = xml.node.toAttr().name();
//         tree->itemData[Value] = str;
//         tree->itemData[IsAttr] = "Attr";
//         tree->itemData[Type] = typeid(QString).name();
//         tree->itemData[FLine] = xml.node.parentNode().lineNumber();
//     }

//     return str.size();
// }

// template <typename T>
//     requires std::is_arithmetic_v<T>
// inline bool read(Xml& xml, T& value) {
//     QString text;
//     if(xml.node.isElement()) {
//         if(text = xml.node.toElement().attribute(typeName<T>); text.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = typeName<T>;
//             tree->itemData[Value] = text;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.lineNumber();
//         } else if(text = xml.node.toElement().attribute(xml.fieldName); text.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = xml.fieldName;
//             tree->itemData[Value] = text;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.lineNumber();
//         }
//     } else if(xml.node.isAttr()) {
//         if(text = xml.node.nodeValue(); text.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = xml.node.toAttr().name();
//             tree->itemData[Value] = text;
//             tree->itemData[IsAttr] = "Attr";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.parentNode().lineNumber();
//         }
//     }
//     value = QVariant{text}.value<T>();
//     return text.size();
// }

// template <typename T>
//     requires std::is_enum_v<T>
// inline bool read(Xml& xml, T& e) {
//     QString value;
//     if(xml.node.isElement()) {
//         if(value = xml.node.toElement().attribute(typeName<T>); value.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = xml.fieldName;
//             tree->itemData[Value] = value;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.lineNumber();
//         } else if(value = xml.node.toElement().attribute(xml.fieldName); value.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = xml.fieldName;
//             tree->itemData[Value] = value;
//             // tree->itemData[IsAttr] = "Tag";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.lineNumber();
//         }
//     } else if(xml.node.isAttr()) {
//         if(value = xml.node.nodeValue(); value.size()) {
//             auto tree = xml.tree->addItem(new TreeItem);
//             tree->itemData[Name] = xml.node.toAttr().name();
//             tree->itemData[Value] = value;
//             tree->itemData[IsAttr] = "Attr";
//             tree->itemData[Type] = typeName<T>;
//             tree->itemData[FLine] = xml.node.parentNode().lineNumber();
//         }
//     }
//     e = stringToEnum<T>(value.toStdString());
//     return value.size();
// }

// template <typename T>
// inline bool read(Xml& xml, std::optional<T>& optional) { // FIXME check contains tag/attribute
//     T val;
//     if(read(xml, val)) optional = val;
//     return optional.has_value();
// }

// template <typename T>
// inline bool read(Xml& xml, XmlAttr<T>& attr) {
//     auto attributes = xml.node.attributes();
//     if(attributes.contains(typeName<T>)) {
//         xml.node = attributes.namedItem(typeName<T>);
//         bool ok = read(xml, attr.value);
//         xml.node = xml.node.parentNode();
//         return ok;
//     } else if(attributes.contains(xml.fieldName)) {
//         xml.node = attributes.namedItem(xml.fieldName);
//         bool ok = read(xml, attr.value);
//         xml.node = xml.node.parentNode();
//         return ok;
//     }
//     return {};
// }

// template <typename... Ts>
// inline bool read(Xml& xml, XmlVariant<Ts...>& variant) { // FIXME variant
//     int ctr{};
//     if(!xml.node.isElement()) return {};
//     auto reader = [&]<typename T>(T&& val) {
//         if(ctr) return;
//         if(xml.node.toElement().tagName() == typeName<T> && read(xml, val)) {
//             ++ctr, variant = std::move(val);
//         } else {
//             auto copy = xml.node;
//             xml.node = xml.node.firstChildElement(typeName<T>);
//             if(!xml.node.isNull())
//                 if(xml.isVariant = true; read(xml, val)) ++ctr, variant = std::move(val);
//             xml.node = copy;
//         }
//     };
//     (reader(Ts{}), ...);
//     assert(ctr < 2);
//     return ctr > 0;
// }

// template <typename T>
// inline bool read(Xml& xml, XmlArrayElem<T>& vector) { // FIXME vector
//     QDomNode node = xml.node.firstChildElement(xml.fieldName);
//     if(node.isNull())
//         return false;
//     xml.isAarrayElem = true;
//     auto childNodes = node.childNodes();
//     if(!childNodes.size())
//         return false;

//     xml.tree = xml.tree->addItem(new TreeItem);
//     xml.tree->itemData[Name] = xml.fieldName;
//     xml.tree->itemData[Value] = childNodes.size();
//     xml.tree->itemData[Type] = typeName<T>;
//     xml.tree->itemData[FLine] = xml.node.lineNumber();

//     vector.resize(childNodes.size());

//     bool ok{true};

//     for(int index{}; auto&& var: vector) {
//         xml.isArray = true;
//         xml.node = childNodes.at(index++);
//         ok &= read(xml, var);
//     }

//     xml.isAarrayElem = false;
//     xml.tree = xml.tree->parent();

//     return ok;
// }

// constexpr auto ArrayNull = std::numeric_limits<int>::max();

// template <typename T>
// struct Tag { };

// template <typename T>
// inline bool read(Xml& xml, XmlArray<T>& vector) {
//     if(xml.node.isNull())
//         return false;

//     auto childNodes = xml.node.childNodes();

//     auto find = [&]<typename Ty>(Tag<Ty>) -> int {
//         auto node = xml.node.firstChildElement(typeName<Ty>());
//         if(!node.isNull())
//             for(int index{}; index < childNodes.size(); ++index)
//                 if(childNodes.at(index) == node) return index;
//         return ArrayNull;
//     };

//     auto index = Overload{
//         [&]<typename... Ts>(Tag<XmlVariant<Ts...>>) -> int {
//             std::array arr{find(Tag<Ts>{})...};
//             return *std::ranges::min_element(arr);
//         },
//         find}(Tag<T>{});

//     if(index == ArrayNull)
//         return false;

//     vector.resize(childNodes.size() - index);

//     if(vector.empty())
//         return false;

//     bool ok{true};

//     for(auto&& var: vector) {
//         xml.isArray = true;
//         xml.node = childNodes.at(index++);
//         ok &= read(xml, var);
//     }

//     return ok;
// }

// template <typename T>
//     requires(std::is_class_v<T> && std::is_aggregate_v<T>)
// inline bool read(Xml& xml, T& str) { // pod structures
//     if(!xml.isArray && !xml.isVariant)
//         xml.node = (xml.node.isNull() ? xml.doc : xml.node).firstChildElement(typeName<T>);
//     xml.isArray = xml.isVariant = false;

//     xml.tree = xml.tree->addItem(new TreeItem);
//     xml.tree->itemData[Name] = typeName<T>;
//     // xml.tree->itemData[Value] = value;
//     // xml.tree->itemData[IsAttr] = "Tag";
//     xml.tree->itemData[Type] = typeName<T>;
//     xml.tree->itemData[FLine] = xml.node.lineNumber();

//     bool ok = read(xml, str, std::make_index_sequence<pfr::tuple_size_v<T>>{});
//     xml.node = xml.node.parentNode();
//     xml.tree = xml.tree->parent();
//     return ok;
// }

// template <typename T, size_t... Is>
// inline bool read(Xml& xml, T& str, std::index_sequence<Is...>) {
//     int ok{};
//     ((ok += readField<Is>(xml, str)), ...);
//     return ok;
// }

// template <size_t Is, typename T>
// inline bool readField(Xml& xml, T& str) {
//     xml.fieldName = pfr::get_name<Is, T>().data();
//     if(xml.fieldName.endsWith('_')) xml.fieldName.resize(xml.fieldName.size() - 1);
//     xml.fieldNum = Is;
//     auto copy = xml.node;
//     bool ok = read(xml, pfr::get<Is>(str));
//     xml.node = copy;
//     return ok;
// }

// template <typename T>
//     requires(!std::is_class_v<T> && !std::is_aggregate_v<T>)
// inline bool read(Xml& xml, T& str) {
//     qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>;
//     return false;
// }

// template <typename T>
//     requires(std::is_polymorphic_v<T>)
// inline bool read(Xml& xml, T& str) {
//     qCritical() << "!!!ERR!!!" << sl::current().function_name() << typeName<T>;
//     return false;
// }

// } // namespace ImplXml
