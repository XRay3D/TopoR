#pragma once

#include <QMainWindow>
#include <QMap>

struct QGraphicsItemGroup;
namespace Ui {
struct MainWindow;
}

namespace TopoR {
struct TopoR_PCB_File;

} // namespace TopoR

struct QGraphicsItem;

struct MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // private:
    Ui::MainWindow* ui;
    TopoR::TopoR_PCB_File* file;
    QString dir;

    std::unordered_map<std::string_view, QColor> detailsColor;
    std::unordered_map<std::string_view, QColor> fixColor;
    std::unordered_map<std::string_view, QColor> padsColor;

    std::unordered_map<std::string_view, QGraphicsItemGroup*> lauerGroups;

    std::unordered_map<std::string_view, bool> isDetailsVisible;
    std::unordered_map<std::string_view, bool> isPadsVisible;
    std::unordered_map<std::string_view, bool> isVisible;

    void edit();

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
