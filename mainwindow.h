#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace TopoR {
struct TopoR_PCB_File;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    TopoR::TopoR_PCB_File* file;
    QString dir;

    std::unordered_map<QStringView, QColor> colors;

    void loadFile();
    void drawFile();
    void drawVias();
    void drawWires();
    void drawBoardOutline();
    void drawBoardOutlineVoids();
    void drawComponents();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
    // void draw();
};
