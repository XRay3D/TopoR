#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TopoR_PCB_File.h"
#include <QFile>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TopoR_PCB_File file;

    QFile fIn(R"(C:\Users\bakiev\Documents\TopoR\Examples\Example_03\arz_2L.fst)");
    if (fIn.open(QFile::ReadOnly | QFile::Text))
        file.fromXml(fIn.readAll());

    QFile fOut(R"(C:\Users\bakiev\Documents\TopoR\Examples\Example_03\arz_2L_.fst)");
    if (fOut.open(QFile::WriteOnly | QFile::Text)) {
        fOut.write(R"(<?xml version="1.0" encoding="UTF-8"?>)");
        fOut.write("\r\n");
        fOut.write(file.toRawXml());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
