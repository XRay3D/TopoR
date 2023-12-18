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
        // [XmlAttribute("scale", DataType = "float")] public float scale_;
        XmlAttr<float> scale;
        // Параметр текущего вида: прокрутка по горизонтали.
        // [XmlAttribute("scrollHorz", DataType = "float")] public float scrollHorz_;
        XmlAttr<float> scrollHorz;
        // Параметр текущего вида: прокрутка по вертикали.
        // [XmlAttribute("scrollVert", DataType = "float")] public float scrollVert_;
        XmlAttr<float> scrollVert;
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
        // Настройка отображения: текущая схема отображения.
        // [XmlAttribute("displayScheme")] public string displayScheme_;
        XmlAttr<QString> displayScheme;
        // Настройка отображения: показывать контур платы.
        // [XmlAttribute("showBoardOutline")] public Bool showBoardOutline_;
        XmlAttr<Bool> showBoardOutline;
        /* public bool showBoardOutlineSpecified_ */
        // Настройка отображения: показывать проводники.
        // [XmlAttribute("showWires")] public Bool showWires_;
        XmlAttr<Bool> showWires;
        /* public bool showWiresSpecified_ */
        // Настройка отображения: показывать области металлизации (полигоны).
        // [XmlAttribute("showCoppers")] public Bool showCoppers_;
        XmlAttr<Bool> showCoppers;
        /* public bool showCoppersSpecified_ */
        // Настройка отображения: показывать ярлыки (надписи).
        // [XmlAttribute("showTexts")] public Bool showTexts_;
        XmlAttr<Bool> showTexts;
        /* public bool showTextsSpecified_ */
        // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        // [XmlAttribute("throughPad")] public Bool throughPad_;
        XmlAttr<Bool> throughPad;
        /* public bool throughPadSpecified_ */
        // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        // [XmlAttribute("throughVia")] public Bool throughVia_;
        XmlAttr<Bool> throughVia;
        /* public bool throughViaSpecified_ */
        // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        // [XmlAttribute("burriedVia")] public Bool burriedVia_;
        XmlAttr<Bool> burriedVia;
        /* public bool burriedViaSpecified_ */
        // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        // [XmlAttribute("blindVia")] public Bool blindVia_;
        XmlAttr<Bool> blindVia;
        /* public bool blindViaSpecified_ */
        // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        // [XmlAttribute("fixedVia")] public Bool fixedVia_;
        XmlAttr<Bool> fixedVia;
        /* public bool fixedViaSpecified_ */
        // Настройка отображения: показывать переходы.
        // [XmlAttribute("showVias")] public Bool showVias_;
        XmlAttr<Bool> showVias;
        /* public bool showViasSpecified_ */
        // Настройка отображения: показывать металлические слои.
        // [XmlAttribute("showSignalLayers")] public Bool showSignalLayers_;
        XmlAttr<Bool> showSignalLayers;
        /* public bool showSignalLayersSpecified_ */
        // Настройка отображения: показывать верхние механические слои.
        // [XmlAttribute("showTopMechLayers")] public Bool showTopMechLayers_;
        XmlAttr<Bool> showTopMechLayers;
        /* public bool showTopMechLayersSpecified_ */
        // Настройка отображения: показывать нижние механические слои.
        // [XmlAttribute("showBotMechLayers")] public Bool showBotMechLayers_;
        XmlAttr<Bool> showBotMechLayers;
        /* public bool showBotMechLayersSpecified_ */
        // Настройка отображения: показывать документирующие слои.
        // [XmlAttribute("showDocLayers")] public Bool showDocLayers_;
        XmlAttr<Bool> showDocLayers;
        /* public bool showDocLayersSpecified_ */
        // Настройка отображения: показывать детали на верхних металлических слоях.
        // [XmlAttribute("showTopMechDetails")] public Bool showTopMechDetails_;
        XmlAttr<Bool> showTopMechDetails;
        /* public bool showTopMechDetailsSpecified_ */
        // Настройка отображения: показывать детали на нижних металлических слоях.
        // [XmlAttribute("showBotMechDetails")] public Bool showBotMechDetails_;
        XmlAttr<Bool> showBotMechDetails;
        /* public bool showBotMechDetailsSpecified_ */
        // Настройка отображения: показывать контактные площадки на металлических слоях.
        // [XmlAttribute("showMetalPads")] public Bool showMetalPads_;
        XmlAttr<Bool> showMetalPads;
        /* public bool showMetalPadsSpecified_ */
        // Настройка отображения: показывать КП на верхних металлических слоях.
        // [XmlAttribute("showTopMechPads")] public Bool showTopMechPads_;
        XmlAttr<Bool> showTopMechPads;
        /* public bool showTopMechPadsSpecified_ */
        // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        // [XmlAttribute("showBotMechPads")] public Bool showBotMechPads_;
        XmlAttr<Bool> showBotMechPads;
        /* public bool showBotMechPadsSpecified_ */
        // Настройка отображения: показывать связи.
        // [XmlAttribute("showNetLines")] public Bool showNetLines_;
        XmlAttr<Bool> showNetLines;
        /* public bool showNetLinesSpecified_ */
        // Настройка отображения: показывать монтажные отверстия.
        // [XmlAttribute("showMountingHoles")] public Bool showMountingHoles_;
        XmlAttr<Bool> showMountingHoles;
        /* public bool showMountingHolesSpecified_ */
        // Настройка отображения: показывать проводники тонкими линиями.
        // [XmlAttribute("showThinWires")] public Bool showThinWires_;
        XmlAttr<Bool> showThinWires;
        /* public bool showThinWiresSpecified_ */
        // Настройка отображения: показывать компоненты.
        // [XmlAttribute("showComponents")] public Bool showComponents_;
        XmlAttr<Bool> showComponents;
        /* public bool showComponentsSpecified_ */
        // Настройка отображения: показывать компоненты на верхней стороне.
        // [XmlAttribute("showCompTop")] public Bool showCompTop_;
        XmlAttr<Bool> showCompTop;
        /* public bool showCompTopSpecified_ */
        // Настройка отображения: показывать компоненты на нижней стороне.
        // [XmlAttribute("showCompBot")] public Bool showCompBot_;
        XmlAttr<Bool> showCompBot;
        /* public bool showCompBotSpecified_ */
        // Настройка отображения: показывать позиционные обозначения компонентов.
        // [XmlAttribute("showCompsDes")] public Bool showCompsDes_;
        XmlAttr<Bool> showCompsDes;
        /* public bool showCompsDesSpecified_ */
        // Настройка отображения: показывать имена контактов.
        // [XmlAttribute("showPinsName")] public Bool showPinsName_;
        XmlAttr<Bool> showPinsName;
        /* public bool showPinsNameSpecified_ */
        // Настройка отображения: показывать имена цепей контактов.
        // [XmlAttribute("showPinsNet")] public Bool showPinsNet_;
        XmlAttr<Bool> showPinsNet;
        /* public bool showPinsNetSpecified_ */
        // Настройка отображения: показывать габариты компонентов.
        // [XmlAttribute("showCompsBound")] public Bool showCompsBound_;
        XmlAttr<Bool> showCompsBound;
        /* public bool showCompsBoundSpecified_ */
        // Настройка отображения: показывать ярлыки атрибута RefDes.
        // [XmlAttribute("showLabelRefDes")] public Bool showLabelRefDes_;
        XmlAttr<Bool> showLabelRefDes;
        /* public bool showLabelRefDesSpecified_ */
        // Настройка отображения: показывать ярлыки атрибута PartName.
        // [XmlAttribute("showLabelPartName")] public Bool showLabelPartName_;
        XmlAttr<Bool> showLabelPartName;
        /* public bool showLabelPartNameSpecified_ */
        // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        // [XmlAttribute("showLabelOther")] public Bool showLabelOther_;
        XmlAttr<Bool> showLabelOther;
        /* public bool showLabelOtherSpecified_ */
        // Настройка отображения: показывать нарушения.
        // [XmlAttribute("showViolations")] public Bool showViolations_;
        XmlAttr<Bool> showViolations;
        /* public bool showViolationsSpecified_ */
        // Настройка отображения: показывать уменьшение номинального зазора.
        // [XmlAttribute("showNarrow")] public Bool showNarrow_;
        XmlAttr<Bool> showNarrow;
        /* public bool showNarrowSpecified_ */
        // Настройка отображения: показывать уменьшение ширины проводника.
        // [XmlAttribute("showTrimmed")] public Bool showTrimmed_;
        XmlAttr<Bool> showTrimmed;
        /* public bool showTrimmedSpecified_ */
        // Настройка отображения: показывать нарушение DRC.
        // [XmlAttribute("showDRCViolations")] public Bool showDRCViolations_;
        XmlAttr<Bool> showDRCViolations;
        /* public bool showDRCViolationsSpecified_ */
        // Настройка отображения: показывать запреты.
        // [XmlAttribute("showKeepouts")] public Bool showKeepouts_;
        XmlAttr<Bool> showKeepouts;
        /* public bool showKeepoutsSpecified_ */
        // Настройка отображения: показывать запреты трассировки.
        // [XmlAttribute("showRouteKeepouts")] public Bool showRouteKeepouts_;
        XmlAttr<Bool> showRouteKeepouts;
        /* public bool showRouteKeepoutsSpecified_ */
        // Настройка отображения: показывать запреты размещения.
        // [XmlAttribute("showPlaceKeepouts")] public Bool showPlaceKeepouts_;
        XmlAttr<Bool> showPlaceKeepouts;
        /* public bool showPlaceKeepoutsSpecified_ */
        // Настройка отображения: показывать только активный слой.
        // [XmlAttribute("showActiveLayerOnly")] public Bool showActiveLayerOnly_;
        XmlAttr<Bool> showActiveLayerOnly;
        /* public bool showActiveLayerOnlySpecified_ */
        // Настройка отображения: показывать области змеек.
        // [XmlAttribute("showSerpentArea")] public Bool showSerpentArea_;
        XmlAttr<Bool> showSerpentArea;
        /* public bool showSerpentAreaSpecified_ */
    };
    // Настройки сетки.
    struct Grid {
        // Настройка отображения сетки: шаг сетки.
        struct GridSpace {
            // шаг сетки по горизонтали.
            // [XmlAttribute("x", DataType = "float")] public float x_;
            XmlAttr<float> x;
            // шаг сетки по вертикали.
            // [XmlAttribute("y", DataType = "float")] public float y_;
            XmlAttr<float> y;
        };
        // Настройка отображения сетки: цвет сетки.
        // [XmlAttribute("gridColor")] public string gridColor_;
        XmlAttr<QString> gridColor;
        // Настройка отображения сетки: тип сетки.
        // [XmlAttribute("gridKind")] public gridKind gridKind_;
        XmlAttr<gridKind> gridKind_;
        // Настройка отображения сетки: показывать сетку.
        // [XmlAttribute("gridShow")] public Bool gridShow_;
        XmlAttr<Bool> gridShow;
        /* public bool gridShowSpecified_ */
        // Настройка ручного редактора: выравнивание на сетку.
        // [XmlAttribute("alignToGrid")] public Bool alignTogrid;
        XmlAttr<Bool> alignTogrid;
        /* public bool alignToGridSpecified_ */
        // Настройка ручного редактирования: привязка к углу кратному 45˚.
        // [XmlAttribute("snapToAngle")] public Bool snapToAngle_;
        XmlAttr<Bool> snapToAngle;
        /* public bool snapToAngleSpecified_ */
        // Настройка отображения сетки: шаг сетки.
        // [XmlElement("GridSpace")] public GridSpace gridSpace;
        GridSpace gridSpace;
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
            XmlAttr<Bool> visible;
            /* public bool visibleSpecified_ */
            // Настройка отображения слоя: видимость деталей.
            // [XmlAttribute("details")] public Bool details_;
            XmlAttr<Bool> details;
            /* public bool detailsSpecified_ */
            // Настройка отображения слоя: видимость контактных площадок.
            // [XmlAttribute("pads")] public Bool pads_;
            XmlAttr<Bool> pads;
            /* public bool padsSpecified_ */
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
        /* public bool enabledSpecified_ */
        // Отображение цепей особым цветом: применять для проводников.
        // [XmlAttribute("colorizeWire")] public Bool colorizeWire_;
        XmlAttr<Bool> colorizeWire;
        /* public bool colorizeWireSpecified_ */
        // Отображение цепей особым цветом: применять для контактных площадок.
        // [XmlAttribute("colorizePad")] public Bool colorizePad_;
        XmlAttr<Bool> colorizePad;
        /* public bool colorizePadSpecified_ */
        // Отображение цепей особым цветом: применять для областей металлизации.
        // [XmlAttribute("colorizeCopper")] public Bool colorizeCopper_;
        XmlAttr<Bool> colorizeCopper;
        /* public bool colorizeCopperSpecified_ */
        // Отображение цепей особым цветом: применять для переходов.
        // [XmlAttribute("colorizeVia")] public Bool colorizeVia_;
        XmlAttr<Bool> colorizeVia;
        /* public bool colorizeViaSpecified_ */
        // Отображение цепей особым цветом: применять для связей.
        // [XmlAttribute("colorizeNetline")] public Bool colorizeNetline_;
        XmlAttr<Bool> colorizeNetline;
        /* public bool colorizeNetlineSpecified_ */
        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        // [XmlElement("SetColor")] public List<SetColor> SetColors_;
        XmlArrayElem<SetColor> SetColors;
    };
    // Фильтр отображения связей.
    struct FilterNetlines {
        // Флаг применения правила.
        // [XmlAttribute("enabled")] public Bool enabled_;
        XmlAttr<Bool> enabled;
        /* public bool enabledSpecified_ */
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
