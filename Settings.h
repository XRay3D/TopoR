﻿#pragma once

#include "Commons.h"

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Настройки дизайна».
struct Settings {

    // Настройки автоматической трассировки.
    struct Autoroute {

        // Настройка автоматической трассировки: режим трассировки.

        // ORIGINAL LINE: [XmlAttribute("mode")] public mode_Autoroute _mode;
        mode_Autoroute _mode{};

        // Параметр автоматической трассировки: использование функциональной эквивалентности.
        // ORIGINAL LINE: [XmlAttribute("autoEqu")] public autoEqu _autoEqu;
        autoEqu _autoEqu{};

        // Параметр автоматической трассировки: форма проводников.
        // ORIGINAL LINE: [XmlAttribute("wireShape")] public wireShape _wireShape;
        wireShape _wireShape{};

        // Параметр автоматической трассировки: создавать «капельки».
        // ORIGINAL LINE: [XmlAttribute("teardrops")] public Bool _teardrops;
        Bool _teardrops{};
        // ORIGINAL LINE: [XmlIgnore] public bool _teardropsSpecified
        bool getTeardropsSpecified() const;

        // Параметр автоматической трассировки: ослабленный контроль зазоров.
        // ORIGINAL LINE: [XmlAttribute("weakCheck")] public Bool _weakCheck;
        Bool _weakCheck{};
        // ORIGINAL LINE: [XmlIgnore] public bool _weakCheckSpecified
        bool getWeakCheckSpecified() const;

        // Параметр автоматической трассировки: использовать имеющуюся разводку в качестве начального варианта.
        // ORIGINAL LINE: [XmlAttribute("takeCurLayout")] public Bool _takeCurLayout;
        Bool _takeCurLayout{};
        // ORIGINAL LINE: [XmlIgnore] public bool _takeCurLayoutSpecified
        bool getTakeCurLayoutSpecified() const;

        // Настройка автоматической трассировки: соединять планарные контакты напрямую.
        // ORIGINAL LINE: [XmlAttribute("directConnectSMD")] public Bool _directConnectSMD;
        Bool _directConnectSMD{};
        // ORIGINAL LINE: [XmlIgnore] public bool _directConnectSMDSpecified
        bool getDirectConnectSMDSpecified() const;

        // Настройка автоматической трассировки: не дотягивать проводник до точки привязки полигонального контакта.
        // ORIGINAL LINE: [XmlAttribute("dontStretchWireToPolypin")] public Bool _dontStretchWireToPolypin;
        Bool _dontStretchWireToPolypin{};
        // ORIGINAL LINE: [XmlIgnore] public bool _dontStretchWireToPolypinSpecified
        bool getDontStretchWireToPolypinSpecified() const;
    };

    // Настройки автоматических процедур.
    struct Autoproc {

        // Настройка автоматической перекладки проводников.
        // ORIGINAL LINE: [XmlAttribute("refine")] public refine _refine;
        refine _refine{};

        // Настройка автоматической подвижки.
        // ORIGINAL LINE: [XmlAttribute("automove")] public automove _automove;
        automove _automove{};
    };

    // Настройки автоматического размещения компонентов.
    struct Placement {
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        struct PlacementArea {
            // Координаты точек, вершин
            // ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
            std::vector<Dot> _Dots;
            bool ShouldSerialize_Dots();
        };

        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        // ORIGINAL LINE: [XmlElement("PlacementArea")] public PlacementArea _PlacementArea;
        PlacementArea _PlacementArea;
    };

    // Настройки ориентации ярлыков.
    struct Labels_Settings {
        // Настройка ориентации ярлыков: вращать ярлык при вращении компонента.
        // ORIGINAL LINE: [XmlAttribute("rotateWithComp")] public Bool _rotateWithComp;
        Bool _rotateWithComp{};
        // ORIGINAL LINE: [XmlIgnore] public bool _rotateWithCompSpecified
        bool getRotateWithCompSpecified() const;

        // Настройка редактирования ярлыков: использовать правила ориентации.
        // ORIGINAL LINE: [XmlAttribute("useOrientRules")] public Bool _useOrientRules;
        Bool _useOrientRules{};
        // ORIGINAL LINE: [XmlIgnore] public bool _useOrientRulesSpecified
        bool getUseOrientRulesSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на верхней стороне.
        // ORIGINAL LINE: [XmlAttribute("topHorzRotate")] public Bool _topHorzRotate;
        Bool _topHorzRotate{};
        // ORIGINAL LINE: [XmlIgnore] public bool _topHorzRotateSpecified
        bool getTopHorzRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на верхней стороне.
        // ORIGINAL LINE: [XmlAttribute("topVertRotate")] public Bool _topVertRotate;
        Bool _topVertRotate{};
        // ORIGINAL LINE: [XmlIgnore] public bool _topVertRotateSpecified
        bool getTopVertRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на нижней стороне.
        // ORIGINAL LINE: [XmlAttribute("bottomHorzRotate")] public Bool _bottomHorzRotate;
        Bool _bottomHorzRotate{};
        // ORIGINAL LINE: [XmlIgnore] public bool _bottomHorzRotateSpecified
        bool getBottomHorzRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на нижней стороне.
        // ORIGINAL LINE: [XmlAttribute("bottomVertRotate")] public Bool _bottomVertRotate;
        Bool _bottomVertRotate{};
        // ORIGINAL LINE: [XmlIgnore] public bool _bottomVertRotateSpecified
        bool getBottomVertRotateSpecified() const;
    };

    // Версия раздела.
    // ORIGINAL LINE: [XmlAttribute("version")] public string _version;
    QString _version;

    // Настройки автоматической трассировки.
    // ORIGINAL LINE: [XmlElement("Autoroute")] public Autoroute _Autoroute;
    Autoroute _Autoroute;

    // Настройки автоматических процедур.
    // ORIGINAL LINE: [XmlElement("Autoproc")] public Autoproc _Autoproc;
    Autoproc _Autoproc;

    // Настройки автоматического размещения компонентов.
    // ORIGINAL LINE: [XmlElement("Placement")] public Placement _Placement;
    Placement _Placement;

    // Настройки ориентации ярлыков.
    // ORIGINAL LINE: [XmlElement("Labels")] public Labels_Settings _Labels;
    Labels_Settings _Labels;

    /********************************************************************
     * Здесь находятся функции для работы с элементами класса Settings. *
     * Они не являются частью формата TopoR PCB.                        *
     * ******************************************************************/

    /********************************************************************/
};
} // namespace TopoR_PCB_Classes
