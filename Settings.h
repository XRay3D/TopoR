#pragma once

#include "Commons.h"
#include <memory>
#include <string>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {
/// <summary>
/// Раздел «Настройки дизайна».
/// </summary>
class Settings : public std::enable_shared_from_this<Settings> {
    /// <summary>
    /// Настройки автоматической трассировки.
    /// </summary>
public:
    class Autoroute : public std::enable_shared_from_this<Autoroute> {
        /// <summary>
        /// Настройка автоматической трассировки: режим трассировки.
        /// </summary>
    public:
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("mode")] public mode_Autoroute _mode;
        mode_Autoroute _mode = static_cast<mode_Autoroute>(0);

        /// <summary>
        /// Параметр автоматической трассировки: использование функциональной эквивалентности.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("autoEqu")] public autoEqu _autoEqu;
        autoEqu _autoEqu = static_cast<autoEqu>(0);

        /// <summary>
        /// Параметр автоматической трассировки: форма проводников.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("wireShape")] public wireShape _wireShape;
        wireShape _wireShape = static_cast<wireShape>(0);

        /// <summary>
        /// Параметр автоматической трассировки: создавать «капельки».
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("teardrops")] public Bool _teardrops;
        Bool _teardrops = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _teardropsSpecified
        bool getTeardropsSpecified() const;

        /// <summary>
        /// Параметр автоматической трассировки: ослабленный контроль зазоров.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("weakCheck")] public Bool _weakCheck;
        Bool _weakCheck = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _weakCheckSpecified
        bool getWeakCheckSpecified() const;

        /// <summary>
        /// Параметр автоматической трассировки: использовать имеющуюся разводку в качестве начального варианта.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("takeCurLayout")] public Bool _takeCurLayout;
        Bool _takeCurLayout = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _takeCurLayoutSpecified
        bool getTakeCurLayoutSpecified() const;

        /// <summary>
        /// Настройка автоматической трассировки: соединять планарные контакты напрямую.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("directConnectSMD")] public Bool _directConnectSMD;
        Bool _directConnectSMD = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _directConnectSMDSpecified
        bool getDirectConnectSMDSpecified() const;

        /// <summary>
        /// Настройка автоматической трассировки: не дотягивать проводник до точки привязки полигонального контакта.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("dontStretchWireToPolypin")] public Bool _dontStretchWireToPolypin;
        Bool _dontStretchWireToPolypin = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _dontStretchWireToPolypinSpecified
        bool getDontStretchWireToPolypinSpecified() const;
    };

    /// <summary>
    /// Настройки автоматических процедур.
    /// </summary>
public:
    class Autoproc : public std::enable_shared_from_this<Autoproc> {
        /// <summary>
        /// Настройка автоматической перекладки проводников.
        /// </summary>
    public:
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("refine")] public refine _refine;
        refine _refine = static_cast<refine>(0);

        /// <summary>
        /// Настройка автоматической подвижки.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("automove")] public automove _automove;
        automove _automove = static_cast<automove>(0);
    };

    /// <summary>
    /// Настройки автоматического размещения компонентов.
    /// </summary>
public:
    class Placement : public std::enable_shared_from_this<Placement> {
        /// <summary>
        /// Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        /// </summary>
    public:
        class PlacementArea : public std::enable_shared_from_this<PlacementArea> {
            /// <summary>
            /// Координаты точек, вершин
            /// </summary>
        public:
            // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
            // ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
            std::vector<std::shared_ptr<Dot>> _Dots;
            bool ShouldSerialize_Dots();
        };

        /// <summary>
        /// Настройки автоматического размещения компонентов: область размещения. Область прямоугольная, задаётся двумя вершинами(верхняя левая и правая нижняя).
        /// </summary>
    public:
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("PlacementArea")] public PlacementArea _PlacementArea;
        std::shared_ptr<PlacementArea> _PlacementArea;
    };

    /// <summary>
    /// Настройки ориентации ярлыков.
    /// </summary>
public:
    class Labels_Settings : public std::enable_shared_from_this<Labels_Settings> {
        /// <summary>
        /// Настройка ориентации ярлыков: вращать ярлык при вращении компонента.
        /// </summary>
    public:
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("rotateWithComp")] public Bool _rotateWithComp;
        Bool _rotateWithComp = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _rotateWithCompSpecified
        bool getRotateWithCompSpecified() const;

        /// <summary>
        /// Настройка редактирования ярлыков: использовать правила ориентации.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("useOrientRules")] public Bool _useOrientRules;
        Bool _useOrientRules = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _useOrientRulesSpecified
        bool getUseOrientRulesSpecified() const;

        /// <summary>
        /// Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на верхней стороне.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("topHorzRotate")] public Bool _topHorzRotate;
        Bool _topHorzRotate = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _topHorzRotateSpecified
        bool getTopHorzRotateSpecified() const;

        /// <summary>
        /// Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на верхней стороне.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("topVertRotate")] public Bool _topVertRotate;
        Bool _topVertRotate = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _topVertRotateSpecified
        bool getTopVertRotateSpecified() const;

        /// <summary>
        /// Настройка ориентации ярлыков: поворот для ярлыков горизонтальной ориентации на нижней стороне.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("bottomHorzRotate")] public Bool _bottomHorzRotate;
        Bool _bottomHorzRotate = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _bottomHorzRotateSpecified
        bool getBottomHorzRotateSpecified() const;

        /// <summary>
        /// Настройка ориентации ярлыков: поворот для ярлыков вертикальной ориентации на нижней стороне.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("bottomVertRotate")] public Bool _bottomVertRotate;
        Bool _bottomVertRotate = static_cast<Bool>(0);
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlIgnore] public bool _bottomVertRotateSpecified
        bool getBottomVertRotateSpecified() const;
    };

    /// <summary>
    /// Версия раздела.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("version")] public string _version;
    std::wstring _version;

    /// <summary>
    /// Настройки автоматической трассировки.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Autoroute")] public Autoroute _Autoroute;
    std::shared_ptr<Autoroute> _Autoroute;

    /// <summary>
    /// Настройки автоматических процедур.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Autoproc")] public Autoproc _Autoproc;
    std::shared_ptr<Autoproc> _Autoproc;

    /// <summary>
    /// Настройки автоматического размещения компонентов.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Placement")] public Placement _Placement;
    std::shared_ptr<Placement> _Placement;

    /// <summary>
    /// Настройки ориентации ярлыков.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Labels")] public Labels_Settings _Labels;
    std::shared_ptr<Labels_Settings> _Labels;

    /********************************************************************
     * Здесь находятся функции для работы с элементами класса Settings. *
     * Они не являются частью формата TopoR PCB.                        *
     * ******************************************************************/

    /********************************************************************/
};
} // namespace TopoR_PCB_Classes
