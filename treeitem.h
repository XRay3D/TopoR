#pragma once

#include <QVector>
#include <QVariant>

class TreeItem {
public:
    explicit TreeItem(const QVector<QVariant>& data, TreeItem* parent = nullptr);
    ~TreeItem();

    QVariant data(int column) const;
    TreeItem* child(int number);
    TreeItem* parent();
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    bool setData(int column, const QVariant& value);
    int childCount() const;
    int childNumber() const;
    int columnCount() const;

private:
    QVector<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem* parentItem;
};
