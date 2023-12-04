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
        mode_Autoroute mode_{};
        // Параметр автоматической трассировки: использование функциональной эквивалентности.
        // [XmlAttribute("autoEqu")] public autoEqu autoEqu_;
        autoEqu autoEqu_{};
        // Параметр автоматической трассировки: форма проводников.
        // [XmlAttribute("wireShape")] public wireShape wireShape_;
        wireShape wireShape_{};
        // Параметр автоматической трассировки: создавать «капельки».
        // [XmlAttribute("teardrops")] public Bool teardrops_;
        Bool teardrops_{};
        // public bool teardropsSpecified_
        // Параметр автоматической трассировки: ослабленный контроль зазоров.
        // [XmlAttribute("weakCheck")] public Bool weakCheck_;
        Bool weakCheck_{};
        // public bool weakCheckSpecified_
        // Параметр автоматической трассировки: использовать имеющуюся разводку в качестве начального варианта.
        // [XmlAttribute("takeCurLayout")] public Bool takeCurLayout_;
        Bool takeCurLayout_{};
        // public bool takeCurLayoutSpecified_
        // Настройка автоматической трассировки: соединять планарные контакты напрямую.
        // [XmlAttribute("directConnectSMD")] public Bool directConnectSMD_;
        Bool directConnectSMD_{};
        // public bool directConnectSMDSpecified_
        // Настройка автоматической трассировки: не дотягивать проводник до точки привязки полигонального контакта.
        // [XmlAttribute("dontStretchWireToPolypin")] public Bool dontStretchWireToPolypin_;
        Bool dontStretchWireToPolypin_{};
        // public bool dontStretchWireToPolypinSpecified_
    };
    // Настройки автоматических процедур.
    struct Autoproc {
        // Настройка автоматической перекладки проводников.
        // [XmlAttribute("refine")] public refine refine_;
        refine refine_{};
        // Настройка автоматической подвижки.
        // [XmlAttribute("automove")] public automove automove_;
        automove automove_{};
    };
    // Настройки автоматического размещения компонентов.
    struct Placement {
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        struct PlacementArea {
            // Координаты точек, вершин
            // [XmlElement("Dot")] public List<Dot> Dots_;
            std::vector<Dot> Dots;
        };
        // Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        // [XmlElement("PlacementArea")] public PlacementArea placementArea;
        PlacementArea placementArea;
    };
    // Настройки ориентации ярлыков.
    struct Labels {
        // Настройка ориентации ярлыков: вращать ярлык при вращении компонента.
        // [XmlAttribute("rotateWithComp")] public Bool rotateWithComp_;
        Bool rotateWithComp_{};
        // public bool rotateWithCompSpecified_
        // Настройка редактирования ярлыков: использовать правила ориентации.
        // [XmlAttribute("useOrientRules")] public Bool useOrientRules_;
        Bool useOrientRules_{};
        // public bool useOrientRulesSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на верхней стороне.
        // [XmlAttribute("topHorzRotate")] public Bool topHorzRotate_;
        Bool topHorzRotate_{};
        // public bool topHorzRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на верхней стороне.
        // [XmlAttribute("topVertRotate")] public Bool topVertRotate_;
        Bool topVertRotate_{};
        // public bool topVertRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на нижней стороне.
        // [XmlAttribute("bottomHorzRotate")] public Bool bottomHorzRotate_;
        Bool bottomHorzRotate_{};
        // public bool bottomHorzRotateSpecified_
        // Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на нижней стороне.
        // [XmlAttribute("bottomVertRotate")] public Bool bottomVertRotate_;
        Bool bottomVertRotate_{};
        // public bool bottomVertRotateSpecified_
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    QString version;
    // Настройки автоматической трассировки.
    // [XmlElement("Autoroute")] public Autoroute autoroute;
    Autoroute autoroute;
    // Настройки автоматических процедур.
    // [XmlElement("Autoproc")] public Autoproc autoproc;
    Autoproc autoproc;
    // Настройки автоматического размещения компонентов.
    // [XmlElement("Placement")] public Placement placement;
    Placement placement;
    // Настройки ориентации ярлыков.
    // [XmlElement("Labels")] public Labels Labels_;
    Labels Labels_;
    /********************************************************************
     * Здесь находятся функции для работы с элементами класса Settings. *
     * Они не являются частью формата TopoR PCB.                        *
     * ******************************************************************/
    /********************************************************************/
};
} // namespace TopoR_PCB_Classes
