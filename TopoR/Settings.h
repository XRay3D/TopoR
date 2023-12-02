#pragma once

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

        // [XmlAttribute("mode")] public mode_Autoroute mode_;
        mode_Autoroute _mode{};

        // Параметр автоматической трассировки: использование функциональной эквивалентности.
        // [XmlAttribute("autoEqu")] public autoEqu autoEqu_;
        autoEqu _autoEqu{};

        // Параметр автоматической трассировки: форма проводников.
        // [XmlAttribute("wireShape")] public wireShape wireShape_;
        wireShape _wireShape{};

        // Параметр автоматической трассировки: создавать «капельки».
        // [XmlAttribute("teardrops")] public Bool teardrops_;
        Bool _teardrops{};
        // public bool _teardropsSpecified
        bool getTeardropsSpecified() const;

        // Параметр автоматической трассировки: ослабленный контроль зазоров.
        // [XmlAttribute("weakCheck")] public Bool weakCheck_;
        Bool _weakCheck{};
        // public bool _weakCheckSpecified
        bool getWeakCheckSpecified() const;

        // Параметр автоматической трассировки: использовать имеющуюся разводку в качестве начального варианта.
        // [XmlAttribute("takeCurLayout")] public Bool takeCurLayout_;
        Bool _takeCurLayout{};
        // public bool _takeCurLayoutSpecified
        bool getTakeCurLayoutSpecified() const;

        // Настройка автоматической трассировки: соединять планарные контакты напрямую.
        // [XmlAttribute("directConnectSMD")] public Bool directConnectSMD_;
        Bool _directConnectSMD{};
        // public bool _directConnectSMDSpecified
        bool getDirectConnectSMDSpecified() const;

        // Настройка автоматической трассировки: не дотягивать проводник до точки привязки полигонального контакта.
        // [XmlAttribute("dontStretchWireToPolypin")] public Bool dontStretchWireToPolypin_;
        Bool _dontStretchWireToPolypin{};
        // public bool _dontStretchWireToPolypinSpecified
        bool getDontStretchWireToPolypinSpecified() const;
    };

    // Настройки автоматических процедур.
    struct Autoproc {

        // Настройка автоматической перекладки проводников.
        // [XmlAttribute("refine")] public refine refine_;
        refine _refine{};

        // Настройка автоматической подвижки.
        // [XmlAttribute("automove")] public automove automove_;
        automove _automove{};
    };

    // Настройки автоматического размещения компонентов.
    struct Placement {
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        struct PlacementArea {
            // Координаты точек, вершин
            // [XmlElement("Dot")] public List<Dot> Dots_;
            std::vector<Dot> Dots_;
            bool ShouldSerialize_Dots();
        };

        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        // [XmlElement("PlacementArea")] public PlacementArea PlacementArea_;
        PlacementArea PlacementArea_;
    };

    // Настройки ориентации ярлыков.
    struct Labels_Settings {
        // Настройка ориентации ярлыков: вращать ярлык при вращении компонента.
        // [XmlAttribute("rotateWithComp")] public Bool rotateWithComp_;
        Bool _rotateWithComp{};
        // public bool _rotateWithCompSpecified
        bool getRotateWithCompSpecified() const;

        // Настройка редактирования ярлыков: использовать правила ориентации.
        // [XmlAttribute("useOrientRules")] public Bool useOrientRules_;
        Bool _useOrientRules{};
        // public bool _useOrientRulesSpecified
        bool getUseOrientRulesSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на верхней стороне.
        // [XmlAttribute("topHorzRotate")] public Bool topHorzRotate_;
        Bool _topHorzRotate{};
        // public bool _topHorzRotateSpecified
        bool getTopHorzRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на верхней стороне.
        // [XmlAttribute("topVertRotate")] public Bool topVertRotate_;
        Bool _topVertRotate{};
        // public bool _topVertRotateSpecified
        bool getTopVertRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на нижней стороне.
        // [XmlAttribute("bottomHorzRotate")] public Bool bottomHorzRotate_;
        Bool _bottomHorzRotate{};
        // public bool _bottomHorzRotateSpecified
        bool getBottomHorzRotateSpecified() const;

        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на нижней стороне.
        // [XmlAttribute("bottomVertRotate")] public Bool bottomVertRotate_;
        Bool _bottomVertRotate{};
        // public bool _bottomVertRotateSpecified
        bool getBottomVertRotateSpecified() const;
    };

    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    QString version_;

    // Настройки автоматической трассировки.
    // [XmlElement("Autoroute")] public Autoroute Autoroute_;
    Autoroute Autoroute_;

    // Настройки автоматических процедур.
    // [XmlElement("Autoproc")] public Autoproc Autoproc_;
    Autoproc Autoproc_;

    // Настройки автоматического размещения компонентов.
    // [XmlElement("Placement")] public Placement Placement_;
    Placement Placement_;

    // Настройки ориентации ярлыков.
    // [XmlElement("Labels")] public Labels_Settings Labels_;
    Labels_Settings Labels_;

    /********************************************************************
     * Здесь находятся функции для работы с элементами класса Settings. *
     * Они не являются частью формата TopoR PCB.                        *
     * ******************************************************************/

    /********************************************************************/
};
} // namespace TopoR_PCB_Classes
