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

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , file{new TopoR_PCB_Classes::TopoR_PCB_File} {

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
    // dir = QFileDialog::getOpenFileName(this, {}, dir, "TopoR (*.fst)");
    if(dir.size() && settings.value("dir").toString() != dir)
        settings.setValue("dir", dir);
    QTimer::singleShot(100, [this] {
        Xml xml{dir};

        try {
            xml.read(*file);
        } catch(const std::set<QString>& names) {
            qCritical() << names;
        } catch(...) {
        }
        // qInfo() << xml.byteArray.data();
        // ui->plainTextEdit->appendPlainText(xml.byteArray);
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

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
        ui->treeView->setAlternatingRowColors(true);
        for(int column = 0; column < model->columnCount(); ++column)
            ui->treeView->resizeColumnToContents(column);
        // ui->treeView->collapseAll();

        connect(ui->treeView, &QTreeView::doubleClicked, [this](const QModelIndex& index) {
            ui->treeView->expandRecursively(index, 1);
        });

#if 0

        // for(auto&& footprint: file->localLibrary.Footprints)
        //     ui->graphicsView->addItem(file->localLibrary.footprintGi(footprint));

        for(auto&& CompInstance: file->componentsOnBoard.Components) {
            auto item = file->localLibrary.getFootprint(CompInstance.footprintRef.name)
                            ->graphicsItem(*file);

            item->setTransform(CompInstance.transform());
            ui->graphicsView->addItem(item);
        }

        for(auto&& wire: file->connectivity.Wires) {
            for(auto&& subwire: wire.Subwires) {
                QPainterPath path;
                path.moveTo(subwire.start);
                if(QPointF p{subwire.start}; p.isNull())
                    qCritical() << p;
                for(auto&& track: subwire.Tracks) {
                    track.visit(
                        [&path](const TrackLine& track) {
                            path.lineTo(track.end);
                            if(QPointF p{track.end}; p.isNull())
                                qCritical() << p;
                        },
                        [&path](const TrackArc& track) {
                            path.lineTo(track.center);
                            if(QPointF p{track.center}; p.isNull())
                                qCritical() << p;
                            path.lineTo(track.end);
                            if(QPointF p{track.end}; p.isNull())
                                qCritical() << p;
                        },
                        [&path](const TrackArcCW& track) {
                            path.lineTo(track.center);
                            if(QPointF p{track.center}; p.isNull())
                                qCritical() << p;
                            path.lineTo(track.end);
                            if(QPointF p{track.end}; p.isNull())
                                qCritical() << p;
                        });
                }
                auto item = new QGraphicsPathItem{path};
                item->setPen({
                    QColor{255, 0, 0, 128},
                    subwire.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin
                });
                ui->graphicsView->addItem(item);
            }
        }

#endif
        ui->graphicsView->zoomFit();
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
