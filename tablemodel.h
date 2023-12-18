#pragma once

#include "Commons.h"
#include "xmlserializertypes.h"
#include <QAbstractTableModel>
#include <pfr.hpp> //

using namespace TopoR;

template <typename Data>
class TableModel : public QAbstractTableModel {
    // Q_OBJECT
    Data& data_;
    using DataType = std::decay_t<decltype(data_.front())>;
    static constexpr auto Size{pfr::tuple_size_v<DataType>};

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
        if (role == Qt::DisplayRole) {
            return [column = index.column(), this]<size_t... Is>(const auto& val, std::index_sequence<Is...>) {
                QVariant ret;
                auto readField = [column, &ret, this]<size_t I>(const auto& val, std::integral_constant<size_t, I>) {
                    if (column == I) ret = read(pfr::get<I>(val));
                };
                (readField(val, std::integral_constant<size_t, Is>{}), ...);
                return ret;
            }(data_[index.row()], std::make_index_sequence<Size>{});
        }
        return {};
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            return [section, this]<size_t... Is>(std::index_sequence<Is...>) {
                QString ret;
                (((section == Is)
                         ? ret = typeName(pfr::get<Is>(*data_.data())) + ",\n" + pfr::get_name<Is, DataType>().data()
                         : ret),
                    ...);
                return ret;
            }(std::make_index_sequence<Size>{});
        }
        return QAbstractTableModel::headerData(section, orientation, role);
    }

private:
    auto overload() const {
        return Overload{
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
                return QString::fromStdString(std::string{enumToString(e)});
            },
            [this]<typename T>(const std::optional<T>& optional) -> QVariant { // перенаправление ↑↑↑
                if (optional.has_value()) return read(optional.value());
                return {};
            },
            [this]<typename T>(const XmlAttr<T>& attr) -> QVariant { // перенаправление ↑↑↑
                return read(attr.value);
            },
            []<typename... Ts>(const XmlVariant<Ts...>& variant) -> QVariant { // перенаправление ↑↑↑
                return variant.visit([]<typename T>(const T&) { return typeName<T>(); });
            },
            []<typename T>(const XmlArrayElem<T>& vector) -> QVariant { // перенаправление ↑↑↑
                return QString{"Elem: %1[%2]"}.arg(typeName<T>()).arg(vector.size());
            },
            []<typename T>(const XmlArray<T>& vector) -> QVariant { // перенаправление ↑↑↑
                return QString{"Field: %1[%2]"}.arg(typeName<T>()).arg(vector.size());
            },
            []<typename T>(const T& str) -> QVariant // чтение полей структуры
                requires(std::is_class_v<T> && std::is_aggregate_v<T>)
            {
                return typeName(str);
            },
            };
    }

    template <typename T>
    QVariant read(const T& str) const { return overload()(str); }
};
