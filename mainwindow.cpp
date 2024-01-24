#include "mainwindow.h"
#include "listmodel.h"
#include "tablemodel.h"
#include "treemodel.h"
#include "ui_mainwindow.h"

#include <QAbstractTableModel>
#include <QDebug>
#include <QSettings>
#include <QtWidgets>
// #include <stacktrace>
// #define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
// #include <boost/stacktrace.hpp>
// #include <magicgetruntime.h>
// #include <unistd.h>
#include "TopoR_PCB_File.h"
using namespace TopoR;
// #include "xmlserializer.h"

#if COMPONENTSONBOARD && CONNECTIVITY && CONSTRUCTIVE && DIALOGSETTINGS && DISPLAYCONTROL && GROUPS && HEADER && HISPEEDRULES && LAYERS && LOCALLIBRARY && NETLIST && RULES && SETTINGS && TEXTSTYLES
#define ALL 1
#else
#define ALL 0
#endif
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , file{new TopoR::TopoR_PCB_File} {

    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup("MainWindow");
    dir = settings.value("dir").toString();
    restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("State").toByteArray());
    ui->splitter->restoreState(settings.value("State").toByteArray());
    if (!QFile::exists(dir))
        dir = QFileDialog::getOpenFileName(this, {}, dir, "TopoR (*.fst)");
    if (dir.size() && settings.value("dir").toString() != dir)
        settings.setValue("dir", dir);
    QTimer::singleShot(100, this, [this] {
        loadFile();
        drawFile();
    });

    auto toolBar = addToolBar("File");
    toolBar->setObjectName("toolBarFile");
    toolBar->addAction("Open", this, [this] {
        dir = QFileDialog::getOpenFileName(this, {}, dir, "TopoR (*.fst)");
        QSettings settings;
        settings.beginGroup("MainWindow");
        if (dir.size() && settings.value("dir").toString() != dir)
            settings.setValue("dir", dir);
        loadFile();
        ui->graphicsView->setScene(new QGraphicsScene{ui->graphicsView});
        drawFile();
    });

    toolBar->addAction("Zoom 100%", ui->graphicsView, &GraphicsView::zoom100);
    toolBar->addAction("Zoom Fit", ui->graphicsView, &GraphicsView::zoomFit);
    toolBar->addAction("Zoom In", ui->graphicsView, &GraphicsView::zoomIn);
    toolBar->addAction("Zoom Out", ui->graphicsView, &GraphicsView::zoomOut);
    toolBar->addAction("Zoom ToSelected", ui->graphicsView, &GraphicsView::zoomToSelected);
}

MainWindow::~MainWindow() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    // if(dir.size()) settings.setValue("dir", dir);
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("State", saveState());
    settings.setValue("State", ui->splitter->saveState());
    delete ui;
}

#if ALL

static QGraphicsItem* graphicsItem(const LocalLibrary::Footprint* fp, const TopoR_PCB_File& file) {
    auto group = new QGraphicsItemGroup;
    LocalLibrary::footprints.emplace(fp->name, group);
    for (auto&& pad: fp->Pads) {
        if (auto padstack = file.localLibrary.getPadstack(pad.padstackRef.name); padstack) {
            QPainterPath path;
            path.addEllipse({}, padstack->holeDiameter * 0.5, padstack->holeDiameter * 0.5);
            auto item = new QGraphicsPathItem{path};
            item->setPen({Qt::magenta, 0.0});
            item->setTransform(pad.transform());
            group->addToGroup(item);
            for (int hue{}; auto&& padShape: padstack->Pads) {
                auto path = padShape.visit([](auto&& pad) -> QPainterPath { return pad; });
                auto item = new QGraphicsPathItem{path};
                int color = 240 / padstack->Pads.size() * hue++;
                item->setPen({QColor::fromHsv(color, 255, 255),
                    0.0});
                item->setTransform(pad.transform());
                group->addToGroup(item);
            }
        }
    }

    for (auto&& detail: fp->Details) {
        auto item = new QGraphicsPathItem{detail.Figure.visit([](auto&& det) -> QPainterPath { return det; })};
        item->setPen({Qt::lightGray, detail.lineWidth < 1.0 ? 0.0 : detail.lineWidth});
        item->setZValue(10000);
        group->addToGroup(item);
    }

    for (auto&& label: fp->Labels) {

        if (auto textStyle = file.textStyles.getTextStyle(label.textStyleRef); textStyle) {
        }
    }
    group->setToolTip(fp->name);
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    return group;
}

void MainWindow::drawFile() {

    for (auto&& layerOptions: file->displayControl.LayersVisualOptions) {
        detailsColor[layerOptions.layerRef] = {layerOptions.colors.details};
        fixColor[layerOptions.layerRef] = {layerOptions.colors.fix};
        padsColor[layerOptions.layerRef] = {layerOptions.colors.pads};
        isDetailsVisible[layerOptions.layerRef] = +layerOptions.show.details;
        isPadsVisible[layerOptions.layerRef] = +layerOptions.show.pads;
        isVisible[layerOptions.layerRef] = +layerOptions.show.visible;
    }

    ui->tvContakts->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tvContakts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->lvStackUpLayers->setModel(new ListModel{file->layers.StackUpLayers,
        [](std::add_const_t<decltype(file->layers.StackUpLayers.front())>& val) { return val.name.value; },
        ui->lvStackUpLayers});
    ui->lvUnStackLayers->setModel(new ListModel{file->layers.UnStackLayers,
        [](std::add_const_t<decltype(file->layers.UnStackLayers.front())>& val) { return val.name.value; },
        ui->lvUnStackLayers});
    ui->lvLayerGroups->setModel(new ListModel{file->groups.LayerGroups,
        [](std::add_const_t<decltype(file->groups.LayerGroups.front())>& val) { return val.name.value; },
        ui->lvLayerGroups});
    ui->lvComponentsOnBoard->setModel(new ListModel{file->componentsOnBoard.Components,
        [](std::add_const_t<decltype(file->componentsOnBoard.Components.front())>& val) { return val.name + ": " + val.uniqueId; },
        ui->lvComponentsOnBoard});
    ui->lvComponents->setModel(new ListModel{file->localLibrary.Components,
        [](std::add_const_t<decltype(file->localLibrary.Components.front())>& val) { return val.name.value; },
        ui->lvComponents});
    ui->lvFootprints->setModel(new ListModel{file->localLibrary.Footprints,
        [](std::add_const_t<decltype(file->localLibrary.Footprints.front())>& val) { return val.name.value; },
        ui->lvFootprints});
    ui->cbxLayer->setDuplicatesEnabled(false);
    connect(ui->lvComponentsOnBoard->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](const QItemSelection& selected, const QItemSelection& /*deselected*/) {
        if (!selected.size()) return;
        auto id = selected.indexes().front().data().toString().split(':').front();
        auto it = std::ranges::find(file->componentsOnBoard.Components, id, &ComponentsOnBoard::CompInstance::name);
        if (it == file->componentsOnBoard.Components.end()) return;
        ui->lvComponentsAttr->setModel(new ListModel{it->Attributes,
            [](std::add_const_t<decltype(it->Attributes.front())>& val) { return val.name + " (" + val.value + ")"; },
            ui->lvComponentsAttr});

        ui->chbxLocked->setChecked(+it->fixed);
        auto sv = enumToString(it->side_.value);
        ui->cbxLayer->addItem(QByteArray{sv.data(), static_cast<int>(sv.size())});
        ui->cbxLayer->setCurrentText(QByteArray{sv.data(), static_cast<int>(sv.size())});
        ui->dsbxAngle->setValue(it->angle);
        ui->dsbxPosY->setValue(it->org.y);
        ui->dxbxPosX->setValue(it->org.x);

        auto component = file->localLibrary.getComponent(it->componentRef);

        ui->tvContakts->setModel(new TableModel{const_cast<LocalLibrary::Component*>(component)->Pins, ui->lvComponentsAttr});
    });

    drawComponents();
    drawWires();
    drawVias();
    drawBoardOutline();
    drawBoardOutlineVoids();
    drawFreePads();

    ui->graphicsView->zoomFit();
}

void MainWindow::drawVias() {
    auto group = new QGraphicsItemGroup;
    for (auto&& via: file->connectivity.Vias) {
        auto viastack = file->localLibrary.getViastack(via.viastackRef.name);
        if (!viastack) continue;
        for (int hue{}; QPainterPath padShape: viastack->ViaPads) {
            padShape.addEllipse({}, viastack->holeDiameter * 0.5, viastack->holeDiameter * 0.5);
            auto item = new QGraphicsPathItem{padShape};
            int color = 240 / viastack->ViaPads.size() * hue++;
            item->setPen({QColor::fromHsv(color, 255, 255), 0.0});
            item->setPos(via.org);
            group->addToGroup(item);
        }
    }
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ui->graphicsView->addItem(group);
}

void MainWindow::drawWires() {
    std::map<QString, int> layers;
    for (auto&& wire: file->connectivity.Wires)
        if (!layers.contains(wire.layerRef.name.value))
            layers.emplace(wire.layerRef.name.value, layers.size());

    for (auto&& wire: file->connectivity.Wires) {
        for (auto&& subwire: wire.Subwires) {
            int color = 240 / layers.size() * layers.at(wire.layerRef.name.value);
            ui->graphicsView->addItem(subwire.graphicsItem(QColor::fromHsv(color, 255, 255, 128)));
        }
    }
}

void MainWindow::drawBoardOutline() {
    for (auto&& contour: file->constructive.boardOutline.Contour_) {
        // QPainterPath path;
        if (contour.NonfilledFigure)
            ui->graphicsView->addItem(
                                new QGraphicsPathItem{
                                    contour.NonfilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
                ->setPen({Qt::yellow, contour.lineWidth});
        // contour.NonfilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        if (contour.FilledFigure)
            ui->graphicsView->addItem(
                                new QGraphicsPathItem{
                                    contour.FilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
                ->setPen({Qt::yellow, contour.lineWidth});
        // contour.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
    }
}

void MainWindow::drawBoardOutlineVoids() {
    for (auto&& void_: file->constructive.boardOutline.Voids) {
        QPainterPath path;
        if (void_.NonfilledFigure)
            void_.NonfilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        if (void_.FilledFigure)
            void_.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        ui->graphicsView->addItem(new QGraphicsPathItem{path})->setPen({Qt::gray, void_.lineWidth});
    }
}

void MainWindow::drawComponents() {
    for (auto&& CompInstance: file->componentsOnBoard.Components) {
        auto footprint = file->localLibrary.getFootprint(CompInstance.footprintRef.name);
        if (!footprint) continue;
        auto item = graphicsItem(footprint, *file);
        item->setTransform(CompInstance.transform());
        ui->graphicsView->addItem(item);
    }
}

void MainWindow::drawFreePads() {
    std::unordered_map<QString, QGraphicsItemGroup*> groups;
    for (auto&& pad: file->componentsOnBoard.FreePads) {
        auto padstack = file->localLibrary.getPadstack(pad.padstackRef);
        if (!padstack) continue;
        for (int hue{}; auto&& padShape: padstack->Pads) {
            auto ref = padShape.visit([](auto&& pad) { return pad.Reference.visit([](auto&& ref) -> QString { return ref; }); });
            if (!groups.contains(ref)) groups.emplace(ref, new QGraphicsItemGroup);
            auto path = padShape.visit([](auto&& pad) -> QPainterPath { return pad; });
            auto item = new QGraphicsPathItem{path};
            int color = 240 / padstack->Pads.size() * hue++;
            item->setPen({QColor::fromHsv(color, 255, 255), 0.0});
            item->setPen({padsColor[ref], 0.0});
            item->setTransform(pad.transform());
            groups[ref]->addToGroup(item);
            groups[ref]->setToolTip(ref);
        }
    }
    for (auto&& [key, group]: groups) {
        group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        ui->graphicsView->addItem(group);
    }
}
#else
void MainWindow::drawFile() { }
void MainWindow::drawVias() { }
void MainWindow::drawWires() { }
void MainWindow::drawBoardOutline() { }
void MainWindow::drawBoardOutlineVoids() { }
void MainWindow::drawComponents() { }
void MainWindow::drawFreePads() { }
#endif
