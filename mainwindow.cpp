#include "mainwindow.h"
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

static QGraphicsItem* graphicsItem(const LocalLibrary::Footprint* fp, const TopoR_PCB_File& file) {
    auto group = new QGraphicsItemGroup;
    LocalLibrary::footprints.emplace(fp->name, group);
    for(auto&& pad: fp->Pads) {
        if(auto padstack = file.localLibrary.getPadstack(pad.padstackRef.name); padstack) {
            QPainterPath path;
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

    for(auto&& detail: fp->Details) {
        auto item = new QGraphicsPathItem{detail.Figure.visit([](auto&& det) -> QPainterPath { return det; })};
        item->setPen({Qt::lightGray, detail.lineWidth < 1.0 ? 0.0 : detail.lineWidth});
        item->setZValue(10000);
        group->addToGroup(item);
    }

    for(auto&& label: fp->Labels) {
        if(auto textStyle = file.textStyles.getTextStyle(label.textStyleRef); textStyle) {
        }
    }

    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    return group;
}

void MainWindow::drawFile() {

    // for (auto&&var : file->dialogSettings.) {

    // }

    // colors

    drawComponents();
    drawWires();
    drawVias();
    drawBoardOutline();
    drawBoardOutlineVoids();

    ui->graphicsView->zoomFit();
}

void MainWindow::drawVias() {
    auto group = new QGraphicsItemGroup;
    for(auto&& via: file->connectivity.Vias) {
        auto viastack = file->localLibrary.getViastack(via.viastackRef.name);
        if(!viastack) continue;
        for(int hue{}; QPainterPath padShape: viastack->ViaPads) {
            padShape.addEllipse({}, viastack->holeDiameter * 0.5, viastack->holeDiameter * 0.5);
            auto item = new QGraphicsPathItem{padShape};
            int color = 240 / viastack->ViaPads.size() * hue++;
            item->setPen({QColor::fromHsv(color, 255, 255),
                0.0});
            item->setPos(via.org);
            group->addToGroup(item);
        }
    }
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ui->graphicsView->addItem(group);
}

void MainWindow::drawWires() {
    std::map<QString, int> layers;
    for(auto&& wire: file->connectivity.Wires)
        if(!layers.contains(wire.layerRef.name.value))
            layers.emplace(wire.layerRef.name.value, layers.size());

    for(auto&& wire: file->connectivity.Wires) {
        for(auto&& subwire: wire.Subwires) {
            int color = 240 / layers.size() * layers.at(wire.layerRef.name.value);
            ui->graphicsView->addItem(subwire.graphicsItem(QColor::fromHsv(color, 255, 255, 128)));
        }
    }
}

void MainWindow::drawBoardOutline() {
    for(auto&& contour: file->constructive.boardOutline.Contour_) {
        // QPainterPath path;
        if(contour.NonfilledFigure)
            ui->graphicsView->addItem(
                                new QGraphicsPathItem{
                                    contour.NonfilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
                ->setPen({Qt::yellow, contour.lineWidth});
        // contour.NonfilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        if(contour.FilledFigure)
            ui->graphicsView->addItem(
                                new QGraphicsPathItem{
                                    contour.FilledFigure.visit([](auto&& val) -> QPainterPath { return val; })})
                ->setPen({Qt::yellow, contour.lineWidth});
        // contour.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
    }
}

void MainWindow::drawBoardOutlineVoids() {

    for(auto&& void_: file->constructive.boardOutline.Voids) {
        QPainterPath path;
        if(void_.NonfilledFigure)
            void_.NonfilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        if(void_.FilledFigure)
            void_.FilledFigure.visit([&path](auto&& val) { val.drawTo(path); });
        ui->graphicsView->addItem(new QGraphicsPathItem{path})->setPen({Qt::gray, void_.lineWidth});
    }
}

void MainWindow::drawComponents() {
    for(auto&& CompInstance: file->componentsOnBoard.Components) {
        auto footprint = file->localLibrary.getFootprint(CompInstance.footprintRef.name);
        if(!footprint) continue;
        auto item = graphicsItem(footprint, *file);
        item->setTransform(CompInstance.transform());
        ui->graphicsView->addItem(item);
    }
}
