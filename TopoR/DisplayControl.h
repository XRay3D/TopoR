#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Настройки отображения».
struct DisplayControl {
    // Настройка отображения: параметры текущего вида.
    struct View {
        // Параметр текущего вида: масштаб.
        // [XmlAttribute("scale", DataType = "double")] public double scale_;
        XmlAttr<double> scale;
        // Параметр текущего вида: прокрутка по горизонтали.
        // [XmlAttribute("scrollHorz", DataType = "double")] public double scrollHorz_;
        XmlAttr<double> scrollHorz;
        // Параметр текущего вида: прокрутка по вертикали.
        // [XmlAttribute("scrollVert", DataType = "double")] public double scrollVert_;
        XmlAttr<double> scrollVert;
    };
    // Устанавливает активный слой.
    struct ActiveLayer {
        /* Опечатка в спецификации?    .
            // Тип слоя.
            [XmlAttribute("type")]
            public LayerType type_;*/
        // Наименование слоя.

        XmlAttr<QString> name;
    };
    // Настройка отображения: единицы измерения.
    struct Units {
        // Настройка отображения: единицы измерения.
        // [XmlAttribute("preference")] public preference preference_;
        XmlAttr<preference> preference_;
    };
    // Настройка отображения: общие цветовые настройки.
    struct Colors {
        // Настройка отображения: текущая цветовая схема.
        // [XmlAttribute("colorScheme")] public string colorScheme_;
        XmlAttr<QString> colorScheme;
        // Настройка отображения: яркость выделенных объектов.
        // [XmlAttribute("hilightRate", DataType = "int")] public int hilightRate_;
        XmlAttr<int> hilightRate;
        // int hilightRate_ = 0;
        // Настройка отображения: степень затемнения невыделенных объектов.
        // [XmlAttribute("darkRate", DataType = "int")] public int darkRate_;
        XmlAttr<int> darkRate;
        // int darkRate_ = 0;
        // Настройка отображения: цвет фона.
        // [XmlAttribute("background")] public string background_;
        XmlAttr<QString> background;
        // Настройка отображения: цвет контура платы.
        // [XmlAttribute("board")] public string board_;
        XmlAttr<QString> board;
        // Настройка отображения: цвет линий связей.
        // [XmlAttribute("netLines")] public string netLines_;
        XmlAttr<QString> netLines;
        // Настройка отображения: цвет запрета размещения на обеих сторонах платы.
        // [XmlAttribute("keepoutPlaceBoth")] public string keepoutPlaceBoth_;
        XmlAttr<QString> keepoutPlaceBoth;
        // Настройка отображения: цвет запрета трассировки на всех слоях.
        // [XmlAttribute("keepoutWireAll")] public string keepoutWireAll_;
        XmlAttr<QString> keepoutWireAll;
        // Настройка отображения: цвет запрета размещения на верхней стороне платы.
        // [XmlAttribute("keepoutPlaceTop")] public string keepoutPlaceTop_;
        XmlAttr<QString> keepoutPlaceTop;
        // Настройка отображения: цвет запрета размещения на нижней стороне платы.
        // [XmlAttribute("keepoutPlaceBot")] public string keepoutPlaceBot_;
        XmlAttr<QString> keepoutPlaceBot;
        // Настройка отображения: цвет габаритов компонентов.
        // [XmlAttribute("compsBound")] public string compsBound_;
        XmlAttr<QString> compsBound;
        // Настройка отображения: цвет позиционных обозначений компонентов.
        // [XmlAttribute("compsName")] public string compsName_;
        XmlAttr<QString> compsName;
        // Настройка отображения: цвет имён контактов.
        // [XmlAttribute("pinsName")] public string pinsName_;
        XmlAttr<QString> pinsName;
        // Настройка отображения: цвет имён цепей контактов.
        // [XmlAttribute("pinsNet")] public string pinsNet_;
        XmlAttr<QString> pinsNet;
        // Настройка отображения: цвет сквозных контактных площадок.
        // [XmlAttribute("clrThroughPads")] public string clrThroughPads_;
        XmlAttr<QString> clrThroughPads;
        // Настройка отображения: цвет сквозных переходных отверстий.
        // [XmlAttribute("clrThroughVias")] public string clrThroughVias_;
        XmlAttr<QString> clrThroughVias;
        // Настройка отображения: цвет скрытых переходных отверстий.
        // [XmlAttribute("clrBurriedVias")] public string clrBurriedVias_;
        XmlAttr<QString> clrBurriedVias;
        // Настройка отображения: цвет глухих переходных отверстий.
        // [XmlAttribute("clrBlindVias")] public string clrBlindVias_;
        XmlAttr<QString> clrBlindVias;
        // Настройка отображения: цвет зафиксированных переходных отверстий.
        // [XmlAttribute("clrFixedVias")] public string clrFixedVias_;
        XmlAttr<QString> clrFixedVias;
        // Настройка отображения: цвет нарушений DRC.
        // [XmlAttribute("drcViolation")] public string drcViolation_;
        XmlAttr<QString> drcViolation;
        // Настройка отображения: цвет индикации уменьшения номинального зазора.
        // [XmlAttribute("narrow")] public string narrow_;
        XmlAttr<QString> narrow;
        // Настройка отображения: цвет индикации уменьшения ширины проводника.
        // [XmlAttribute("trimmed")] public string trimmed_;
        XmlAttr<QString> trimmed;
    };
    // Настройка отображения: настройки видимости объектов.
    struct Show {
        Optional<XmlAttr<Bool>> blindVia;            // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        Optional<XmlAttr<Bool>> burriedVia;          // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        Optional<XmlAttr<Bool>> fixedVia;            // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        Optional<XmlAttr<Bool>> showActiveLayerOnly; // Настройка отображения: показывать только активный слой.
        Optional<XmlAttr<Bool>> showBoardOutline;    // Настройка отображения: показывать контур платы.
        Optional<XmlAttr<Bool>> showBotMechDetails;  // Настройка отображения: показывать детали на нижних металлических слоях.
        Optional<XmlAttr<Bool>> showBotMechLayers;   // Настройка отображения: показывать нижние механические слои.
        Optional<XmlAttr<Bool>> showBotMechPads;     // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        Optional<XmlAttr<Bool>> showCompBot;         // Настройка отображения: показывать компоненты на нижней стороне.
        Optional<XmlAttr<Bool>> showCompTop;         // Настройка отображения: показывать компоненты на верхней стороне.
        Optional<XmlAttr<Bool>> showComponents;      // Настройка отображения: показывать компоненты.
        Optional<XmlAttr<Bool>> showCompsBound;      // Настройка отображения: показывать габариты компонентов.
        Optional<XmlAttr<Bool>> showCompsDes;        // Настройка отображения: показывать позиционные обозначения компонентов.
        Optional<XmlAttr<Bool>> showCoppers;         // Настройка отображения: показывать области металлизации (полигоны).
        Optional<XmlAttr<Bool>> showDRCViolations;   // Настройка отображения: показывать нарушение DRC.
        Optional<XmlAttr<Bool>> showDocLayers;       // Настройка отображения: показывать документирующие слои.
        Optional<XmlAttr<Bool>> showKeepouts;        // Настройка отображения: показывать запреты.
        Optional<XmlAttr<Bool>> showLabelOther;      // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        Optional<XmlAttr<Bool>> showLabelPartName;   // Настройка отображения: показывать ярлыки атрибута PartName.
        Optional<XmlAttr<Bool>> showLabelRefDes;     // Настройка отображения: показывать ярлыки атрибута RefDes.
        Optional<XmlAttr<Bool>> showMetalPads;       // Настройка отображения: показывать контактные площадки на металлических слоях.
        Optional<XmlAttr<Bool>> showMountingHoles;   // Настройка отображения: показывать монтажные отверстия.
        Optional<XmlAttr<Bool>> showNarrow;          // Настройка отображения: показывать уменьшение номинального зазора.
        Optional<XmlAttr<Bool>> showNetLines;        // Настройка отображения: показывать связи.
        Optional<XmlAttr<Bool>> showPinsName;        // Настройка отображения: показывать имена контактов.
        Optional<XmlAttr<Bool>> showPinsNet;         // Настройка отображения: показывать имена цепей контактов.
        Optional<XmlAttr<Bool>> showPlaceKeepouts;   // Настройка отображения: показывать запреты размещения.
        Optional<XmlAttr<Bool>> showRouteKeepouts;   // Настройка отображения: показывать запреты трассировки.
        Optional<XmlAttr<Bool>> showSerpentArea;     // Настройка отображения: показывать области змеек.
        Optional<XmlAttr<Bool>> showSignalLayers;    // Настройка отображения: показывать металлические слои.
        Optional<XmlAttr<Bool>> showTexts;           // Настройка отображения: показывать ярлыки (надписи).
        Optional<XmlAttr<Bool>> showThinWires;       // Настройка отображения: показывать проводники тонкими линиями.
        Optional<XmlAttr<Bool>> showTopMechDetails;  // Настройка отображения: показывать детали на верхних металлических слоях.
        Optional<XmlAttr<Bool>> showTopMechLayers;   // Настройка отображения: показывать верхние механические слои.
        Optional<XmlAttr<Bool>> showTopMechPads;     // Настройка отображения: показывать КП на верхних металлических слоях.
        Optional<XmlAttr<Bool>> showTrimmed;         // Настройка отображения: показывать уменьшение ширины проводника.
        Optional<XmlAttr<Bool>> showVias;            // Настройка отображения: показывать переходы.
        Optional<XmlAttr<Bool>> showViolations;      // Настройка отображения: показывать нарушения.
        Optional<XmlAttr<Bool>> showWires;           // Настройка отображения: показывать проводники.
        Optional<XmlAttr<Bool>> throughPad;          // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        Optional<XmlAttr<Bool>> throughVia;          // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        Optional<XmlAttr<QString>> displayScheme;    // Настройка отображения: текущая схема отображения.
    };
    // Настройки сетки.
    struct Grid {
        // Настройка отображения сетки: шаг сетки.
        // Настройка отображения сетки: шаг сетки.
        // [XmlElement("GridSpace")] public GridSpace gridSpace;
        struct GridSpace {
            // шаг сетки по горизонтали.
            // [XmlAttribute("x", DataType = "double")] public double x_;
            XmlAttr<double> x;
            // шаг сетки по вертикали.
            // [XmlAttribute("y", DataType = "double")] public double y_;
            XmlAttr<double> y;
        } gridSpace;
        // Настройка отображения сетки: цвет сетки.
        // [XmlAttribute("gridColor")] public string gridColor_;
        Optional<XmlAttr<QString>> gridColor;
        // Настройка отображения сетки: тип сетки.
        // [XmlAttribute("gridKind")] public gridKind gridKind_;
        Optional<XmlAttr<gridKind>> gridKind_;
        // Настройка отображения сетки: показывать сетку.
        // [XmlAttribute("gridShow")] public Bool gridShow_;
        Optional<XmlAttr<Bool>> gridShow;
        // Настройка ручного редактора: выравнивание на сетку.
        // [XmlAttribute("alignToGrid")] public Bool alignTogrid;
        Optional<XmlAttr<Bool>> alignTogrid;
        // Настройка ручного редактирования: привязка к углу кратному 45˚.
        // [XmlAttribute("snapToAngle")] public Bool snapToAngle_;
        Optional<XmlAttr<Bool>> snapToAngle;

        Optional<XmlAttr<Bool>> saveProportion;
    };
    // Настройка отображения: настройки видимости слоя.
    struct LayerOptions {
        // Настройка отображения: цветовые настройки слоя.
        struct Colors {
            // Настройка отображения слоя: цвет деталей, проводников (основной цвет слоя).
            // [XmlAttribute("details")] public string details_;
            XmlAttr<QString> details;
            // Настройка отображения слоя: цвет контактных площадок.
            // [XmlAttribute("pads")] public string pads_;
            XmlAttr<QString> pads;
            // Настройка отображения слоя: цвет зафиксированных объектов.
            // [XmlAttribute("fix")] public string fix_;
            XmlAttr<QString> fix;
        };
        // Настройка отображения слоя: настройки видимости.
        struct Show {
            // Флаг видимости.
            // [XmlAttribute("visible")] public Bool visible_;
            Optional<XmlAttr<Bool>> visible;
            // Настройка отображения слоя: видимость деталей.
            // [XmlAttribute("details")] public Bool details_;
            XmlAttr<Bool> details;
            // Настройка отображения слоя: видимость контактных площадок.
            // [XmlAttribute("pads")] public Bool pads_;
            XmlAttr<Bool> pads;
        };
        // Ссылка на слой.
        // [XmlElement("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Настройка отображения: цветовые настройки слоя.
        // [XmlElement("Colors")] public Colors colors;
        Colors colors;
        // Настройка отображения слоя: настройки видимости.
        // [XmlElement("Show")] public Show show;
        Show show;
    };
    // Отображение цепей особым цветом.
    struct ColorNets {
        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        struct SetColor {
            // Отображение цепей особым цветом: задание цвета.
            // [XmlAttribute("color")] public string color_;
            XmlAttr<QString> color;
            // Ссылка на цепь или сигнал
            // [XmlElement(NetRef),
            //  XmlElement(NetGroupRef),
            //  XmlElement(AllNets),
            //  XmlElement(SignalRef),
            //  XmlElement(DiffSignalRef),
            //  XmlElement(SignalGroupRef),] public Object Refs_;
            XmlVariant<
                NetRef,
                NetGroupRef,
                AllNets,
                SignalRef,
                DiffSignalRef,
                SignalGroupRef>
                Refs;
        };
        // Флаг применения правила.
        // [XmlAttribute("enabled")] public Bool enabled_;
        XmlAttr<Bool> enabled;
        // Отображение цепей особым цветом: применять для проводников.
        // [XmlAttribute("colorizeWire")] public Bool colorizeWire_;
        XmlAttr<Bool> colorizeWire;
        // Отображение цепей особым цветом: применять для контактных площадок.
        // [XmlAttribute("colorizePad")] public Bool colorizePad_;
        XmlAttr<Bool> colorizePad;
        // Отображение цепей особым цветом: применять для областей металлизации.
        // [XmlAttribute("colorizeCopper")] public Bool colorizeCopper_;
        XmlAttr<Bool> colorizeCopper;
        // Отображение цепей особым цветом: применять для переходов.
        // [XmlAttribute("colorizeVia")] public Bool colorizeVia_;
        XmlAttr<Bool> colorizeVia;
        // Отображение цепей особым цветом: применять для связей.
        // [XmlAttribute("colorizeNetline")] public Bool colorizeNetline_;
        XmlAttr<Bool> colorizeNetline;
        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        // [XmlElement("SetColor")] public List<SetColor> SetColors_;
        XmlArrayElem<SetColor> SetColors;
    };
    // Фильтр отображения связей.
    struct FilterNetlines {
        // Флаг применения правила.
        // [XmlAttribute("enabled")] public Bool enabled_;
        XmlAttr<Bool> enabled;
        // Ссылки на цепь или сигнал
        // [XmlElement(NetRef),
        //  XmlElement(NetGroupRef),
        //  XmlElement(AllNets),
        //  XmlElement(SignalRef),
        //  XmlElement(DiffSignalRef),
        //  XmlElement(SignalGroupRef),] public List<Object> Refs_;
        XmlArrayElem<XmlVariant<
            AllNets,
            DiffSignalRef,
            NetGroupRef,
            NetRef,
            SignalGroupRef,
            SignalRef>>
            Refs_;
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Настройка отображения: параметры текущего вида.
    // [XmlElement("View")] public View view;
    View view;
    // Устанавливает активный слой.
    // [XmlElement("ActiveLayer")] public ActiveLayer activeLayer;
    ActiveLayer activeLayer;
    // Настройка отображения: единицы измерения.
    // [XmlElement("Units")] public Units Units_;
    Units Units_;
    // Настройка отображения: общие цветовые настройки.
    // [XmlElement("Colors")] public Colors Colors_;
    Colors Colors_;
    //  Настройка отображения: настройки видимости объектов.
    // [XmlElement("Show")] public Show Show_;
    Show Show_;
    //  Настройки сетки.
    // [XmlElement("Grid")] public Grid grid;
    Grid grid;
    // Настройка отображения: настройки видимости слоёв.
    // [XmlArray("LayersVisualOptions")][XmlArrayItem("LayerOptions")] public List<LayerOptions> LayersVisualOptions_;
    XmlArrayElem<LayerOptions> LayersVisualOptions;
    // Отображение цепей особым цветом.
    // [XmlElement("ColorNets")] public ColorNets colorNets;
    ColorNets colorNets;
    // Фильтр отображения связей.
    // [XmlElement("FilterNetlines")] public FilterNetlines filterNetlines;
    FilterNetlines filterNetlines;
    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DisplayControl. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/
    /**************************************************************************/
};
} // namespace TopoR
