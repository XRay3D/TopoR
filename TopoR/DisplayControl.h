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
        //        float _scale = 0.0F;

        // Параметр текущего вида: прокрутка по горизонтали.
        /* [XmlAttribute("scrollHorz", DataType = "float")] public float scrollHorz_; */
        XmlAttr<float> scrollHorz;
        // float _scrollHorz = 0.0F;

        // Параметр текущего вида: прокрутка по вертикали.
        /* [XmlAttribute("scrollVert", DataType = "float")] public float scrollVert_; */
        XmlAttr<float> scrollVert;
        // float _scrollVert = 0.0F;
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
        preference _preference{};
    };

    // Настройка отображения: общие цветовые настройки.
    struct Colors_DisplayControl {

        // Настройка отображения: текущая цветовая схема.
        /* [XmlAttribute("colorScheme")] public string colorScheme_; */
        QString colorScheme;

        // Настройка отображения: яркость выделенных объектов.
        /* [XmlAttribute("hilightRate", DataType = "int")] public int hilightRate_; */
        XmlAttr<int> hilightRate;
        // int _hilightRate = 0;

        // Настройка отображения: степень затемнения невыделенных объектов.
        /* [XmlAttribute("darkRate", DataType = "int")] public int darkRate_; */
        XmlAttr<int> darkRate;
        // int _darkRate = 0;

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
        Bool _showBoardOutline{};
        /* public bool _showBoardOutlineSpecified */
        bool getShowBoardOutlineSpecified() const;

        // Настройка отображения: показывать проводники.
        /* [XmlAttribute("showWires")] public Bool showWires_; */
        Bool _showWires{};
        /* public bool _showWiresSpecified */
        bool getShowWiresSpecified() const;

        // Настройка отображения: показывать области металлизации (полигоны).
        /* [XmlAttribute("showCoppers")] public Bool showCoppers_; */
        Bool _showCoppers{};
        /* public bool _showCoppersSpecified */
        bool getShowCoppersSpecified() const;

        // Настройка отображения: показывать ярлыки (надписи).
        /* [XmlAttribute("showTexts")] public Bool showTexts_; */
        Bool _showTexts{};
        /* public bool _showTextsSpecified */
        bool getShowTextsSpecified() const;

        // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        /* [XmlAttribute("throughPad")] public Bool throughPad_; */
        Bool _throughPad{};
        /* public bool _throughPadSpecified */
        bool getThroughPadSpecified() const;

        // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        /* [XmlAttribute("throughVia")] public Bool throughVia_; */
        Bool _throughVia{};
        /* public bool _throughViaSpecified */
        bool getThroughViaSpecified() const;

        // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        /* [XmlAttribute("burriedVia")] public Bool burriedVia_; */
        Bool _burriedVia{};
        /* public bool _burriedViaSpecified */
        bool getBurriedViaSpecified() const;

        // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        /* [XmlAttribute("blindVia")] public Bool blindVia_; */
        Bool _blindVia{};
        /* public bool _blindViaSpecified */
        bool getBlindViaSpecified() const;

        // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        /* [XmlAttribute("fixedVia")] public Bool fixedVia_; */
        Bool _fixedVia{};
        /* public bool _fixedViaSpecified */
        bool getFixedViaSpecified() const;

        // Настройка отображения: показывать переходы.
        /* [XmlAttribute("showVias")] public Bool showVias_; */
        Bool _showVias{};
        /* public bool _showViasSpecified */
        bool getShowViasSpecified() const;

        // Настройка отображения: показывать металлические слои.
        /* [XmlAttribute("showSignalLayers")] public Bool showSignalLayers_; */
        Bool _showSignalLayers{};
        /* public bool _showSignalLayersSpecified */
        bool getShowSignalLayersSpecified() const;

        // Настройка отображения: показывать верхние механические слои.
        /* [XmlAttribute("showTopMechLayers")] public Bool showTopMechLayers_; */
        Bool _showTopMechLayers{};
        /* public bool _showTopMechLayersSpecified */
        bool getShowTopMechLayersSpecified() const;

        // Настройка отображения: показывать нижние механические слои.
        /* [XmlAttribute("showBotMechLayers")] public Bool showBotMechLayers_; */
        Bool _showBotMechLayers{};
        /* public bool _showBotMechLayersSpecified */
        bool getShowBotMechLayersSpecified() const;

        // Настройка отображения: показывать документирующие слои.
        /* [XmlAttribute("showDocLayers")] public Bool showDocLayers_; */
        Bool _showDocLayers{};
        /* public bool _showDocLayersSpecified */
        bool getShowDocLayersSpecified() const;

        // Настройка отображения: показывать детали на верхних металлических слоях.
        /* [XmlAttribute("showTopMechDetails")] public Bool showTopMechDetails_; */
        Bool _showTopMechDetails{};
        /* public bool _showTopMechDetailsSpecified */
        bool getShowTopMechDetailsSpecified() const;

        // Настройка отображения: показывать детали на нижних металлических слоях.
        /* [XmlAttribute("showBotMechDetails")] public Bool showBotMechDetails_; */
        Bool _showBotMechDetails{};
        /* public bool _showBotMechDetailsSpecified */
        bool getShowBotMechDetailsSpecified() const;

        // Настройка отображения: показывать контактные площадки на металлических слоях.
        /* [XmlAttribute("showMetalPads")] public Bool showMetalPads_; */
        Bool _showMetalPads{};
        /* public bool _showMetalPadsSpecified */
        bool getShowMetalPadsSpecified() const;

        // Настройка отображения: показывать КП на верхних металлических слоях.
        /* [XmlAttribute("showTopMechPads")] public Bool showTopMechPads_; */
        Bool _showTopMechPads{};
        /* public bool _showTopMechPadsSpecified */
        bool getShowTopMechPadsSpecified() const;

        // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        /* [XmlAttribute("showBotMechPads")] public Bool showBotMechPads_; */
        Bool _showBotMechPads{};
        /* public bool _showBotMechPadsSpecified */
        bool getShowBotMechPadsSpecified() const;

        // Настройка отображения: показывать связи.
        /* [XmlAttribute("showNetLines")] public Bool showNetLines_; */
        Bool _showNetLines{};
        /* public bool _showNetLinesSpecified */
        bool getShowNetLinesSpecified() const;

        // Настройка отображения: показывать монтажные отверстия.
        /* [XmlAttribute("showMountingHoles")] public Bool showMountingHoles_; */
        Bool _showMountingHoles{};
        /* public bool _showMountingHolesSpecified */
        bool getShowMountingHolesSpecified() const;

        // Настройка отображения: показывать проводники тонкими линиями.
        /* [XmlAttribute("showThinWires")] public Bool showThinWires_; */
        Bool _showThinWires{};
        /* public bool _showThinWiresSpecified */
        bool getShowThinWiresSpecified() const;

        // Настройка отображения: показывать компоненты.
        /* [XmlAttribute("showComponents")] public Bool showComponents_; */
        Bool _showComponents{};
        /* public bool _showComponentsSpecified */
        bool getShowComponentsSpecified() const;

        // Настройка отображения: показывать компоненты на верхней стороне.
        /* [XmlAttribute("showCompTop")] public Bool showCompTop_; */
        Bool _showCompTop{};
        /* public bool _showCompTopSpecified */
        bool getShowCompTopSpecified() const;

        // Настройка отображения: показывать компоненты на нижней стороне.
        /* [XmlAttribute("showCompBot")] public Bool showCompBot_; */
        Bool _showCompBot{};
        /* public bool _showCompBotSpecified */
        bool getShowCompBotSpecified() const;

        // Настройка отображения: показывать позиционные обозначения компонентов.
        /* [XmlAttribute("showCompsDes")] public Bool showCompsDes_; */
        Bool _showCompsDes{};
        /* public bool _showCompsDesSpecified */
        bool getShowCompsDesSpecified() const;

        // Настройка отображения: показывать имена контактов.
        /* [XmlAttribute("showPinsName")] public Bool showPinsName_; */
        Bool _showPinsName{};
        /* public bool _showPinsNameSpecified */
        bool getShowPinsNameSpecified() const;

        // Настройка отображения: показывать имена цепей контактов.
        /* [XmlAttribute("showPinsNet")] public Bool showPinsNet_; */
        Bool _showPinsNet{};
        /* public bool _showPinsNetSpecified */
        bool getShowPinsNetSpecified() const;

        // Настройка отображения: показывать габариты компонентов.
        /* [XmlAttribute("showCompsBound")] public Bool showCompsBound_; */
        Bool _showCompsBound{};
        /* public bool _showCompsBoundSpecified */
        bool getShowCompsBoundSpecified() const;

        // Настройка отображения: показывать ярлыки атрибута RefDes.
        /* [XmlAttribute("showLabelRefDes")] public Bool showLabelRefDes_; */
        Bool _showLabelRefDes{};
        /* public bool _showLabelRefDesSpecified */
        bool getShowLabelRefDesSpecified() const;

        // Настройка отображения: показывать ярлыки атрибута PartName.
        /* [XmlAttribute("showLabelPartName")] public Bool showLabelPartName_; */
        Bool _showLabelPartName{};
        /* public bool _showLabelPartNameSpecified */
        bool getShowLabelPartNameSpecified() const;

        // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        /* [XmlAttribute("showLabelOther")] public Bool showLabelOther_; */
        Bool _showLabelOther{};
        /* public bool _showLabelOtherSpecified */
        bool getShowLabelOtherSpecified() const;

        // Настройка отображения: показывать нарушения.
        /* [XmlAttribute("showViolations")] public Bool showViolations_; */
        Bool _showViolations{};
        /* public bool _showViolationsSpecified */
        bool getShowViolationsSpecified() const;

        // Настройка отображения: показывать уменьшение номинального зазора.
        /* [XmlAttribute("showNarrow")] public Bool showNarrow_; */
        Bool _showNarrow{};
        /* public bool _showNarrowSpecified */
        bool getShowNarrowSpecified() const;

        // Настройка отображения: показывать уменьшение ширины проводника.
        /* [XmlAttribute("showTrimmed")] public Bool showTrimmed_; */
        Bool _showTrimmed{};
        /* public bool _showTrimmedSpecified */
        bool getShowTrimmedSpecified() const;

        // Настройка отображения: показывать нарушение DRC.
        /* [XmlAttribute("showDRCViolations")] public Bool showDRCViolations_; */
        Bool _showDRCViolations{};
        /* public bool _showDRCViolationsSpecified */
        bool getShowDRCViolationsSpecified() const;

        // Настройка отображения: показывать запреты.
        /* [XmlAttribute("showKeepouts")] public Bool showKeepouts_; */
        Bool _showKeepouts{};
        /* public bool _showKeepoutsSpecified */
        bool getShowKeepoutsSpecified() const;

        // Настройка отображения: показывать запреты трассировки.
        /* [XmlAttribute("showRouteKeepouts")] public Bool showRouteKeepouts_; */
        Bool _showRouteKeepouts{};
        /* public bool _showRouteKeepoutsSpecified */
        bool getShowRouteKeepoutsSpecified() const;

        // Настройка отображения: показывать запреты размещения.
        /* [XmlAttribute("showPlaceKeepouts")] public Bool showPlaceKeepouts_; */
        Bool _showPlaceKeepouts{};
        /* public bool _showPlaceKeepoutsSpecified */
        bool getShowPlaceKeepoutsSpecified() const;

        // Настройка отображения: показывать только активный слой.
        /* [XmlAttribute("showActiveLayerOnly")] public Bool showActiveLayerOnly_; */
        Bool _showActiveLayerOnly{};
        /* public bool _showActiveLayerOnlySpecified */
        bool getShowActiveLayerOnlySpecified() const;

        // Настройка отображения: показывать области змеек.
        /* [XmlAttribute("showSerpentArea")] public Bool showSerpentArea_; */
        Bool _showSerpentArea{};
        /* public bool _showSerpentAreaSpecified */
        bool getShowSerpentAreaSpecified() const;
    };

    // Настройки сетки.
    struct Grid {

        // Настройка отображения сетки: шаг сетки.
        struct GridSpace {
            // шаг сетки по горизонтали.
            /* [XmlAttribute("x", DataType = "float")] public float x_; */
            XmlAttr<float> x;
            // float _x = 0.0F;

            // шаг сетки по вертикали.
            /* [XmlAttribute("y", DataType = "float")] public float y_; */
            XmlAttr<float> y;
            // float _y = 0.0F;
        };

        // Настройка отображения сетки: цвет сетки.
        /* [XmlAttribute("gridColor")] public string gridColor_; */
        QString gridColor;

        // Настройка отображения сетки: тип сетки.
        /* [XmlAttribute("gridKind")] public gridKind gridKind_; */
        gridKind _gridKind{};

        // Настройка отображения сетки: показывать сетку.
        /* [XmlAttribute("gridShow")] public Bool gridShow_; */
        Bool _gridShow{};
        /* public bool _gridShowSpecified */
        bool getGridShowSpecified() const;

        // Настройка ручного редактора: выравнивание на сетку.
        /* [XmlAttribute("alignToGrid")] public Bool alignToGrid_; */
        Bool _alignToGrid{};
        /* public bool _alignToGridSpecified */
        bool getAlignToGridSpecified() const;

        // Настройка ручного редактирования: привязка к углу кратному 45˚.
        /* [XmlAttribute("snapToAngle")] public Bool snapToAngle_; */
        Bool _snapToAngle{};
        /* public bool _snapToAngleSpecified */
        bool getSnapToAngleSpecified() const;

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
            Bool _visible{};
            /* public bool _visibleSpecified */
            bool getVisibleSpecified() const;

            // Настройка отображения слоя: видимость деталей.
            /* [XmlAttribute("details")] public Bool details_; */
            Bool _details{};
            /* public bool _detailsSpecified */
            bool getDetailsSpecified() const;

            // Настройка отображения слоя: видимость контактных площадок.
            /* [XmlAttribute("pads")] public Bool pads_; */
            Bool _pads{};
            /* public bool _padsSpecified */
            bool getPadsSpecified() const;
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
        Bool _enabled{};
        /* public bool _enabledSpecified */
        bool getEnabledSpecified() const;

        // Отображение цепей особым цветом: применять для проводников.
        /* [XmlAttribute("colorizeWire")] public Bool colorizeWire_; */
        Bool _colorizeWire{};
        /* public bool _colorizeWireSpecified */
        bool getColorizeWireSpecified() const;

        // Отображение цепей особым цветом: применять для контактных площадок.
        /* [XmlAttribute("colorizePad")] public Bool colorizePad_; */
        Bool _colorizePad{};
        /* public bool _colorizePadSpecified */
        bool getColorizePadSpecified() const;

        // Отображение цепей особым цветом: применять для областей металлизации.
        /* [XmlAttribute("colorizeCopper")] public Bool colorizeCopper_; */
        Bool _colorizeCopper{};
        /* public bool _colorizeCopperSpecified */
        bool getColorizeCopperSpecified() const;

        // Отображение цепей особым цветом: применять для переходов.
        /* [XmlAttribute("colorizeVia")] public Bool colorizeVia_; */
        Bool _colorizeVia{};
        /* public bool _colorizeViaSpecified */
        bool getColorizeViaSpecified() const;

        // Отображение цепей особым цветом: применять для связей.
        /* [XmlAttribute("colorizeNetline")] public Bool colorizeNetline_; */
        Bool _colorizeNetline{};
        /* public bool _colorizeNetlineSpecified */
        bool getColorizeNetlineSpecified() const;

        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        /* [XmlElement("SetColor")] public List<SetColor> SetColors_; */
        std::vector<SetColor> SetColors;
        bool ShouldSerialize_SetColors();
    };

    // Фильтр отображения связей.
    struct FilterNetlines {

        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool _enabled{};
        /* public bool _enabledSpecified */
        bool getEnabledSpecified() const;

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
        bool ShouldSerialize_Refs();
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
    bool ShouldSerialize_LayersVisualOptions();

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
