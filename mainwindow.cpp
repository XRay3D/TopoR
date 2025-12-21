#include "mainwindow.h"
#include "listmodel.h"
// #include "tablemodel.h"
// #include "treemodel.h"
#include "ui_mainwindow.h"

#include <QAbstractTableModel>
#include <QDebug>
#include <QSettings>
#include <QtWidgets>

#include "TopoR_PCB_File.h"
#include "tablemodel.h"
using namespace TopoR;

// #if COMPONENTSONBOARD && CONNECTIVITY && CONSTRUCTIVE && DIALOGSETTINGS && DISPLAYCONTROL && GROUPS && HEADER && HISPEEDRULES && LAYERS && LOCALLIBRARY && NETLIST && RULES && SETTINGS && TEXTSTYLES
#define ALL 1
// #else
// #define ALL 0
// #endif

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
    if(!QFile::exists(dir))
        dir = QFileDialog::getOpenFileName(this, {}, dir, "TopoR (*.fst)");
    if(dir.size() && settings.value("dir").toString() != dir)
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
        if(dir.size() && settings.value("dir").toString() != dir)
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

static QGraphicsItem* graphicsItem(const LocalLibrary::Footprint& fp, const TopoR_PCB_File& file) {
    auto group = new QGraphicsItemGroup;
    // file.LocalLibrary.Footprints.emplace(fp->name, group);
    for(auto&& pad: fp.Pads) {
        if(auto padstack = file.LocalLibrary.getPadstack(pad.PadstackRef.name); padstack) {
            QPainterPath path;
            if(padstack->holeDiameter)
                path.addEllipse({}, padstack->holeDiameter * 0.5, padstack->holeDiameter * 0.5);
            auto item = new QGraphicsPathItem{path};
            item->setPen({Qt::magenta, 0.0});
            item->setTransform(pad.transform());
            group->addToGroup(item);
            for(int hue{}; auto&& padShape: padstack->Pads) {
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

    for(auto&& detail: fp.Details) {
        auto item = new QGraphicsPathItem{detail.Figure.visit([](auto&& det) -> QPainterPath { return det; })};
        item->setPen({Qt::lightGray, detail.lineWidth < 1.0 ? 0.0 : detail.lineWidth});
        item->setZValue(10000);
        group->addToGroup(item);
    }

    for(auto&& label: fp.Labels) {

        if(auto textStyle = file.TextStyles.getTextStyle(label.TextStyleRef); textStyle) {
        }
    }
    group->setToolTip(fp.name.c_str());
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    return group;
}

void MainWindow::drawFile() {

    for(auto&& layerOptions: file->DisplayControl.LayersVisualOptions) {
        detailsColor[layerOptions.LayerRef] = {layerOptions.Colors.details.c_str()};
        fixColor[layerOptions.LayerRef] = {layerOptions.Colors.fix.c_str()};
        padsColor[layerOptions.LayerRef] = {layerOptions.Colors.pads.c_str()};
        isDetailsVisible[layerOptions.LayerRef] = +layerOptions.Show.details;
        isPadsVisible[layerOptions.LayerRef] = +layerOptions.Show.pads;
        isVisible[layerOptions.LayerRef] = +layerOptions.Show.visible;
    }

    ui->tvContakts->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tvContakts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->lvStackUpLayers->setModel(new ListModel{file->Layers.StackUpLayers,
        [](std::add_const_t<decltype(file->Layers.StackUpLayers.front())>& val) { return val.name; },
        ui->lvStackUpLayers});
    ui->lvUnStackLayers->setModel(new ListModel{file->Layers.UnStackLayers,
        [](std::add_const_t<decltype(file->Layers.UnStackLayers.front())>& val) { return val.name; },
        ui->lvUnStackLayers});
    ui->lvLayerGroups->setModel(new ListModel{file->Groups.LayerGroups,
        [](std::add_const_t<decltype(file->Groups.LayerGroups.front())>& val) { return val.name; },
        ui->lvLayerGroups});
    ui->lvComponentsOnBoard->setModel(new ListModel{file->ComponentsOnBoard.Components,
        [](std::add_const_t<decltype(file->ComponentsOnBoard.Components.front())>& val) { return val.name + ": " + val.uniqueId; },
        ui->lvComponentsOnBoard});
    ui->lvComponents->setModel(new ListModel{file->LocalLibrary.Components,
        [](std::add_const_t<decltype(file->LocalLibrary.Components.front())>& val) { return val.name; },
        ui->lvComponents});
    ui->lvFootprints->setModel(new ListModel{file->LocalLibrary.Footprints,
        [](std::add_const_t<decltype(file->LocalLibrary.Footprints.front())>& val) { return val.name; },
        ui->lvFootprints});
    ui->cbxLayer->setDuplicatesEnabled(false);
    connect(ui->lvComponentsOnBoard->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](const QItemSelection& selected, const QItemSelection& /*deselected*/) {
        if(!selected.size()) return;
        auto id = selected.indexes().front().data().toString().split(':').front().toStdString();
        auto it = std::ranges::find(file->ComponentsOnBoard.Components, id, &ComponentsOnBoard::CompInstance::name);
        if(it == file->ComponentsOnBoard.Components.end()) return;
        ui->lvComponentsAttr->setModel(new ListModel{it->Attributes,
            [](std::add_const_t<decltype(it->Attributes.front())>& val) { return val.name + " (" + val.value + ")"; },
            ui->lvComponentsAttr});

        ui->chbxLocked->setChecked(+it->fixed);
        auto sv = XML::toString(it->side);
        ui->cbxLayer->addItem(QByteArray{sv.data(), static_cast<int>(sv.size())});
        ui->cbxLayer->setCurrentText(QByteArray{sv.data(), static_cast<int>(sv.size())});
        ui->dsbxAngle->setValue(it->angle);
        ui->dsbxPosY->setValue(it->Org.y);
        ui->dxbxPosX->setValue(it->Org.x);

        auto component = file->LocalLibrary.getComponent(it->ComponentRef);
        if(component) {
            ui->tvContakts->setModel(new TableModel{const_cast<LocalLibrary::Component&>(*component).Pins, ui->lvComponentsAttr});
        }
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
    for(auto&& via: file->Connectivity.Vias) {
        auto viastack = file->LocalLibrary.getViastack(via.ViastackRef.name);
        if(!viastack) continue;
        for(int hue{}; QPainterPath padShape: viastack->ViaPads) {
            padShape.addEllipse({}, viastack->holeDiameter * 0.5, viastack->holeDiameter * 0.5);
            auto item = new QGraphicsPathItem{padShape};
            int color = 240 / viastack->ViaPads.size() * hue++;
            item->setPen({QColor::fromHsv(color, 255, 255), 0.0});
            item->setPos(via.Org);
            group->addToGroup(item);
        }
    }
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ui->graphicsView->addItem(group);
}

void MainWindow::drawWires() {
    std::map<std::string_view, int> Layers;
    for(auto&& wire: file->Connectivity.Wires)
        if(!Layers.contains(wire.LayerRef.name))
            Layers.emplace(wire.LayerRef.name, Layers.size());

    for(auto&& wire: file->Connectivity.Wires) {
        for(auto&& subwire: wire.Subwires) {
            int color = 240 / Layers.size() * Layers.at(wire.LayerRef.name);
            ui->graphicsView->addItem(subwire.graphicsItem(QColor::fromHsv(color, 255, 255, 128)));
        }
    }
}

void MainWindow::drawBoardOutline() {
    for(auto&& contour: file->Constructive.BoardOutline.Contour) {
        // QPainterPath path;
        // if(contour.NonfilledFigure)
        ui->graphicsView->addItem(
                            new QGraphicsPathItem{
                                contour.NonfilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
            ->setPen({Qt::yellow, contour.lineWidth});
        // contour.NonfilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        // if(contour.FilledFigure)
        // ui->graphicsView->addItem(
        //                     new QGraphicsPathItem{
        //                         contour.FilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
        //     ->setPen({Qt::yellow, contour.lineWidth});
        // contour.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
    }
}

void MainWindow::drawBoardOutlineVoids() {
    for(auto&& void_: file->Constructive.BoardOutline.Voids) {
        QPainterPath path;
        // if(void_.NonfilledFigure)
        void_.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        // if(void_.FilledFigure)
        void_.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        ui->graphicsView->addItem(new QGraphicsPathItem{path})->setPen({Qt::gray, void_.lineWidth});
    }
}

void MainWindow::drawComponents() {
    for(auto&& CompInstance: file->ComponentsOnBoard.Components) {
        auto footprint = file->LocalLibrary.getFootprint(CompInstance.FootprintRef.name);
        if(!footprint) continue;
        auto item = graphicsItem(*footprint, *file);
        item->setTransform(CompInstance.transform());
        ui->graphicsView->addItem(item);
    }
}

void MainWindow::drawFreePads() {
    std::unordered_map<std::string_view, QGraphicsItemGroup*> groups;
    for(auto&& pad: file->ComponentsOnBoard.FreePads) {
        auto padstack = file->LocalLibrary.getPadstack(pad.PadstackRef);
        if(!padstack) continue;
        for(int hue{}; auto&& padShape: padstack->Pads) {
            auto ref = padShape.visit([](auto&& pad) { return pad.Reference.visit(
                                                           [](auto&& ref) -> std::string_view { return ref; }

                                                           /*XML::Overload{
                                                               [](auto&& ref) -> std::string_view { return ref; },
                                                               [](XML::IsEnum auto ref) -> std::string_view { return XML::toString(ref); },
                                                           }*/

                                                       ); });
            if(!groups.contains(ref)) groups.emplace(ref, new QGraphicsItemGroup);
            auto path = padShape.visit([](auto&& pad) -> QPainterPath { return pad; });
            auto item = new QGraphicsPathItem{path};
            int color = 240 / padstack->Pads.size() * hue++;
            item->setPen({QColor::fromHsv(color, 255, 255), 0.0});
            item->setPen({padsColor[ref], 0.0});
            item->setTransform(pad.transform());
            groups[ref]->addToGroup(item);
            groups[ref]->setToolTip(ref.data());
        }
    }
    for(auto&& [key, group]: groups) {
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
