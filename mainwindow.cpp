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
    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup("MainWindow");
    dir = settings.value("dir").toString();
    restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("State").toByteArray());
    ui->splitter->restoreState(settings.value("State").toByteArray());
    // = QFileDialog::getOpenFileName(this, {}, dir, "TopoR (*.fst)")
    QTimer::singleShot(100, [this] {
        Xml xml{dir};

        try {
            xml.read(file);
        } catch(const std::set<QString>& names) {
            qCritical() << names;
        } catch(...) {
        }
        // qInfo() << xml.byteArray.data();
        ui->plainTextEdit->appendPlainText(xml.byteArray);
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
        ui->treeView->collapseAll();

        connect(ui->treeView, &QTreeView::doubleClicked, [this](const QModelIndex& index) {
            ui->treeView->expandRecursively(index, 1);
        });

#if 1

        // for(auto&& footprint: file->localLibrary.Footprints)
        //     ui->graphicsView->addItem(file->localLibrary.footprintGi(footprint));

        for(auto&& CompInstance: file->componentsOnBoard.Components) {
            {
                auto item = file->localLibrary.getFootprint(CompInstance.footprintRef.name)
                                ->graphicsItem(*file);

                item->setTransform(CompInstance.transform());
                ui->graphicsView->addItem(item);
            }
            {
                auto item = file->localLibrary.getFootprint(CompInstance.footprintRef.name)
                                ->graphicsItem(*file);
            }

            // if(auto group = Footprints[CompInstance.FootprintRef_.name]; group) {
            //     for(var: group->childItems()) {
            //     }
            //     group = new QGraphicsItemGroup{group};
            //     group->setRotation(CompInstance.angle);
            //     group->setPos(CompInstance.org);
            //     ui->graphicsView->addItem(group);
            // }
        }
        // for(auto&& FreePad: file->ComponentsOnBoard_.FreePads) {
        //     if(auto group = Footprints[FreePad.PadstackRef_.name]; group) {
        //         group = new QGraphicsItemGroup{group};
        //         group->setRotation(FreePad.angle);
        //         group->setPos(FreePad.org);
        //         ui->graphicsView->addItem(group);
        //     }
        // }
#endif
        ui->graphicsView->zoomFit();
    });
}

MainWindow::~MainWindow() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("dir", dir);
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("State", saveState());
    settings.setValue("State", ui->splitter->saveState());
    delete ui;
}
