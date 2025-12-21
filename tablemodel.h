#pragma once

// #include "Commons.h"
// using namespace TopoR;
// #include "xmlserializertypes.h"

#include "lxmlser.hpp"
#include <QAbstractTableModel>
#include <boost/pfr.hpp>
#include <type_traits>

namespace pfr = boost::pfr;

template <typename Data>
struct TableModel : public QAbstractTableModel {
    // Q_OBJECT
    Data& data_;
    using DataType = std::decay_t<decltype(data_.front())>;
    static constexpr auto Size{pfr::tuple_size_v<DataType>};
    QVariant value_;

public:
    explicit TableModel(Data& data, QObject* parent = nullptr)
        : QAbstractTableModel{parent}
        , data_{data} {
    }

signals:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override {
        return data_.size();
    }
    int columnCount(const QModelIndex& parent) const override {
        return Size;
    }
    QVariant data(const QModelIndex& index, int role) const override {
        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return [column = index.column(), this]<size_t... Is>(const auto& val, std::index_sequence<Is...>) {
                QVariant ret;
                auto readField = [column, &ret, this]<size_t I>(const auto& val, std::integral_constant<size_t, I>) {
                    if(column == I) ret = get(pfr::get<I>(val));
                };
                (readField(val, std::integral_constant<size_t, Is>{}), ...);
                return ret;
            }(data_[index.row()], std::make_index_sequence<Size>{});
        return {};
    }
    bool setData(const QModelIndex& index, const QVariant& value, int role) override {
        if(role == Qt::EditRole) {
            value_ = value;
            return [column = index.column(), this]<size_t... Is>(auto& val, std::index_sequence<Is...>) {
                bool ret;
                auto readField = [column, &ret, this]<size_t I>(auto& val, std::integral_constant<size_t, I>) {
                    if(column == I) ret = set(pfr::get<I>(val));
                };
                (readField(val, std::integral_constant<size_t, Is>{}), ...);
                return ret;
            }(data_[index.row()], std::make_index_sequence<Size>{});
        }
        return {};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
            return [section, this]<size_t... Is>(std::index_sequence<Is...>) {
                QString ret;
                (((section == Is)
                         ? ret = display_string_of(^^decltype(pfr::get<Is>(*data_.data()))) + QByteArray{"\n"} + pfr::get_name<Is, DataType>().data()
                         : ret),
                    ...);
                return ret;
            }(std::make_index_sequence<Size>{});
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

private:
    auto get() const {
        return XML::Overload{
            [](const QString& str) -> QVariant { // Строки
                return str;
            },
            []<typename T>(const T& value) -> QVariant // float`ы int`ы
                requires std::is_arithmetic_v<T>
            {
                return value;
            },
            []<typename T>(const T& e) -> QVariant // enum`ы
                requires std::is_enum_v<T>
            {
                return QString::fromStdString(std::string{XML::toString(e)});
            },
            [this]<typename T>(const std::optional<T>& optional) -> QVariant { // перенаправление ↑↑↑
                if(optional.has_value()) return get(optional.value());
                return {};
            },
            [this]<typename T>(const[[= XML::Attr]] T& attr) -> QVariant { // перенаправление ↑↑↑
                return get(attr);
            },
            []<typename... Ts>(const std::variant<Ts...>& variant) -> QVariant { // перенаправление ↑↑↑
                return variant.visit([]<typename T>(const T&) { return display_string_of(^^T); });
            },
            []<typename T>(const[[= XML::Array]] std::vector<T>& vector) -> QVariant { // перенаправление ↑↑↑
                return QString{"Elem: %1[%2]"}.arg(display_string_of(^^T)).arg(vector.size());
            },
            // []<typename T>(const XML::Array<T>& vector) -> QVariant { // перенаправление ↑↑↑
            //     return QString{"Field: %1[%2]"}.arg(display_string_of(^^T)).arg(vector.size());
            // },
            []<typename T>(const T& str) -> QVariant // чтение полей структуры
                requires(std::is_class_v<T> && std::is_aggregate_v<T>)
            {
                return display_string_of(^^T).data();
            },
            };
    }

    auto set() {
        return XML::Overload{
            [this](QString& str) -> bool { // Строки
                return str = value_.toString(), true;
            },
            [this]<typename T>(T& value) -> bool // float`ы int`ы
                requires std::is_arithmetic_v<T>
            {
                return value = value_.value<T>(), true;
            },
            [this]<typename T>(T& e) -> bool // enum`ы
                requires std::is_enum_v<T>
            {
                auto E = enumToString<T>(value_.toString().toStdString());
                if(enumToString(E) == "!!!") return false;
                return e = E, true;
            },
            [this]<typename T>(std::optional<T>& optional) -> bool { // перенаправление ↑↑↑
                T val;
                if(set(val)) return optional = val, true;
                return false;
            },
            [this]<typename T>([[= XML::Attr]] T& attr) -> bool { // перенаправление ↑↑↑
                return set(attr);
            },
            []<typename... Ts>(std::variant<Ts...>& variant) -> bool { // перенаправление ↑↑↑
                return false;                                          // variant.visit([]<typename T>( T&) { return typeName<T>; });
            },
            []<typename T>(std::vector<T>& vector) -> bool { // перенаправление ↑↑↑
                return false;                                // QString{"Elem: %1[%2]"}.arg(typeName<T>).arg(vector.size());
            },
            // []<typename T>(XML::Array<T>& vector) -> bool { // перенаправление ↑↑↑
            //     return false;                               // QString{"Field: %1[%2]"}.arg(typeName<T>).arg(vector.size());
            // },
            []<typename T>(T& str) -> bool // чтение полей структуры
                requires(std::is_class_v<T> && std::is_aggregate_v<T>)
            {
                return false; // typeName(str);
            },
            };
    }

    template <typename T>
    QVariant get(const T& str) const {
        return get()(str);
    }

    template <typename T>
    bool set(T& str) {
        return set()(str);
    }
};
