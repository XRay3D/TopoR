#pragma once

#include "Commons.h"

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Настройки отображения».
struct DisplayControl {

    // Настройка отображения: параметры текущего вида.
    struct View {

        // Параметр текущего вида: масштаб.
        /* [XmlAttribute("scale", DataType = "float")] public float scale_; */
        XmlAttr<float> scale;
        //        float scale_ = 0.0F;

        // Параметр текущего вида: прокрутка по горизонтали.
        /* [XmlAttribute("scrollHorz", DataType = "float")] public float scrollHorz_; */
        XmlAttr<float> scrollHorz;
        // float scrollHorz_ = 0.0F;

        // Параметр текущего вида: прокрутка по вертикали.
        /* [XmlAttribute("scrollVert", DataType = "float")] public float scrollVert_; */
        XmlAttr<float> scrollVert;
        // float scrollVert_ = 0.0F;
    };

    // Устанавливает активный слой.
    struct ActiveLayer {
        /* Опечатка в спецификации?    .
            // Тип слоя.
            [XmlAttribute("type")]
            public layer_type type_;*/

        // Наименование слоя.
        /* [XmlAttribute("name")] public string name_; */
        QString name;
    };

    // Настройка отображения: единицы измерения.
    struct Units_DisplayControl {

        // Настройка отображения: единицы измерения.
        /* [XmlAttribute("preference")] public preference preference_; */
        preference preference_{};
    };

    // Настройка отображения: общие цветовые настройки.
    struct Colors_DisplayControl {

        // Настройка отображения: текущая цветовая схема.
        /* [XmlAttribute("colorScheme")] public string colorScheme_; */
        QString colorScheme;

        // Настройка отображения: яркость выделенных объектов.
        /* [XmlAttribute("hilightRate", DataType = "int")] public int hilightRate_; */
        XmlAttr<int> hilightRate;
        // int hilightRate_ = 0;

        // Настройка отображения: степень затемнения невыделенных объектов.
        /* [XmlAttribute("darkRate", DataType = "int")] public int darkRate_; */
        XmlAttr<int> darkRate;
        // int darkRate_ = 0;

        // Настройка отображения: цвет фона.
        /* [XmlAttribute("background")] public string background_; */
        QString background;

        // Настройка отображения: цвет контура платы.
        /* [XmlAttribute("board")] public string board_; */
        QString board;

        // Настройка отображения: цвет линий связей.
        /* [XmlAttribute("netLines")] public string netLines_; */
        QString netLines;

        // Настройка отображения: цвет запрета размещения на обеих сторонах платы.
        /* [XmlAttribute("keepoutPlaceBoth")] public string keepoutPlaceBoth_; */
        QString keepoutPlaceBoth;

        // Настройка отображения: цвет запрета трассировки на всех слоях.
        /* [XmlAttribute("keepoutWireAll")] public string keepoutWireAll_; */
        QString keepoutWireAll;

        // Настройка отображения: цвет запрета размещения на верхней стороне платы.
        /* [XmlAttribute("keepoutPlaceTop")] public string keepoutPlaceTop_; */
        QString keepoutPlaceTop;

        // Настройка отображения: цвет запрета размещения на нижней стороне платы.
        /* [XmlAttribute("keepoutPlaceBot")] public string keepoutPlaceBot_; */
        QString keepoutPlaceBot;

        // Настройка отображения: цвет габаритов компонентов.
        /* [XmlAttribute("compsBound")] public string compsBound_; */
        QString compsBound;

        // Настройка отображения: цвет позиционных обозначений компонентов.
        /* [XmlAttribute("compsName")] public string compsName_; */
        QString compsName;

        // Настройка отображения: цвет имён контактов.
        /* [XmlAttribute("pinsName")] public string pinsName_; */
        QString pinsName;

        // Настройка отображения: цвет имён цепей контактов.
        /* [XmlAttribute("pinsNet")] public string pinsNet_; */
        QString pinsNet;

        // Настройка отображения: цвет сквозных контактных площадок.
        /* [XmlAttribute("clrThroughPads")] public string clrThroughPads_; */
        QString clrThroughPads;

        // Настройка отображения: цвет сквозных переходных отверстий.
        /* [XmlAttribute("clrThroughVias")] public string clrThroughVias_; */
        QString clrThroughVias;

        // Настройка отображения: цвет скрытых переходных отверстий.
        /* [XmlAttribute("clrBurriedVias")] public string clrBurriedVias_; */
        QString clrBurriedVias;

        // Настройка отображения: цвет глухих переходных отверстий.
        /* [XmlAttribute("clrBlindVias")] public string clrBlindVias_; */
        QString clrBlindVias;

        // Настройка отображения: цвет зафиксированных переходных отверстий.
        /* [XmlAttribute("clrFixedVias")] public string clrFixedVias_; */
        QString clrFixedVias;

        // Настройка отображения: цвет нарушений DRC.
        /* [XmlAttribute("drcViolation")] public string drcViolation_; */
        QString drcViolation;

        // Настройка отображения: цвет индикации уменьшения номинального зазора.
        /* [XmlAttribute("narrow")] public string narrow_; */
        QString narrow;

        // Настройка отображения: цвет индикации уменьшения ширины проводника.
        /* [XmlAttribute("trimmed")] public string trimmed_; */
        QString trimmed;
    };

    // Настройка отображения: настройки видимости объектов.
    struct Show_DisplayControl {

        // Настройка отображения: текущая схема отображения.
        /* [XmlAttribute("displayScheme")] public string displayScheme_; */
        QString displayScheme;

        // Настройка отображения: показывать контур платы.
        /* [XmlAttribute("showBoardOutline")] public Bool showBoardOutline_; */
        Bool showBoardOutline_{};
        /* public bool showBoardOutlineSpecified_ */

        // Настройка отображения: показывать проводники.
        /* [XmlAttribute("showWires")] public Bool showWires_; */
        Bool showWires_{};
        /* public bool showWiresSpecified_ */

        // Настройка отображения: показывать области металлизации (полигоны).
        /* [XmlAttribute("showCoppers")] public Bool showCoppers_; */
        Bool showCoppers_{};
        /* public bool showCoppersSpecified_ */

        // Настройка отображения: показывать ярлыки (надписи).
        /* [XmlAttribute("showTexts")] public Bool showTexts_; */
        Bool showTexts_{};
        /* public bool showTextsSpecified_ */

        // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        /* [XmlAttribute("throughPad")] public Bool throughPad_; */
        Bool throughPad_{};
        /* public bool throughPadSpecified_ */

        // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        /* [XmlAttribute("throughVia")] public Bool throughVia_; */
        Bool throughVia_{};
        /* public bool throughViaSpecified_ */

        // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        /* [XmlAttribute("burriedVia")] public Bool burriedVia_; */
        Bool burriedVia_{};
        /* public bool burriedViaSpecified_ */

        // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        /* [XmlAttribute("blindVia")] public Bool blindVia_; */
        Bool blindVia_{};
        /* public bool blindViaSpecified_ */

        // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        /* [XmlAttribute("fixedVia")] public Bool fixedVia_; */
        Bool fixedVia_{};
        /* public bool fixedViaSpecified_ */

        // Настройка отображения: показывать переходы.
        /* [XmlAttribute("showVias")] public Bool showVias_; */
        Bool showVias_{};
        /* public bool showViasSpecified_ */

        // Настройка отображения: показывать металлические слои.
        /* [XmlAttribute("showSignalLayers")] public Bool showSignalLayers_; */
        Bool showSignalLayers_{};
        /* public bool showSignalLayersSpecified_ */

        // Настройка отображения: показывать верхние механические слои.
        /* [XmlAttribute("showTopMechLayers")] public Bool showTopMechLayers_; */
        Bool showTopMechLayers_{};
        /* public bool showTopMechLayersSpecified_ */

        // Настройка отображения: показывать нижние механические слои.
        /* [XmlAttribute("showBotMechLayers")] public Bool showBotMechLayers_; */
        Bool showBotMechLayers_{};
        /* public bool showBotMechLayersSpecified_ */

        // Настройка отображения: показывать документирующие слои.
        /* [XmlAttribute("showDocLayers")] public Bool showDocLayers_; */
        Bool showDocLayers_{};
        /* public bool showDocLayersSpecified_ */

        // Настройка отображения: показывать детали на верхних металлических слоях.
        /* [XmlAttribute("showTopMechDetails")] public Bool showTopMechDetails_; */
        Bool showTopMechDetails_{};
        /* public bool showTopMechDetailsSpecified_ */

        // Настройка отображения: показывать детали на нижних металлических слоях.
        /* [XmlAttribute("showBotMechDetails")] public Bool showBotMechDetails_; */
        Bool showBotMechDetails_{};
        /* public bool showBotMechDetailsSpecified_ */

        // Настройка отображения: показывать контактные площадки на металлических слоях.
        /* [XmlAttribute("showMetalPads")] public Bool showMetalPads_; */
        Bool showMetalPads_{};
        /* public bool showMetalPadsSpecified_ */

        // Настройка отображения: показывать КП на верхних металлических слоях.
        /* [XmlAttribute("showTopMechPads")] public Bool showTopMechPads_; */
        Bool showTopMechPads_{};
        /* public bool showTopMechPadsSpecified_ */

        // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        /* [XmlAttribute("showBotMechPads")] public Bool showBotMechPads_; */
        Bool showBotMechPads_{};
        /* public bool showBotMechPadsSpecified_ */

        // Настройка отображения: показывать связи.
        /* [XmlAttribute("showNetLines")] public Bool showNetLines_; */
        Bool showNetLines_{};
        /* public bool showNetLinesSpecified_ */

        // Настройка отображения: показывать монтажные отверстия.
        /* [XmlAttribute("showMountingHoles")] public Bool showMountingHoles_; */
        Bool showMountingHoles_{};
        /* public bool showMountingHolesSpecified_ */

        // Настройка отображения: показывать проводники тонкими линиями.
        /* [XmlAttribute("showThinWires")] public Bool showThinWires_; */
        Bool showThinWires_{};
        /* public bool showThinWiresSpecified_ */

        // Настройка отображения: показывать компоненты.
        /* [XmlAttribute("showComponents")] public Bool showComponents_; */
        Bool showComponents_{};
        /* public bool showComponentsSpecified_ */

        // Настройка отображения: показывать компоненты на верхней стороне.
        /* [XmlAttribute("showCompTop")] public Bool showCompTop_; */
        Bool showCompTop_{};
        /* public bool showCompTopSpecified_ */

        // Настройка отображения: показывать компоненты на нижней стороне.
        /* [XmlAttribute("showCompBot")] public Bool showCompBot_; */
        Bool showCompBot_{};
        /* public bool showCompBotSpecified_ */

        // Настройка отображения: показывать позиционные обозначения компонентов.
        /* [XmlAttribute("showCompsDes")] public Bool showCompsDes_; */
        Bool showCompsDes_{};
        /* public bool showCompsDesSpecified_ */

        // Настройка отображения: показывать имена контактов.
        /* [XmlAttribute("showPinsName")] public Bool showPinsName_; */
        Bool showPinsName_{};
        /* public bool showPinsNameSpecified_ */

        // Настройка отображения: показывать имена цепей контактов.
        /* [XmlAttribute("showPinsNet")] public Bool showPinsNet_; */
        Bool showPinsNet_{};
        /* public bool showPinsNetSpecified_ */

        // Настройка отображения: показывать габариты компонентов.
        /* [XmlAttribute("showCompsBound")] public Bool showCompsBound_; */
        Bool showCompsBound_{};
        /* public bool showCompsBoundSpecified_ */

        // Настройка отображения: показывать ярлыки атрибута RefDes.
        /* [XmlAttribute("showLabelRefDes")] public Bool showLabelRefDes_; */
        Bool showLabelRefDes_{};
        /* public bool showLabelRefDesSpecified_ */

        // Настройка отображения: показывать ярлыки атрибута PartName.
        /* [XmlAttribute("showLabelPartName")] public Bool showLabelPartName_; */
        Bool showLabelPartName_{};
        /* public bool showLabelPartNameSpecified_ */

        // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        /* [XmlAttribute("showLabelOther")] public Bool showLabelOther_; */
        Bool showLabelOther_{};
        /* public bool showLabelOtherSpecified_ */

        // Настройка отображения: показывать нарушения.
        /* [XmlAttribute("showViolations")] public Bool showViolations_; */
        Bool showViolations_{};
        /* public bool showViolationsSpecified_ */

        // Настройка отображения: показывать уменьшение номинального зазора.
        /* [XmlAttribute("showNarrow")] public Bool showNarrow_; */
        Bool showNarrow_{};
        /* public bool showNarrowSpecified_ */

        // Настройка отображения: показывать уменьшение ширины проводника.
        /* [XmlAttribute("showTrimmed")] public Bool showTrimmed_; */
        Bool showTrimmed_{};
        /* public bool showTrimmedSpecified_ */

        // Настройка отображения: показывать нарушение DRC.
        /* [XmlAttribute("showDRCViolations")] public Bool showDRCViolations_; */
        Bool showDRCViolations_{};
        /* public bool showDRCViolationsSpecified_ */

        // Настройка отображения: показывать запреты.
        /* [XmlAttribute("showKeepouts")] public Bool showKeepouts_; */
        Bool showKeepouts_{};
        /* public bool showKeepoutsSpecified_ */

        // Настройка отображения: показывать запреты трассировки.
        /* [XmlAttribute("showRouteKeepouts")] public Bool showRouteKeepouts_; */
        Bool showRouteKeepouts_{};
        /* public bool showRouteKeepoutsSpecified_ */

        // Настройка отображения: показывать запреты размещения.
        /* [XmlAttribute("showPlaceKeepouts")] public Bool showPlaceKeepouts_; */
        Bool showPlaceKeepouts_{};
        /* public bool showPlaceKeepoutsSpecified_ */

        // Настройка отображения: показывать только активный слой.
        /* [XmlAttribute("showActiveLayerOnly")] public Bool showActiveLayerOnly_; */
        Bool showActiveLayerOnly_{};
        /* public bool showActiveLayerOnlySpecified_ */

        // Настройка отображения: показывать области змеек.
        /* [XmlAttribute("showSerpentArea")] public Bool showSerpentArea_; */
        Bool showSerpentArea_{};
        /* public bool showSerpentAreaSpecified_ */
    };

    // Настройки сетки.
    struct Grid {

        // Настройка отображения сетки: шаг сетки.
        struct GridSpace {
            // шаг сетки по горизонтали.
            /* [XmlAttribute("x", DataType = "float")] public float x_; */
            XmlAttr<float> x;
            // float x_ = 0.0F;

            // шаг сетки по вертикали.
            /* [XmlAttribute("y", DataType = "float")] public float y_; */
            XmlAttr<float> y;
            // float y_ = 0.0F;
        };

        // Настройка отображения сетки: цвет сетки.
        /* [XmlAttribute("gridColor")] public string gridColor_; */
        QString gridColor;

        // Настройка отображения сетки: тип сетки.
        /* [XmlAttribute("gridKind")] public gridKind gridKind_; */
        gridKind gridKind_{};

        // Настройка отображения сетки: показывать сетку.
        /* [XmlAttribute("gridShow")] public Bool gridShow_; */
        Bool gridShow_{};
        /* public bool gridShowSpecified_ */

        // Настройка ручного редактора: выравнивание на сетку.
        /* [XmlAttribute("alignToGrid")] public Bool alignToGrid_; */
        Bool alignToGrid_{};
        /* public bool alignToGridSpecified_ */

        // Настройка ручного редактирования: привязка к углу кратному 45˚.
        /* [XmlAttribute("snapToAngle")] public Bool snapToAngle_; */
        Bool snapToAngle_{};
        /* public bool snapToAngleSpecified_ */

        // Настройка отображения сетки: шаг сетки.
        /* [XmlElement("GridSpace")] public GridSpace GridSpace_; */
        GridSpace GridSpace_;
    };

    // Настройка отображения: настройки видимости слоя.
    struct LayerOptions {

        // Настройка отображения: цветовые настройки слоя.
        struct Colors_LayerOptions {

            // Настройка отображения слоя: цвет деталей, проводников (основной цвет слоя).
            /* [XmlAttribute("details")] public string details_; */
            QString details;

            // Настройка отображения слоя: цвет контактных площадок.
            /* [XmlAttribute("pads")] public string pads_; */
            QString pads;

            // Настройка отображения слоя: цвет зафиксированных объектов.
            /* [XmlAttribute("fix")] public string fix_; */
            QString fix;
        };

        // Настройка отображения слоя: настройки видимости.
        struct Show_LayerOptions {

            // Флаг видимости.
            /* [XmlAttribute("visible")] public Bool visible_; */
            Bool visible_{};
            /* public bool visibleSpecified_ */

            // Настройка отображения слоя: видимость деталей.
            /* [XmlAttribute("details")] public Bool details_; */
            Bool details_{};
            /* public bool detailsSpecified_ */

            // Настройка отображения слоя: видимость контактных площадок.
            /* [XmlAttribute("pads")] public Bool pads_; */
            Bool pads_{};
            /* public bool padsSpecified_ */
        };

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
        LayerRef LayerRef_;

        // Настройка отображения: цветовые настройки слоя.
        /* [XmlElement("Colors")] public Colors_LayerOptions Colors_; */
        Colors_LayerOptions Colors_;

        // Настройка отображения слоя: настройки видимости.
        /* [XmlElement("Show")] public Show_LayerOptions Show_; */
        Show_LayerOptions Show_;
    };

    // Отображение цепей особым цветом.
    struct ColorNets {

        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        struct SetColor {

            // Отображение цепей особым цветом: задание цвета.
            /* [XmlAttribute("color")] public string color_; */
            QString color;

            // Ссылка на цепь или сигнал
            /* [XmlElement("NetRef", typeof(NetRef)),
                XmlElement("NetGroupRef", typeof(NetGroupRef)),
                XmlElement("AllNets", typeof(AllNets)),
                XmlElement("SignalRef", typeof(SignalRef)),
                XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
                XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object Refs_; */
            XmlVariant<
                NetRef,
                NetGroupRef,
                AllNets,
                SignalRef,
                DiffSignalRef,
                SignalGroupRef>
                Refs_;
        };

        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */

        // Отображение цепей особым цветом: применять для проводников.
        /* [XmlAttribute("colorizeWire")] public Bool colorizeWire_; */
        Bool colorizeWire_{};
        /* public bool colorizeWireSpecified_ */

        // Отображение цепей особым цветом: применять для контактных площадок.
        /* [XmlAttribute("colorizePad")] public Bool colorizePad_; */
        Bool colorizePad_{};
        /* public bool colorizePadSpecified_ */

        // Отображение цепей особым цветом: применять для областей металлизации.
        /* [XmlAttribute("colorizeCopper")] public Bool colorizeCopper_; */
        Bool colorizeCopper_{};
        /* public bool colorizeCopperSpecified_ */

        // Отображение цепей особым цветом: применять для переходов.
        /* [XmlAttribute("colorizeVia")] public Bool colorizeVia_; */
        Bool colorizeVia_{};
        /* public bool colorizeViaSpecified_ */

        // Отображение цепей особым цветом: применять для связей.
        /* [XmlAttribute("colorizeNetline")] public Bool colorizeNetline_; */
        Bool colorizeNetline_{};
        /* public bool colorizeNetlineSpecified_ */

        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        /* [XmlElement("SetColor")] public List<SetColor> SetColors_; */
        std::vector<SetColor> SetColors;
    };

    // Фильтр отображения связей.
    struct FilterNetlines {

        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */

        // Ссылки на цепь или сигнал
        /* [XmlElement("NetRef", typeof(NetRef)),
        XmlElement("NetGroupRef", typeof(NetGroupRef)),
        XmlElement("AllNets", typeof(AllNets)),
        XmlElement("SignalRef", typeof(SignalRef)),
        XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
        XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public List<Object> Refs_; */
        std::vector<XmlVariant<
            AllNets,
            DiffSignalRef,
            NetGroupRef,
            NetRef,
            SignalGroupRef,
            SignalRef>>
            Refs_;
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    QString version;

    // Настройка отображения: параметры текущего вида.
    /* [XmlElement("View")] public View View_; */
    View View_;

    // Устанавливает активный слой.
    /* [XmlElement("ActiveLayer")] public ActiveLayer ActiveLayer_; */
    ActiveLayer ActiveLayer_;

    // Настройка отображения: единицы измерения.
    /* [XmlElement("Units")] public Units_DisplayControl Units_; */
    Units_DisplayControl Units_;

    // Настройка отображения: общие цветовые настройки.
    /* [XmlElement("Colors")] public Colors_DisplayControl Colors_; */
    Colors_DisplayControl Colors_;

    //  Настройка отображения: настройки видимости объектов.
    /* [XmlElement("Show")] public Show_DisplayControl Show_; */
    Show_DisplayControl Show_;

    //  Настройки сетки.
    /* [XmlElement("Grid")] public Grid Grid_; */
    Grid Grid_;

    // Настройка отображения: настройки видимости слоёв.
    /* [XmlArray("LayersVisualOptions")][XmlArrayItem("LayerOptions")] public List<LayerOptions> LayersVisualOptions_; */
    std::vector<LayerOptions> LayersVisualOptions;

    // Отображение цепей особым цветом.
    /* [XmlElement("ColorNets")] public ColorNets ColorNets_; */
    ColorNets ColorNets_;

    // Фильтр отображения связей.
    /* [XmlElement("FilterNetlines")] public FilterNetlines FilterNetlines_; */
    FilterNetlines FilterNetlines_;

    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DisplayControl. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/

    /**************************************************************************/
};

} // namespace TopoR_PCB_Classes
