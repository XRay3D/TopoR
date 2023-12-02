#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "TopoR_PCB_File.h"
#include "xmlserializer.h"
#include <QAbstractTableModel>
#include <QDebug>
#include <QSettings>
#include <QtWidgets>
#include <magicgetruntime.h>
#include <unistd.h>

using namespace TopoR_PCB_Classes;

template <>
QVariant toVariant(const TopoR_PCB_Classes::XmlAttr<QString>& val) {
    return QVariant::fromValue(val.value);
}

template <class T>
QVariant toVariant(const std::vector<T>& val) {
    return QVariant::fromValue(val.s);
}

template <typename T>
class Model : public QAbstractTableModel {
    T& data_;

public:
    Model(T& data, QObject* parent = nullptr)
        : QAbstractTableModel{parent}
        , data_{data} { }
    virtual ~Model() { }

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent) const override { return data_.size(); }

    int columnCount(const QModelIndex& parent) const override {
        return 3; // pfr::tuple_size_v<std::remove_cvref_t<decltype(data_.front())>>;
    }

    QVariant data(const QModelIndex& index, int role) const override {

        QString str;
        if(role == Qt::DisplayRole)
            // return get_at(data_[index.row()], index.column());
            switch(index.column()) {
            case 0:
                return data_[index.row()].name.value;
            case 1:
                // for(auto&& val: data_[index.row()].Attributes)
                //     str += val.name.value + '|';
                return str;
            case 2:
                // for(auto&& val: data_[index.row()].Attributes)
                //     str += val.value.value + '|';
                return str;
            default:
                break;
            }
        return {};
    }
};

template <typename T>
Model(T&, QObject*) -> Model<T>;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , file{new TopoR_PCB_Classes::TopoR_PCB_File} {
    ui->setupUi(this);

    Xml xml;

    try {
        xml.read(file);
    } catch(const std::set<QString>& names) {
        qCritical() << names;
    } catch(...) {
    }
    // qInfo() << xml.byteArray.data();

    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(new Model(file->LocalLibrary_.Footprints, ui->tableView));

    // auto graphicsView = new QGraphicsView{new QGraphicsScene};

    auto Padstack = [this](const QString& name) {
        for(auto&& Padstack: file->LocalLibrary_.Padstacks)
            if(name == Padstack.name) return Padstack;
        return LocalLibrary::Padstack{};
    };

    for(auto&& Footprint: file->LocalLibrary_.Footprints) {
        auto group = new QGraphicsItemGroup;
        for(auto&& pad: Footprint.Pads) {
            auto padstack = Padstack(pad.PadstackRef_.name);
            // qInfo() << pad.name << padstack.name << padstack.Pads.size() << pad.Org_;
            for(int hue{}; auto&& Pad: padstack.Pads) {
                auto item = std::visit([]<class T>(T& pad) -> QAbstractGraphicsShapeItem* {
                    QAbstractGraphicsShapeItem* item{};
                    if constexpr(std::is_same_v<T, LocalLibrary::PadCircle>)
                        item = new QGraphicsPathItem{pad};
                    if constexpr(std::is_same_v<T, LocalLibrary::PadOval>)
                        item = new QGraphicsPathItem{pad};
                    if constexpr(std::is_same_v<T, LocalLibrary::PadPoly>)
                        item = new QGraphicsPathItem{pad};
                    if constexpr(std::is_same_v<T, LocalLibrary::PadRect>)
                        item = new QGraphicsPathItem{pad};
                    return item;
                },
                    Pad);
                if(item) {
                    item->setPen({QColor::fromHsv(240 / padstack.Pads.size() * hue++, 255, 255), 0.0});
                    item->setRotation(pad.angle);
                    item->setPos(pad.Org_.x, pad.Org_.y);
                    group->addToGroup(item);
                }
            }
        }
        ui->graphicsView->addItem(group);
        group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    }

    ui->graphicsView->zoomFit();

    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("State").toByteArray());
    ui->splitter->restoreState(settings.value("State").toByteArray());
}

MainWindow::~MainWindow() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("State", saveState());
    settings.setValue("State", ui->splitter->saveState());
    delete ui;
}
