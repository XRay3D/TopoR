#pragma once

#include "lxmlser.hpp"
#include <QAbstractItemModel>

namespace meta = std ::meta;
using namespace std::string_view_literals;

struct TreeItem {
    TreeItem(TreeItem* parent = nullptr)
        : parent_{parent} {
        if(parent_) parent_->children.emplace_back(this);
    }

    virtual ~TreeItem() = default;

    virtual QVariant data(int column, int role) const {
        if(role == Qt::DisplayRole
            || role == Qt::EditRole
            || role == Qt::ToolTipRole)
            return data_[column].data();
        return {};
    }

    TreeItem* child(size_t number) {
        return (number >= children.size())
            ? nullptr
            : children.at(number).get();
    }

    TreeItem* parent() { return parent_; }

    virtual bool setData(int column, const QVariant& value) { return false; }

    ptrdiff_t childNumber() const {
        if(parent_)
            if(auto it = std::ranges::find(parent_->children, this, &std::unique_ptr<TreeItem>::get); it != parent_->children.end())
                return std::distance(parent_->children.begin(), it);
        return 0;
    }
    size_t columnCount() const { return data_.size(); }
    size_t size() const { return children.size(); }

    std::string_view& data(size_t i) { return data_[i]; }

protected:
    std::vector<std::unique_ptr<TreeItem>> children;
    std::array<std::string_view, 3> data_{"typeName"sv, "fieldName"sv};

    TreeItem* parent_{};

    enum {
        TypeName,
        FieldName
    };
};

template <typename T>
struct Item : TreeItem {
    T& val;
    Item(T& val, TreeItem* parent = nullptr)
        : TreeItem{parent}, val{val} {
        data_ = {display_string_of(^^T), ""sv};
        XML::Overload{
            [this]<XML::IsClass Ty>(Ty& arg) {
                template for(constexpr auto FIELD: members(^^Ty)) {
                    TreeItem* item = new Item<decltype(arg.[:FIELD:])>{arg.[:FIELD:], this};
                    item->data(FieldName) = display_string_of /*identifier_of*/ (FIELD);
                }
            },
            [this]<typename Ty>(std::vector<Ty>& arg) {
                for(auto&& var: arg) new Item<Ty>{var, this};
            },
            [this]<typename... Ts>(std::variant<Ts...>& arg) {
                arg.visit([this]<typename Ty>(Ty& arg) { new Item<Ty>{arg, this}; });
            },
            [this](std::string&) {
                data_[TypeName] = "string"sv;
            },
            []<typename Ty>(Ty&) {},
        }(val);
    }

    // TreeItem interface
    QVariant data(int column, int role) const override {
        if(column == 2) {
            if(role == Qt::DisplayRole || role == Qt::EditRole) {
                /**/ if constexpr(std::is_same_v<T, std::string>) {
                    return val.c_str();
                } else if constexpr(std::is_same_v<T, std::string_view>) {
                    return val.data();
                } else if constexpr(std::is_arithmetic_v<T>) {
                    return val;
                } else if constexpr(std::is_enum_v<T>) {
                    return XML::toString(val).data();
                }
            }
            if constexpr(std::is_same_v<T, std::string>) {
                if(role == Qt::BackgroundRole && val.front() == '#')
                    return QColor{val.c_str()};
            }
        }
        return TreeItem::data(column, role);
    }
    bool setData(int column, const QVariant& value) override {
        return TreeItem::setData(column, value);
    }

    static consteval auto members(meta::info info) {
        static constexpr auto CTX = meta::access_context::unprivileged();
        return std::define_static_array([info] consteval {
            auto members = nonstatic_data_members_of(info, CTX);
            [&members](this auto self, auto&& bases) -> void {
                for(meta::info base: bases | std::views::transform(meta::type_of)) {
                    self(bases_of(base, CTX));
                    members.append_range(meta::nonstatic_data_members_of(base, CTX));
                }
            }(bases_of(info, CTX));
            return members;
        }());
    }
};

// template <typename T> Item(T&) -> Item<T>;

struct TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    TreeModel(TreeItem* rootItem, QObject* parent = nullptr)
        : QAbstractItemModel{parent}
        , rootItem{rootItem} {
    }
    ~TreeModel() { delete rootItem; }

    QVariant data(const QModelIndex& index, int role) const override {
        if(index.isValid())
            return getItem(index)->data(index.column(), role);
        return {};
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
            return rootItem->data(section, role);
        return QAbstractItemModel::headerData(section, orientation, role);
    }

    QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override {
        if(parent.isValid() && parent.column()) return {};
        TreeItem* item = getItem(parent);
        if(!item) return {};
        item = item->child(row);
        if(item) return createIndex(row, column, item);
        return {};
    }
    QModelIndex parent(const QModelIndex& index) const override {
        if(!index.isValid()) return {};
        TreeItem* item = getItem(index);
        TreeItem* parent = item ? item->parent() : nullptr;
        if(parent == rootItem || !parent) return {};
        return createIndex(parent->childNumber(), 0, parent);
    }

    int rowCount(const QModelIndex& parent = {}) const override {
        if(parent.isValid() && parent.column()) return 0;
        TreeItem* item = getItem(parent);
        return item ? item->size() : 0;
    }

    int columnCount(const QModelIndex& /*parent*/ = {}) const override {
        return rootItem->columnCount();
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if(!index.isValid()) return Qt::NoItemFlags;
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if(role != Qt::EditRole) return false;
        TreeItem* item = getItem(index);
        const bool result = item->setData(index.column(), value);
        if(result) emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return result;
    }
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override {
        if(role != Qt::EditRole || orientation != Qt::Horizontal) return false;
        const bool result = rootItem->setData(section, value);
        if(result) emit headerDataChanged(orientation, section, section);
        return result;
    }

private:
    TreeItem* getItem(const QModelIndex& index) const {
        if(index.isValid())
            if(TreeItem* item = static_cast<TreeItem*>(index.internalPointer()))
                return item;
        return rootItem;
    }

    TreeItem* rootItem;
};
