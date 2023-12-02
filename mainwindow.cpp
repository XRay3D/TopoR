#include "mainwindow.h"
#include "treemodel.h"
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
    int columnCount_{1};

public:
    Model(T& data, QObject* parent = nullptr)
        : QAbstractTableModel{parent}
        , data_{data} {

        for(NetList::Net& net: data_)
            if(columnCount_ < net.refs.size())
                columnCount_ = net.refs.size();
        columnCount_ += 1;
    }
    virtual ~Model() { }

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent) const override { return data_.size(); }

    int columnCount(const QModelIndex& parent) const override {
        return columnCount_; // pfr::tuple_size_v<std::remove_cvref_t<decltype(data.front())>>;
    }

    QVariant data(const QModelIndex& index, int role) const override {
        QString str;
        NetList::Net& net = data_[index.row()];

        if(role == Qt::DisplayRole)
            // return get_at(data_[index.row()], index.column());
            switch(index.column()) {
            case 0:
                return {net.name};
            default:
                if(index.column() <= net.refs.size())
                    return net.refs[index.column() - 1].visit(
                        Overload{
                            [](const PinRef& ref) -> QVariant {
                                return {ref.compName + "{" + ref.pinName + "}"};
                            },
                            [](const PadRef& ref) -> QVariant {
                                return {ref.compName + "{" + ref.padNum + "}"};
                            }});
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
    ui->plainTextEdit->appendPlainText(xml.byteArray);

    connect(new QLineEdit{ui->plainTextEdit}, &QLineEdit::textEdited, [this](const QString& str) {
        if(!ui->plainTextEdit->find(str)) {
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            ui->plainTextEdit->find(str);
        }
    });

    const QStringList headers({tr("Title"), tr("Description")});
    TreeModel* model = new TreeModel{xml.item, headers, this};

    ui->treeView->setModel(model);
    ui->treeView->expandAll();
    for(int column = 0; column < model->columnCount(); ++column)
        ui->treeView->resizeColumnToContents(column);

    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setModel(new Model(file->NetList_.Nets, ui->tableView));

    // auto graphicsView = new QGraphicsView{new QGraphicsScene};

    auto Padstack = [this](const QString& name) {
        for(auto&& Padstack: file->LocalLibrary_.Padstacks)
            if(name == Padstack.name) return Padstack;
        return LocalLibrary::Padstack{};
    };

    ui->treeView->setModel(model);
    for(int column = 0; column < model->columnCount(); ++column)
        ui->treeView->resizeColumnToContents(column);

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
