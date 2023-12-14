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

void MainWindow::drawFile() { // for(auto&& footprint: file->localLibrary.Footprints)
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
            QPainterPath path;
            auto arc = [&path, this](bool ccw, /*const QPointF& p1,*/ const QPointF& p2, const QPointF& center) {
                const auto p1 = path.currentPosition();
                // double radius = sqrt(pow((center.x() - p1.x()), 2) + pow((center.y() - p1.y()), 2));
                // double start = atan2(p1.y() - center.y(), p1.x() - center.x());
                // double stop = atan2(p2.y() - center.y(), p2.x() - center.x());
                // const double sign[]{-1.0, +1.0};

                // if(!ccw && stop >= start)
                //     stop -= 2.0 * M_PI;
                // else if(ccw && stop <= start)
                //     stop += 2.0 * M_PI;

                // start = qRadiansToDegrees(start);
                // stop = qRadiansToDegrees(stop);

                // double angle = qAbs(stop - start);
                // angle *= sign[ccw];

                // path.arcTo(
                //     -radius + center.x(), -radius + center.y(), radius * 2, radius * 2,
                //     start, angle);
                // QPainterPath path_;
                // path_.moveTo(path.currentPosition());
                // path_.arcTo(
                //     -radius + center.x(), -radius + center.y(), radius * 2, radius * 2,
                //     start, angle);
                // auto item = new QGraphicsPathItem{path_};
                // // auto item = new QGraphicsEllipseItem{-r + center.x, -r + center.y, r * 2, r * 2};
                // item->setPen({Qt::green, 0.0});
                // item->setZValue(100000);
                // item->setToolTip(QString{"A1=%1\nA2=%2\n%3"}.arg(start).arg(stop).arg(angle));
                // ui->graphicsView->addItem(item);

                if(ccw) {
                    QLineF line1{center, p1};
                    QLineF line2{center, p2};
                    const auto a1 = line1.angle();
                    auto a2 = line2.angle();
                    const auto a = a2 - (qFuzzyIsNull(a1) ? 360. : a1);
                    const auto r = line1.length();
                    path.arcTo(
                        -r + center.x(), -r + center.y(), r * 2, r * 2,
                        a1, a);
                    QPainterPath path_;
                    path_.moveTo(p1);
                    path_.arcTo(
                        -r + center.x(), -r + center.y(), r * 2, r * 2,
                        a1, a);
                    auto item = new QGraphicsPathItem{path_};
                    // auto item = new QGraphicsEllipseItem{-r + center.x, -r + center.y, r * 2, r * 2};
                    item->setPen({Qt::green, 0.0});
                    item->setZValue(100000);
                    item->setToolTip(QString{"A1=%1\nA2=%2\n%3"}.arg(a1).arg(a2).arg(a));
                    ui->graphicsView->addItem(item);
                } else {
                    QLineF line1{center, p1};
                    QLineF line2{center, p2};
                    const auto a1 = line1.angle();
                    auto a2 = line2.angle();
                    auto a = a2 - a1;
                    // if(a < 0) a = 360 - a;
                    const auto r = line1.length();
                    path.arcTo(
                        -r + center.x(), -r + center.y(), r * 2, r * 2,
                        a1, a);
                    QPainterPath path_;
                    path_.moveTo(p1);
                    path_.arcTo(
                        -r + center.x(), -r + center.y(), r * 2, r * 2,
                        a1, a);
                    auto item = new QGraphicsPathItem{path_};
                    // auto item = new QGraphicsEllipseItem{-r + center.x, -r + center.y, r * 2, r * 2};
                    item->setPen({Qt::magenta, 0.0});
                    item->setZValue(100000);
                    item->setToolTip(QString{"A1=%1\nA2=%2\n%3"}.arg(a1).arg(a2).arg(a));
                    ui->graphicsView->addItem(item);
                }
            };

            path.moveTo(subwire.start);
            if(QPointF p{subwire.start}; p.isNull())
                qCritical() << p;
            for(auto&& track: subwire.Tracks) {
                track.visit(
                    [&path](const TrackLine& track) {
                        path.lineTo(track.end);
                    },
                    [&arc](const TrackArc& track) { // ccw
                        arc(true, track.end, track.center);
                    },
                    [&arc](const TrackArcCW& track) { // cw
                        arc(false, track.end, track.center);
                    });
            }
            auto item = new QGraphicsPathItem{path};
            int color = 240 / layers.size() * layers.at(wire.layerRef.name.value);
            item->setPen({QColor::fromHsv(color, 255, 255, 128),
                subwire.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
            ui->graphicsView->addItem(item);
        }
    }

    ui->graphicsView->zoomFit();
}
