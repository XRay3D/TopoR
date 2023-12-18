#pragma once

#include <QMainWindow>
#include <QMap>

class QGraphicsItemGroup;
namespace Ui {
class MainWindow;
}

namespace TopoR {
struct TopoR_PCB_File;
} // namespace TopoR

struct QGraphicsItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // private:
    Ui::MainWindow* ui;
    TopoR::TopoR_PCB_File* file;
    QString dir;

    QMap<QString, QColor> detailsColor;
    QMap<QString, QColor> fixColor;
    QMap<QString, QColor> padsColor;

    std::unordered_map<QString, QGraphicsItemGroup*> lauerGroups;

    QMap<QString, bool> isDetailsVisible;
    QMap<QString, bool> isPadsVisible;
    QMap<QString, bool> isVisible;
    void loadFile();
    void drawFile();
    void drawVias();
    void drawWires();
    void drawBoardOutline();
    void drawBoardOutlineVoids();
    void drawComponents();
    void drawFreePads();
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
