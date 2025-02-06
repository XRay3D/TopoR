#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Настройки дизайна».
struct Settings {
    // Настройки автоматической трассировки.
    struct Autoroute {
        // Настройка автоматической трассировки: режим трассировки.
        // [Xml::Attribute("mode")] public mode_Autoroute mode_;
        Xml::Attr<mode_Autoroute> mode;
        // Параметр автоматической трассировки: использование функциональной эквивалентности.
        // [Xml::Attribute("autoEqu")] public autoEqu autoEqu_;
        Xml::Attr<autoEqu> autoEqu_;
        // Параметр автоматической трассировки: форма проводников.
        // [Xml::Attribute("wireShape")] public wireShape wireShape_;
        Xml::Attr<wireShape> wireShape_;
        // Параметр автоматической трассировки: создавать «капельки».
        // [Xml::Attribute("teardrops")] public Bool teardrops_;
        Xml::Attr<Bool> teardrops;
        // public bool teardropsSpecified_
        // Параметр автоматической трассировки: ослабленный контроль зазоров.
        // [Xml::Attribute("weakCheck")] public Bool weakCheck_;
        Xml::Attr<Bool> weakCheck;
        // public bool weakCheckSpecified_
        // Параметр автоматической трассировки: использовать имеющуюся разводку в качестве начального варианта.
        // [Xml::Attribute("takeCurLayout")] public Bool takeCurLayout_;
        Xml::Attr<Bool> takeCurLayout;
        // public bool takeCurLayoutSpecified_
        // Настройка автоматической трассировки: соединять планарные контакты напрямую.
        // [Xml::Attribute("directConnectSMD")] public Bool directConnectSMD_;
        Xml::Attr<Bool> directConnectSMD;
        // public bool directConnectSMDSpecified_
        // Настройка автоматической трассировки: не дотягивать проводник до точки привязки полигонального контакта.
        // [Xml::Attribute("dontStretchWireToPolypin")] public Bool dontStretchWireToPolypin_;
        Xml::Attr<Bool> dontStretchWireToPolypin;
        // public bool dontStretchWireToPolypinSpecified_
    };
    // Настройки автоматических процедур.
    struct Autoproc {
        // Настройка автоматической перекладки проводников.
        // [Xml::Attribute("refine")] public refine refine_;
        Xml::Attr<refine> refine_;
        // Настройка автоматической подвижки.
        // [Xml::Attribute("automove")] public automove automove_;
        Xml::Attr<automove> automove_;
    };
    // Настройки автоматического размещения компонентов.
    struct Placement {
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        // struct PlacementArea {
        // Координаты точек, вершин
        // [Xml::Element("Dot")] public List<Dot> Dots_;
        Xml::ArrayElem<Dot> PlacementArea;
        // };
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        // [Xml::Element("PlacementArea")] public PlacementArea placementArea;
        // PlacementArea placementArea;
    };
    // Настройки ориентации ярлыков.
    struct Labels {
        // Настройка ориентации ярлыков: вращать ярлык при вращении компонента.
        // [Xml::Attribute("rotateWithComp")] public Bool rotateWithComp_;
        Xml::Attr<Bool> rotateWithComp;
        // public bool rotateWithCompSpecified_
        // Настройка редактирования ярлыков: использовать правила ориентации.
        // [Xml::Attribute("useOrientRules")] public Bool useOrientRules_;
        Xml::Attr<Bool> useOrientRules;
        // public bool useOrientRulesSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на верхней стороне.
        // [Xml::Attribute("topHorzRotate")] public Bool topHorzRotate_;
        Xml::Attr<Bool> topHorzRotate;
        // public bool topHorzRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на верхней стороне.
        // [Xml::Attribute("topVertRotate")] public Bool topVertRotate_;
        Xml::Attr<Bool> topVertRotate;
        // public bool topVertRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на нижней стороне.
        // [Xml::Attribute("bottomHorzRotate")] public Bool bottomHorzRotate_;
        Xml::Attr<Bool> bottomHorzRotate;
        // public bool bottomHorzRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на нижней стороне.
        // [Xml::Attribute("bottomVertRotate")] public Bool bottomVertRotate_;
        Xml::Attr<Bool> bottomVertRotate;
        // public bool bottomVertRotateSpecified_
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Настройки автоматической трассировки.
    // [Xml::Element("Autoroute")] public Autoroute autoroute;
    Autoroute autoroute;
    // Настройки автоматических процедур.
    // [Xml::Element("Autoproc")] public Autoproc autoproc;
    Autoproc autoproc;
    // Настройки автоматического размещения компонентов.
    // [Xml::Element("Placement")] public Placement placement;
    Placement placement;
    // Настройки ориентации ярлыков.
    // [Xml::Element("Labels")] public Labels Labels_;
    Labels labels;
    /********************************************************************
     * Здесь находятся функции для работы с элементами класса Settings. *
     * Они не являются частью формата TopoR PCB.                        *
     * ******************************************************************/
    /********************************************************************/
};
} // namespace TopoR
