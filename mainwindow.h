#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace TopoR_PCB_Classes {
struct TopoR_PCB_File;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    TopoR_PCB_Classes::TopoR_PCB_File* file;
};
