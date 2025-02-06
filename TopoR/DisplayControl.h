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
        // [Xml::Attribute("scale", DataType = "double")] public double scale_;
        Xml::Attr<double> scale;
        // Параметр текущего вида: прокрутка по горизонтали.
        // [Xml::Attribute("scrollHorz", DataType = "double")] public double scrollHorz_;
        Xml::Attr<double> scrollHorz;
        // Параметр текущего вида: прокрутка по вертикали.
        // [Xml::Attribute("scrollVert", DataType = "double")] public double scrollVert_;
        Xml::Attr<double> scrollVert;
    };
    // Устанавливает активный слой.
    struct ActiveLayer {
        /* Опечатка в спецификации?    .
            // Тип слоя.
            [Xml::Attribute("type")]
            public LayerType type_;*/
        // Наименование слоя.

        Xml::Attr<QString> name;
    };
    // Настройка отображения: единицы измерения.
    struct Units {
        // Настройка отображения: единицы измерения.
        // [Xml::Attribute("preference")] public preference preference_;
        Xml::Attr<preference, NoOpt> preference_;
    };
    // Настройка отображения: общие цветовые настройки.
    struct Colors {
        // Настройка отображения: текущая цветовая схема.
        // [Xml::Attribute("colorScheme")] public string colorScheme_;
        Xml::Attr<QString> colorScheme;
        // Настройка отображения: яркость выделенных объектов.
        // [Xml::Attribute("hilightRate", DataType = "int")] public int hilightRate_;
        Xml::Attr<int> hilightRate;
        // int hilightRate_ = 0;
        // Настройка отображения: степень затемнения невыделенных объектов.
        // [Xml::Attribute("darkRate", DataType = "int")] public int darkRate_;
        Xml::Attr<int> darkRate;
        // int darkRate_ = 0;
        // Настройка отображения: цвет фона.
        // [Xml::Attribute("background")] public string background_;
        Xml::Attr<QString> background;
        // Настройка отображения: цвет контура платы.
        // [Xml::Attribute("board")] public string board_;
        Xml::Attr<QString> board;
        // Настройка отображения: цвет линий связей.
        // [Xml::Attribute("netLines")] public string netLines_;
        Xml::Attr<QString> netLines;
        // Настройка отображения: цвет запрета размещения на обеих сторонах платы.
        // [Xml::Attribute("keepoutPlaceBoth")] public string keepoutPlaceBoth_;
        Xml::Attr<QString> keepoutPlaceBoth;
        // Настройка отображения: цвет запрета трассировки на всех слоях.
        // [Xml::Attribute("keepoutWireAll")] public string keepoutWireAll_;
        Xml::Attr<QString> keepoutWireAll;
        // Настройка отображения: цвет запрета размещения на верхней стороне платы.
        // [Xml::Attribute("keepoutPlaceTop")] public string keepoutPlaceTop_;
        Xml::Attr<QString> keepoutPlaceTop;
        // Настройка отображения: цвет запрета размещения на нижней стороне платы.
        // [Xml::Attribute("keepoutPlaceBot")] public string keepoutPlaceBot_;
        Xml::Attr<QString> keepoutPlaceBot;
        // Настройка отображения: цвет габаритов компонентов.
        // [Xml::Attribute("compsBound")] public string compsBound_;
        Xml::Attr<QString> compsBound;
        // Настройка отображения: цвет позиционных обозначений компонентов.
        // [Xml::Attribute("compsName")] public string compsName_;
        Xml::Attr<QString> compsName;
        // Настройка отображения: цвет имён контактов.
        // [Xml::Attribute("pinsName")] public string pinsName_;
        Xml::Attr<QString> pinsName;
        // Настройка отображения: цвет имён цепей контактов.
        // [Xml::Attribute("pinsNet")] public string pinsNet_;
        Xml::Attr<QString> pinsNet;
        // Настройка отображения: цвет сквозных контактных площадок.
        // [Xml::Attribute("clrThroughPads")] public string clrThroughPads_;
        Xml::Attr<QString> clrThroughPads;
        // Настройка отображения: цвет сквозных переходных отверстий.
        // [Xml::Attribute("clrThroughVias")] public string clrThroughVias_;
        Xml::Attr<QString> clrThroughVias;
        // Настройка отображения: цвет скрытых переходных отверстий.
        // [Xml::Attribute("clrBurriedVias")] public string clrBurriedVias_;
        Xml::Attr<QString> clrBurriedVias;
        // Настройка отображения: цвет глухих переходных отверстий.
        // [Xml::Attribute("clrBlindVias")] public string clrBlindVias_;
        Xml::Attr<QString> clrBlindVias;
        // Настройка отображения: цвет зафиксированных переходных отверстий.
        // [Xml::Attribute("clrFixedVias")] public string clrFixedVias_;
        Xml::Attr<QString> clrFixedVias;
        // Настройка отображения: цвет нарушений DRC.
        // [Xml::Attribute("drcViolation")] public string drcViolation_;
        Xml::Attr<QString> drcViolation;
        // Настройка отображения: цвет индикации уменьшения номинального зазора.
        // [Xml::Attribute("narrow")] public string narrow_;
        Xml::Attr<QString> narrow;
        // Настройка отображения: цвет индикации уменьшения ширины проводника.
        // [Xml::Attribute("trimmed")] public string trimmed_;
        Xml::Attr<QString> trimmed;
    };
    // Настройка отображения: настройки видимости объектов.
    struct Show {
        Xml::Attr<Bool> blindVia;            // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        Xml::Attr<Bool> burriedVia;          // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        Xml::Attr<Bool> fixedVia;            // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        Xml::Attr<Bool> showActiveLayerOnly; // Настройка отображения: показывать только активный слой.
        Xml::Attr<Bool> showBoardOutline;    // Настройка отображения: показывать контур платы.
        Xml::Attr<Bool> showBotMechDetails;  // Настройка отображения: показывать детали на нижних металлических слоях.
        Xml::Attr<Bool> showBotMechLayers;   // Настройка отображения: показывать нижние механические слои.
        Xml::Attr<Bool> showBotMechPads;     // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        Xml::Attr<Bool> showCompBot;         // Настройка отображения: показывать компоненты на нижней стороне.
        Xml::Attr<Bool> showCompTop;         // Настройка отображения: показывать компоненты на верхней стороне.
        Xml::Attr<Bool> showComponents;      // Настройка отображения: показывать компоненты.
        Xml::Attr<Bool> showCompsBound;      // Настройка отображения: показывать габариты компонентов.
        Xml::Attr<Bool> showCompsDes;        // Настройка отображения: показывать позиционные обозначения компонентов.
        Xml::Attr<Bool> showCoppers;         // Настройка отображения: показывать области металлизации (полигоны).
        Xml::Attr<Bool> showDRCViolations;   // Настройка отображения: показывать нарушение DRC.
        Xml::Attr<Bool> showDocLayers;       // Настройка отображения: показывать документирующие слои.
        Xml::Attr<Bool> showKeepouts;        // Настройка отображения: показывать запреты.
        Xml::Attr<Bool> showLabelOther;      // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        Xml::Attr<Bool> showLabelPartName;   // Настройка отображения: показывать ярлыки атрибута PartName.
        Xml::Attr<Bool> showLabelRefDes;     // Настройка отображения: показывать ярлыки атрибута RefDes.
        Xml::Attr<Bool> showMetalPads;       // Настройка отображения: показывать контактные площадки на металлических слоях.
        Xml::Attr<Bool> showMountingHoles;   // Настройка отображения: показывать монтажные отверстия.
        Xml::Attr<Bool> showNarrow;          // Настройка отображения: показывать уменьшение номинального зазора.
        Xml::Attr<Bool> showNetLines;        // Настройка отображения: показывать связи.
        Xml::Attr<Bool> showPinsName;        // Настройка отображения: показывать имена контактов.
        Xml::Attr<Bool> showPinsNet;         // Настройка отображения: показывать имена цепей контактов.
        Xml::Attr<Bool> showPlaceKeepouts;   // Настройка отображения: показывать запреты размещения.
        Xml::Attr<Bool> showRouteKeepouts;   // Настройка отображения: показывать запреты трассировки.
        Xml::Attr<Bool> showSerpentArea;     // Настройка отображения: показывать области змеек.
        Xml::Attr<Bool> showSignalLayers;    // Настройка отображения: показывать металлические слои.
        Xml::Attr<Bool> showTexts;           // Настройка отображения: показывать ярлыки (надписи).
        Xml::Attr<Bool> showThinWires;       // Настройка отображения: показывать проводники тонкими линиями.
        Xml::Attr<Bool> showTopMechDetails;  // Настройка отображения: показывать детали на верхних металлических слоях.
        Xml::Attr<Bool> showTopMechLayers;   // Настройка отображения: показывать верхние механические слои.
        Xml::Attr<Bool> showTopMechPads;     // Настройка отображения: показывать КП на верхних металлических слоях.
        Xml::Attr<Bool> showTrimmed;         // Настройка отображения: показывать уменьшение ширины проводника.
        Xml::Attr<Bool> showVias;            // Настройка отображения: показывать переходы.
        Xml::Attr<Bool> showViolations;      // Настройка отображения: показывать нарушения.
        Xml::Attr<Bool> showWires;           // Настройка отображения: показывать проводники.
        Xml::Attr<Bool> throughPad;          // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        Xml::Attr<Bool> throughVia;          // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        Xml::Attr<QString> displayScheme;    // Настройка отображения: текущая схема отображения.
    };
    // Настройки сетки.
    struct Grid {
        // Настройка отображения сетки: шаг сетки.
        // [Xml::Element("GridSpace")] public GridSpace gridSpace;
        struct GridSpace {
            Xml::Attr<double> x, y; // шаг сетки по горизонтали и вертикали.
        } gridSpace;
        Xml::Attr<QString> gridColor;         // Настройка отображения сетки: цвет сетки.
        Xml::Attr<gridKind, NoOpt> gridKind_; // Настройка отображения сетки: тип сетки.
        Xml::Attr<Bool> gridShow;             // Настройка отображения сетки: показывать сетку.
        Xml::Attr<Bool> alignTogrid;          // Настройка ручного редактора: выравнивание на сетку.
        Xml::Attr<Bool> snapToAngle;          // Настройка ручного редактирования: привязка к углу кратному 45˚.
        Xml::Attr<Bool> saveProportion;
    };
    // Настройка отображения: настройки видимости слоя.
    struct LayerOptions {
        // Настройка отображения: цветовые настройки слоя.
        struct Colors {
            // Настройка отображения слоя: цвет деталей, проводников (основной цвет слоя).
            // [Xml::Attribute("details")] public string details_;
            Xml::Attr<QString> details;
            // Настройка отображения слоя: цвет контактных площадок.
            // [Xml::Attribute("pads")] public string pads_;
            Xml::Attr<QString> pads;
            // Настройка отображения слоя: цвет зафиксированных объектов.
            // [Xml::Attribute("fix")] public string fix_;
            Xml::Attr<QString> fix;
        };
        // Настройка отображения слоя: настройки видимости.
        struct Show {
            // Флаг видимости.
            // [Xml::Attribute("visible")] public Bool visible_;
            Xml::Attr<Bool> visible;
            // Настройка отображения слоя: видимость деталей.
            // [Xml::Attribute("details")] public Bool details_;
            Xml::Attr<Bool> details;
            // Настройка отображения слоя: видимость контактных площадок.
            // [Xml::Attribute("pads")] public Bool pads_;
            Xml::Attr<Bool> pads;
        };
        // Ссылка на слой.
        // [Xml::Element("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Настройка отображения: цветовые настройки слоя.
        // [Xml::Element("Colors")] public Colors colors;
        Colors colors;
        // Настройка отображения слоя: настройки видимости.
        // [Xml::Element("Show")] public Show show;
        Show show;
    };
    // Отображение цепей особым цветом.
    struct ColorNets {
        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        struct SetColor {
            // Отображение цепей особым цветом: задание цвета.
            // [Xml::Attribute("color")] public string color_;
            Xml::Attr<QString> color;
            // Ссылка на цепь или сигнал
            // [Xml::Element(NetRef),
            //  Xml::Element(NetGroupRef),
            //  Xml::Element(AllNets),
            //  Xml::Element(SignalRef),
            //  Xml::Element(DiffSignalRef),
            //  Xml::Element(SignalGroupRef),] public Object Refs_;
            Xml::Variant<
                NetRef,
                NetGroupRef,
                AllNets,
                SignalRef,
                DiffSignalRef,
                SignalGroupRef>
                Refs;
        };
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        // Отображение цепей особым цветом: применять для проводников.
        // [Xml::Attribute("colorizeWire")] public Bool colorizeWire_;
        Xml::Attr<Bool> colorizeWire;
        // Отображение цепей особым цветом: применять для контактных площадок.
        // [Xml::Attribute("colorizePad")] public Bool colorizePad_;
        Xml::Attr<Bool> colorizePad;
        // Отображение цепей особым цветом: применять для областей металлизации.
        // [Xml::Attribute("colorizeCopper")] public Bool colorizeCopper_;
        Xml::Attr<Bool> colorizeCopper;
        // Отображение цепей особым цветом: применять для переходов.
        // [Xml::Attribute("colorizeVia")] public Bool colorizeVia_;
        Xml::Attr<Bool> colorizeVia;
        // Отображение цепей особым цветом: применять для связей.
        // [Xml::Attribute("colorizeNetline")] public Bool colorizeNetline_;
        Xml::Attr<Bool> colorizeNetline;
        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        // [Xml::Element("SetColor")] public List<SetColor> SetColors_;
        Xml::ArrayElem<SetColor> SetColors;
    };
    // Фильтр отображения связей.
    struct FilterNetlines {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool, NoOpt> enabled;
        // Ссылки на цепь или сигнал
        // [Xml::Element(NetRef),
        //  Xml::Element(NetGroupRef),
        //  Xml::Element(AllNets),
        //  Xml::Element(SignalRef),
        //  Xml::Element(DiffSignalRef),
        //  Xml::Element(SignalGroupRef),] public List<Object> Refs_;
        Xml::ArrayElem<Xml::Variant<
            AllNets,
            DiffSignalRef,
            NetGroupRef,
            NetRef,
            SignalGroupRef,
            SignalRef>>
            Refs;
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Настройка отображения: параметры текущего вида.
    // [Xml::Element("View")] public View view;
    View view;
    // Устанавливает активный слой.
    // [Xml::Element("ActiveLayer")] public ActiveLayer activeLayer;
    ActiveLayer activeLayer;
    // Настройка отображения: единицы измерения.
    // [Xml::Element("Units")] public Units Units_;
    Units Units_;
    // Настройка отображения: общие цветовые настройки.
    // [Xml::Element("Colors")] public Colors Colors_;
    Colors Colors_;
    //  Настройка отображения: настройки видимости объектов.
    // [Xml::Element("Show")] public Show Show_;
    Show Show_;
    //  Настройки сетки.
    // [Xml::Element("Grid")] public Grid grid;
    Grid grid;
    // Настройка отображения: настройки видимости слоёв.
    // [Xml::Array("LayersVisualOptions")][Xml::ArrayItem("LayerOptions")] public List<LayerOptions> LayersVisualOptions_;
    Xml::ArrayElem<LayerOptions> LayersVisualOptions;
    // Отображение цепей особым цветом.
    // [Xml::Element("ColorNets")] public ColorNets colorNets;
    ColorNets colorNets;
    // Фильтр отображения связей.
    // [Xml::Element("FilterNetlines")] public FilterNetlines filterNetlines;
    FilterNetlines filterNetlines;
    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DisplayControl. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/
};
} // namespace TopoR
