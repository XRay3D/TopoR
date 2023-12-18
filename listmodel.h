#pragma once

#include <QAbstractListModel>
template <typename T, typename Proj>
class ListModel : public QAbstractListModel {
    // Q_OBJECT
    T& data_;
    Proj proj;

public:
    explicit ListModel(T& data, Proj&& proj, QObject* parent = nullptr)
        : QAbstractListModel{parent}
        , data_{data}
        , proj{std::forward<Proj>(proj)} { }
    ~ListModel() { qWarning(__FUNCTION__); }

    // QAbstractItemModel interface

    int rowCount(const QModelIndex& parent) const override {
        return data_.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if(role == Qt::DisplayRole)
            return proj(data_.at(index.row()));
        return {};
    }
};
