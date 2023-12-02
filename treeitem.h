#pragma once

#include <QVariant>
#include <QVector>

class TreeItem {
public:
    // explicit TreeItem(const QVector<QVariant>& data, TreeItem* parent = nullptr);
    // TreeItem(){};
    ~TreeItem();

    QVariant data(int column) const;
    TreeItem* child(int number);
    TreeItem* parent();
    // bool insertChildren(int position, int count, int columns);
    // bool insertColumns(int position, int columns);
    // bool removeChildren(int position, int count);
    // bool removeColumns(int position, int columns);
    bool setData(int column, const QVariant& value);
    int childCount() const;
    int childNumber() const;
    int columnCount() const;
    std::array<QVariant, 4> itemData;
    void addItem(TreeItem* item) {
        childItems.emplace_back(item)->parentItem = this;
    }

    std::vector<TreeItem*> childItems;

private:
    TreeItem* parentItem{};
};
