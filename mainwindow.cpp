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

    if(0) {
        QStringList files{
            "../TopoR/Commons.cpp",
            "../TopoR/Commons.h",
            "../TopoR/ComponentsOnBoard.cpp",
            "../TopoR/ComponentsOnBoard.h",
            "../TopoR/Connectivity.cpp",
            "../TopoR/Connectivity.h",
            "../TopoR/Constructive.cpp",
            "../TopoR/Constructive.h",
            "../TopoR/Coordinates.h",
            "../TopoR/DialogSettings.cpp",
            "../TopoR/DialogSettings.h",
            "../TopoR/DisplayControl.cpp",
            "../TopoR/DisplayControl.h",
            "../TopoR/Enums.h",
            "../TopoR/Groups.cpp",
            "../TopoR/Groups.h",
            "../TopoR/Header.cpp",
            "../TopoR/Header.h",
            "../TopoR/HiSpeedRules.cpp",
            "../TopoR/HiSpeedRules.h",
            "../TopoR/Layers.cpp",
            "../TopoR/Layers.h",
            "../TopoR/LocalLibrary.cpp",
            "../TopoR/LocalLibrary.h",
            "../TopoR/NetList.cpp",
            "../TopoR/NetList.h",
            "../TopoR/Rules.cpp",
            "../TopoR/Rules.h",
            "../TopoR/Settings.cpp",
            "../TopoR/Settings.h",
            "../TopoR/TextStyles.cpp",
            "../TopoR/TextStyles.h",
            "../TopoR/TopoR_PCB_File.cpp",
            "../TopoR/TopoR_PCB_File.h",
        };
        for(auto&& fileName: files) {
            QFile file(fileName);
            QString dataWr;
            bool fl{};
            if(file.open(QFile::ReadOnly)) {
                dataWr = file.readAll();
                while(dataWr.contains("\r\n\r\n"))
                    dataWr.replace("\r\n\r\n", "\r\n");
                // dataWr = data;
                // qWarning() << fileName;
                // for(auto&& [all /*, repCap, type, name*/]:
                //     ctre::multiline_range<R"(//.+(?:\r\n)+)">(data)) {
                //     // if(repCap.view().starts_with("XmlAttr"sv)) continue;
                //     auto rep = QString::fromStdString(all.str());
                //     fl = true;

                //     // auto rep = QString::fromStdString("XmlAttr<" + type.str() + "> " + name.str());
                //     qInfo() << rep;
                //     for(int i = 0; i < 5; ++i)
                //         rep.replace("\r\n\r\n", "\r\n");
                //     qInfo() << rep;
                //     // dataWr.replace(QString::fromStdString(repCap.str()), rep);
                // }
                file.close();
            }
            if(1 && file.open(QFile::WriteOnly)) {
                file.write(dataWr.toUtf8());
                file.close();
            }
        }
        exit(0);
    }
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

void MainWindow::drawFile() {
    // for(auto&& footprint: file->localLibrary.Footprints)
    //     ui->graphicsView->addItem(file->localLibrary.footprintGi(footprint));

    for(auto&& CompInstance: file->componentsOnBoard.Components) {
        auto footprint = file->localLibrary.getFootprint(CompInstance.footprintRef.name);
        if(!footprint) continue;
        auto item = footprint->graphicsItem(*file);
        item->setTransform(CompInstance.transform());
        ui->graphicsView->addItem(item);
    }

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

    ui->graphicsView->zoomFit();
}
