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
        /* [XmlAttribute("scale", DataType = "float")] public float _scale; */
        Attribute<float> scale;
        //        float _scale = 0.0F;

        // Параметр текущего вида: прокрутка по горизонтали.
        /* [XmlAttribute("scrollHorz", DataType = "float")] public float _scrollHorz; */
        Attribute<float> scrollHorz;
        // float _scrollHorz = 0.0F;

        // Параметр текущего вида: прокрутка по вертикали.
        /* [XmlAttribute("scrollVert", DataType = "float")] public float _scrollVert; */
        Attribute<float> scrollVert;
        // float _scrollVert = 0.0F;
    };

    // Устанавливает активный слой.
    struct ActiveLayer {
        /* Опечатка в спецификации?    .
            // Тип слоя.
            [XmlAttribute("type")]
            public layer_type _type;*/

        // Наименование слоя.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;
    };

    // Настройка отображения: единицы измерения.
    struct Units_DisplayControl {

        // Настройка отображения: единицы измерения.
        /* [XmlAttribute("preference")] public preference _preference; */
        preference _preference{};
    };

    // Настройка отображения: общие цветовые настройки.
    struct Colors_DisplayControl {

        // Настройка отображения: текущая цветовая схема.
        /* [XmlAttribute("colorScheme")] public string _colorScheme; */
        QString _colorScheme;

        // Настройка отображения: яркость выделенных объектов.
        /* [XmlAttribute("hilightRate", DataType = "int")] public int _hilightRate; */
        Attribute<int> hilightRate;
        // int _hilightRate = 0;

        // Настройка отображения: степень затемнения невыделенных объектов.
        /* [XmlAttribute("darkRate", DataType = "int")] public int _darkRate; */
        Attribute<int> darkRate;
        // int _darkRate = 0;

        // Настройка отображения: цвет фона.
        /* [XmlAttribute("background")] public string _background; */
        QString _background;

        // Настройка отображения: цвет контура платы.
        /* [XmlAttribute("board")] public string _board; */
        QString _board;

        // Настройка отображения: цвет линий связей.
        /* [XmlAttribute("netLines")] public string _netLines; */
        QString _netLines;

        // Настройка отображения: цвет запрета размещения на обеих сторонах платы.
        /* [XmlAttribute("keepoutPlaceBoth")] public string _keepoutPlaceBoth; */
        QString _keepoutPlaceBoth;

        // Настройка отображения: цвет запрета трассировки на всех слоях.
        /* [XmlAttribute("keepoutWireAll")] public string _keepoutWireAll; */
        QString _keepoutWireAll;

        // Настройка отображения: цвет запрета размещения на верхней стороне платы.
        /* [XmlAttribute("keepoutPlaceTop")] public string _keepoutPlaceTop; */
        QString _keepoutPlaceTop;

        // Настройка отображения: цвет запрета размещения на нижней стороне платы.
        /* [XmlAttribute("keepoutPlaceBot")] public string _keepoutPlaceBot; */
        QString _keepoutPlaceBot;

        // Настройка отображения: цвет габаритов компонентов.
        /* [XmlAttribute("compsBound")] public string _compsBound; */
        QString _compsBound;

        // Настройка отображения: цвет позиционных обозначений компонентов.
        /* [XmlAttribute("compsName")] public string _compsName; */
        QString _compsName;

        // Настройка отображения: цвет имён контактов.
        /* [XmlAttribute("pinsName")] public string _pinsName; */
        QString _pinsName;

        // Настройка отображения: цвет имён цепей контактов.
        /* [XmlAttribute("pinsNet")] public string _pinsNet; */
        QString _pinsNet;

        // Настройка отображения: цвет сквозных контактных площадок.
        /* [XmlAttribute("clrThroughPads")] public string _clrThroughPads; */
        QString _clrThroughPads;

        // Настройка отображения: цвет сквозных переходных отверстий.
        /* [XmlAttribute("clrThroughVias")] public string _clrThroughVias; */
        QString _clrThroughVias;

        // Настройка отображения: цвет скрытых переходных отверстий.
        /* [XmlAttribute("clrBurriedVias")] public string _clrBurriedVias; */
        QString _clrBurriedVias;

        // Настройка отображения: цвет глухих переходных отверстий.
        /* [XmlAttribute("clrBlindVias")] public string _clrBlindVias; */
        QString _clrBlindVias;

        // Настройка отображения: цвет зафиксированных переходных отверстий.
        /* [XmlAttribute("clrFixedVias")] public string _clrFixedVias; */
        QString _clrFixedVias;

        // Настройка отображения: цвет нарушений DRC.
        /* [XmlAttribute("drcViolation")] public string _drcViolation; */
        QString _drcViolation;

        // Настройка отображения: цвет индикации уменьшения номинального зазора.
        /* [XmlAttribute("narrow")] public string _narrow; */
        QString _narrow;

        // Настройка отображения: цвет индикации уменьшения ширины проводника.
        /* [XmlAttribute("trimmed")] public string _trimmed; */
        QString _trimmed;
    };

    // Настройка отображения: настройки видимости объектов.
    struct Show_DisplayControl {

        // Настройка отображения: текущая схема отображения.
        /* [XmlAttribute("displayScheme")] public string _displayScheme; */
        QString _displayScheme;

        // Настройка отображения: показывать контур платы.
        /* [XmlAttribute("showBoardOutline")] public Bool _showBoardOutline; */
        Bool _showBoardOutline{};
        /* [XmlIgnore] public bool _showBoardOutlineSpecified */
        bool getShowBoardOutlineSpecified() const;

        // Настройка отображения: показывать проводники.
        /* [XmlAttribute("showWires")] public Bool _showWires; */
        Bool _showWires{};
        /* [XmlIgnore] public bool _showWiresSpecified */
        bool getShowWiresSpecified() const;

        // Настройка отображения: показывать области металлизации (полигоны).
        /* [XmlAttribute("showCoppers")] public Bool _showCoppers; */
        Bool _showCoppers{};
        /* [XmlIgnore] public bool _showCoppersSpecified */
        bool getShowCoppersSpecified() const;

        // Настройка отображения: показывать ярлыки (надписи).
        /* [XmlAttribute("showTexts")] public Bool _showTexts; */
        Bool _showTexts{};
        /* [XmlIgnore] public bool _showTextsSpecified */
        bool getShowTextsSpecified() const;

        // Настройка отображения: показывать сквозные контактные площадки специальным цветом.
        /* [XmlAttribute("throughPad")] public Bool _throughPad; */
        Bool _throughPad{};
        /* [XmlIgnore] public bool _throughPadSpecified */
        bool getThroughPadSpecified() const;

        // Настройка отображения: показывать сквозные переходные отверстия специальным цветом.
        /* [XmlAttribute("throughVia")] public Bool _throughVia; */
        Bool _throughVia{};
        /* [XmlIgnore] public bool _throughViaSpecified */
        bool getThroughViaSpecified() const;

        // Настройка отображения: показывать скрытые переходные отверстия специальным цветом
        /* [XmlAttribute("burriedVia")] public Bool _burriedVia; */
        Bool _burriedVia{};
        /* [XmlIgnore] public bool _burriedViaSpecified */
        bool getBurriedViaSpecified() const;

        // Настройка отображения: показывать глухие переходные отверстия специальным цветом.
        /* [XmlAttribute("blindVia")] public Bool _blindVia; */
        Bool _blindVia{};
        /* [XmlIgnore] public bool _blindViaSpecified */
        bool getBlindViaSpecified() const;

        // Настройка отображения: показывать фиксированные переходные отверстия специальным цветом.
        /* [XmlAttribute("fixedVia")] public Bool _fixedVia; */
        Bool _fixedVia{};
        /* [XmlIgnore] public bool _fixedViaSpecified */
        bool getFixedViaSpecified() const;

        // Настройка отображения: показывать переходы.
        /* [XmlAttribute("showVias")] public Bool _showVias; */
        Bool _showVias{};
        /* [XmlIgnore] public bool _showViasSpecified */
        bool getShowViasSpecified() const;

        // Настройка отображения: показывать металлические слои.
        /* [XmlAttribute("showSignalLayers")] public Bool _showSignalLayers; */
        Bool _showSignalLayers{};
        /* [XmlIgnore] public bool _showSignalLayersSpecified */
        bool getShowSignalLayersSpecified() const;

        // Настройка отображения: показывать верхние механические слои.
        /* [XmlAttribute("showTopMechLayers")] public Bool _showTopMechLayers; */
        Bool _showTopMechLayers{};
        /* [XmlIgnore] public bool _showTopMechLayersSpecified */
        bool getShowTopMechLayersSpecified() const;

        // Настройка отображения: показывать нижние механические слои.
        /* [XmlAttribute("showBotMechLayers")] public Bool _showBotMechLayers; */
        Bool _showBotMechLayers{};
        /* [XmlIgnore] public bool _showBotMechLayersSpecified */
        bool getShowBotMechLayersSpecified() const;

        // Настройка отображения: показывать документирующие слои.
        /* [XmlAttribute("showDocLayers")] public Bool _showDocLayers; */
        Bool _showDocLayers{};
        /* [XmlIgnore] public bool _showDocLayersSpecified */
        bool getShowDocLayersSpecified() const;

        // Настройка отображения: показывать детали на верхних металлических слоях.
        /* [XmlAttribute("showTopMechDetails")] public Bool _showTopMechDetails; */
        Bool _showTopMechDetails{};
        /* [XmlIgnore] public bool _showTopMechDetailsSpecified */
        bool getShowTopMechDetailsSpecified() const;

        // Настройка отображения: показывать детали на нижних металлических слоях.
        /* [XmlAttribute("showBotMechDetails")] public Bool _showBotMechDetails; */
        Bool _showBotMechDetails{};
        /* [XmlIgnore] public bool _showBotMechDetailsSpecified */
        bool getShowBotMechDetailsSpecified() const;

        // Настройка отображения: показывать контактные площадки на металлических слоях.
        /* [XmlAttribute("showMetalPads")] public Bool _showMetalPads; */
        Bool _showMetalPads{};
        /* [XmlIgnore] public bool _showMetalPadsSpecified */
        bool getShowMetalPadsSpecified() const;

        // Настройка отображения: показывать КП на верхних металлических слоях.
        /* [XmlAttribute("showTopMechPads")] public Bool _showTopMechPads; */
        Bool _showTopMechPads{};
        /* [XmlIgnore] public bool _showTopMechPadsSpecified */
        bool getShowTopMechPadsSpecified() const;

        // Настройка отображения: показывать контактные площадки на нижних металлических слоях.
        /* [XmlAttribute("showBotMechPads")] public Bool _showBotMechPads; */
        Bool _showBotMechPads{};
        /* [XmlIgnore] public bool _showBotMechPadsSpecified */
        bool getShowBotMechPadsSpecified() const;

        // Настройка отображения: показывать связи.
        /* [XmlAttribute("showNetLines")] public Bool _showNetLines; */
        Bool _showNetLines{};
        /* [XmlIgnore] public bool _showNetLinesSpecified */
        bool getShowNetLinesSpecified() const;

        // Настройка отображения: показывать монтажные отверстия.
        /* [XmlAttribute("showMountingHoles")] public Bool _showMountingHoles; */
        Bool _showMountingHoles{};
        /* [XmlIgnore] public bool _showMountingHolesSpecified */
        bool getShowMountingHolesSpecified() const;

        // Настройка отображения: показывать проводники тонкими линиями.
        /* [XmlAttribute("showThinWires")] public Bool _showThinWires; */
        Bool _showThinWires{};
        /* [XmlIgnore] public bool _showThinWiresSpecified */
        bool getShowThinWiresSpecified() const;

        // Настройка отображения: показывать компоненты.
        /* [XmlAttribute("showComponents")] public Bool _showComponents; */
        Bool _showComponents{};
        /* [XmlIgnore] public bool _showComponentsSpecified */
        bool getShowComponentsSpecified() const;

        // Настройка отображения: показывать компоненты на верхней стороне.
        /* [XmlAttribute("showCompTop")] public Bool _showCompTop; */
        Bool _showCompTop{};
        /* [XmlIgnore] public bool _showCompTopSpecified */
        bool getShowCompTopSpecified() const;

        // Настройка отображения: показывать компоненты на нижней стороне.
        /* [XmlAttribute("showCompBot")] public Bool _showCompBot; */
        Bool _showCompBot{};
        /* [XmlIgnore] public bool _showCompBotSpecified */
        bool getShowCompBotSpecified() const;

        // Настройка отображения: показывать позиционные обозначения компонентов.
        /* [XmlAttribute("showCompsDes")] public Bool _showCompsDes; */
        Bool _showCompsDes{};
        /* [XmlIgnore] public bool _showCompsDesSpecified */
        bool getShowCompsDesSpecified() const;

        // Настройка отображения: показывать имена контактов.
        /* [XmlAttribute("showPinsName")] public Bool _showPinsName; */
        Bool _showPinsName{};
        /* [XmlIgnore] public bool _showPinsNameSpecified */
        bool getShowPinsNameSpecified() const;

        // Настройка отображения: показывать имена цепей контактов.
        /* [XmlAttribute("showPinsNet")] public Bool _showPinsNet; */
        Bool _showPinsNet{};
        /* [XmlIgnore] public bool _showPinsNetSpecified */
        bool getShowPinsNetSpecified() const;

        // Настройка отображения: показывать габариты компонентов.
        /* [XmlAttribute("showCompsBound")] public Bool _showCompsBound; */
        Bool _showCompsBound{};
        /* [XmlIgnore] public bool _showCompsBoundSpecified */
        bool getShowCompsBoundSpecified() const;

        // Настройка отображения: показывать ярлыки атрибута RefDes.
        /* [XmlAttribute("showLabelRefDes")] public Bool _showLabelRefDes; */
        Bool _showLabelRefDes{};
        /* [XmlIgnore] public bool _showLabelRefDesSpecified */
        bool getShowLabelRefDesSpecified() const;

        // Настройка отображения: показывать ярлыки атрибута PartName.
        /* [XmlAttribute("showLabelPartName")] public Bool _showLabelPartName; */
        Bool _showLabelPartName{};
        /* [XmlIgnore] public bool _showLabelPartNameSpecified */
        bool getShowLabelPartNameSpecified() const;

        // Настройка отображения: показывать ярлыки пользовательских атрибутов.
        /* [XmlAttribute("showLabelOther")] public Bool _showLabelOther; */
        Bool _showLabelOther{};
        /* [XmlIgnore] public bool _showLabelOtherSpecified */
        bool getShowLabelOtherSpecified() const;

        // Настройка отображения: показывать нарушения.
        /* [XmlAttribute("showViolations")] public Bool _showViolations; */
        Bool _showViolations{};
        /* [XmlIgnore] public bool _showViolationsSpecified */
        bool getShowViolationsSpecified() const;

        // Настройка отображения: показывать уменьшение номинального зазора.
        /* [XmlAttribute("showNarrow")] public Bool _showNarrow; */
        Bool _showNarrow{};
        /* [XmlIgnore] public bool _showNarrowSpecified */
        bool getShowNarrowSpecified() const;

        // Настройка отображения: показывать уменьшение ширины проводника.
        /* [XmlAttribute("showTrimmed")] public Bool _showTrimmed; */
        Bool _showTrimmed{};
        /* [XmlIgnore] public bool _showTrimmedSpecified */
        bool getShowTrimmedSpecified() const;

        // Настройка отображения: показывать нарушение DRC.
        /* [XmlAttribute("showDRCViolations")] public Bool _showDRCViolations; */
        Bool _showDRCViolations{};
        /* [XmlIgnore] public bool _showDRCViolationsSpecified */
        bool getShowDRCViolationsSpecified() const;

        // Настройка отображения: показывать запреты.
        /* [XmlAttribute("showKeepouts")] public Bool _showKeepouts; */
        Bool _showKeepouts{};
        /* [XmlIgnore] public bool _showKeepoutsSpecified */
        bool getShowKeepoutsSpecified() const;

        // Настройка отображения: показывать запреты трассировки.
        /* [XmlAttribute("showRouteKeepouts")] public Bool _showRouteKeepouts; */
        Bool _showRouteKeepouts{};
        /* [XmlIgnore] public bool _showRouteKeepoutsSpecified */
        bool getShowRouteKeepoutsSpecified() const;

        // Настройка отображения: показывать запреты размещения.
        /* [XmlAttribute("showPlaceKeepouts")] public Bool _showPlaceKeepouts; */
        Bool _showPlaceKeepouts{};
        /* [XmlIgnore] public bool _showPlaceKeepoutsSpecified */
        bool getShowPlaceKeepoutsSpecified() const;

        // Настройка отображения: показывать только активный слой.
        /* [XmlAttribute("showActiveLayerOnly")] public Bool _showActiveLayerOnly; */
        Bool _showActiveLayerOnly{};
        /* [XmlIgnore] public bool _showActiveLayerOnlySpecified */
        bool getShowActiveLayerOnlySpecified() const;

        // Настройка отображения: показывать области змеек.
        /* [XmlAttribute("showSerpentArea")] public Bool _showSerpentArea; */
        Bool _showSerpentArea{};
        /* [XmlIgnore] public bool _showSerpentAreaSpecified */
        bool getShowSerpentAreaSpecified() const;
    };

    // Настройки сетки.
    struct Grid {

        // Настройка отображения сетки: шаг сетки.
        struct GridSpace {
            // шаг сетки по горизонтали.
            /* [XmlAttribute("x", DataType = "float")] public float _x; */
            Attribute<float> x;
            // float _x = 0.0F;

            // шаг сетки по вертикали.
            /* [XmlAttribute("y", DataType = "float")] public float _y; */
            Attribute<float> y;
            // float _y = 0.0F;
        };

        // Настройка отображения сетки: цвет сетки.
        /* [XmlAttribute("gridColor")] public string _gridColor; */
        QString _gridColor;

        // Настройка отображения сетки: тип сетки.
        /* [XmlAttribute("gridKind")] public gridKind _gridKind; */
        gridKind _gridKind{};

        // Настройка отображения сетки: показывать сетку.
        /* [XmlAttribute("gridShow")] public Bool _gridShow; */
        Bool _gridShow{};
        /* [XmlIgnore] public bool _gridShowSpecified */
        bool getGridShowSpecified() const;

        // Настройка ручного редактора: выравнивание на сетку.
        /* [XmlAttribute("alignToGrid")] public Bool _alignToGrid; */
        Bool _alignToGrid{};
        /* [XmlIgnore] public bool _alignToGridSpecified */
        bool getAlignToGridSpecified() const;

        // Настройка ручного редактирования: привязка к углу кратному 45˚.
        /* [XmlAttribute("snapToAngle")] public Bool _snapToAngle; */
        Bool _snapToAngle{};
        /* [XmlIgnore] public bool _snapToAngleSpecified */
        bool getSnapToAngleSpecified() const;

        // Настройка отображения сетки: шаг сетки.
        /* [XmlElement("GridSpace")] public GridSpace _GridSpace; */
        GridSpace _GridSpace;
    };

    // Настройка отображения: настройки видимости слоя.
    struct LayerOptions {

        // Настройка отображения: цветовые настройки слоя.
        struct Colors_LayerOptions {

            // Настройка отображения слоя: цвет деталей, проводников (основной цвет слоя).
            /* [XmlAttribute("details")] public string _details; */
            QString _details;

            // Настройка отображения слоя: цвет контактных площадок.
            /* [XmlAttribute("pads")] public string _pads; */
            QString _pads;

            // Настройка отображения слоя: цвет зафиксированных объектов.
            /* [XmlAttribute("fix")] public string _fix; */
            QString _fix;
        };

        // Настройка отображения слоя: настройки видимости.
        struct Show_LayerOptions {

            // Флаг видимости.
            /* [XmlAttribute("visible")] public Bool _visible; */
            Bool _visible{};
            /* [XmlIgnore] public bool _visibleSpecified */
            bool getVisibleSpecified() const;

            // Настройка отображения слоя: видимость деталей.
            /* [XmlAttribute("details")] public Bool _details; */
            Bool _details{};
            /* [XmlIgnore] public bool _detailsSpecified */
            bool getDetailsSpecified() const;

            // Настройка отображения слоя: видимость контактных площадок.
            /* [XmlAttribute("pads")] public Bool _pads; */
            Bool _pads{};
            /* [XmlIgnore] public bool _padsSpecified */
            bool getPadsSpecified() const;
        };

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
        LayerRef _LayerRef;

        // Настройка отображения: цветовые настройки слоя.
        /* [XmlElement("Colors")] public Colors_LayerOptions _Colors; */
        Colors_LayerOptions _Colors;

        // Настройка отображения слоя: настройки видимости.
        /* [XmlElement("Show")] public Show_LayerOptions _Show; */
        Show_LayerOptions _Show;
    };

    // Отображение цепей особым цветом.
    struct ColorNets {

        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        struct SetColor {

            // Отображение цепей особым цветом: задание цвета.
            /* [XmlAttribute("color")] public string _color; */
            QString _color;

            // Ссылка на цепь или сигнал
            /* [XmlElement("NetRef", typeof(NetRef)),
                XmlElement("NetGroupRef", typeof(NetGroupRef)),
                XmlElement("AllNets", typeof(AllNets)),
                XmlElement("SignalRef", typeof(SignalRef)),
                XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
                XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object _Refs; */
            std::variant<
                NetRef,
                NetGroupRef,
                AllNets,
                SignalRef,
                DiffSignalRef,
                SignalGroupRef>
                _Refs;
        };

        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool _enabled; */
        Bool _enabled{};
        /* [XmlIgnore] public bool _enabledSpecified */
        bool getEnabledSpecified() const;

        // Отображение цепей особым цветом: применять для проводников.
        /* [XmlAttribute("colorizeWire")] public Bool _colorizeWire; */
        Bool _colorizeWire{};
        /* [XmlIgnore] public bool _colorizeWireSpecified */
        bool getColorizeWireSpecified() const;

        // Отображение цепей особым цветом: применять для контактных площадок.
        /* [XmlAttribute("colorizePad")] public Bool _colorizePad; */
        Bool _colorizePad{};
        /* [XmlIgnore] public bool _colorizePadSpecified */
        bool getColorizePadSpecified() const;

        // Отображение цепей особым цветом: применять для областей металлизации.
        /* [XmlAttribute("colorizeCopper")] public Bool _colorizeCopper; */
        Bool _colorizeCopper{};
        /* [XmlIgnore] public bool _colorizeCopperSpecified */
        bool getColorizeCopperSpecified() const;

        // Отображение цепей особым цветом: применять для переходов.
        /* [XmlAttribute("colorizeVia")] public Bool _colorizeVia; */
        Bool _colorizeVia{};
        /* [XmlIgnore] public bool _colorizeViaSpecified */
        bool getColorizeViaSpecified() const;

        // Отображение цепей особым цветом: применять для связей.
        /* [XmlAttribute("colorizeNetline")] public Bool _colorizeNetline; */
        Bool _colorizeNetline{};
        /* [XmlIgnore] public bool _colorizeNetlineSpecified */
        bool getColorizeNetlineSpecified() const;

        // Отображение цепей особым цветом: установить цвет для цепи / сигнала / группы цепей / группы сигналов.
        /* [XmlElement("SetColor")] public List<SetColor> _SetColors; */
        std::vector<SetColor> _SetColors;
        bool ShouldSerialize_SetColors();
    };

    // Фильтр отображения связей.
    struct FilterNetlines {

        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool _enabled; */
        Bool _enabled{};
        /* [XmlIgnore] public bool _enabledSpecified */
        bool getEnabledSpecified() const;

        // Ссылки на цепь или сигнал
        /* [XmlElement("NetRef", typeof(NetRef)),
        XmlElement("NetGroupRef", typeof(NetGroupRef)),
        XmlElement("AllNets", typeof(AllNets)),
        XmlElement("SignalRef", typeof(SignalRef)),
        XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
        XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public List<Object> _Refs; */
        std::vector<std::variant<
            AllNets,
            DiffSignalRef,
            NetGroupRef,
            NetRef,
            SignalGroupRef,
            SignalRef>>
            _Refs;
        bool ShouldSerialize_Refs();
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string _version; */
    QString _version;

    // Настройка отображения: параметры текущего вида.
    /* [XmlElement("View")] public View _View; */
    View _View;

    // Устанавливает активный слой.
    /* [XmlElement("ActiveLayer")] public ActiveLayer _ActiveLayer; */
    ActiveLayer _ActiveLayer;

    // Настройка отображения: единицы измерения.
    /* [XmlElement("Units")] public Units_DisplayControl _Units; */
    Units_DisplayControl _Units;

    // Настройка отображения: общие цветовые настройки.
    /* [XmlElement("Colors")] public Colors_DisplayControl _Colors; */
    Colors_DisplayControl _Colors;

    //  Настройка отображения: настройки видимости объектов.
    /* [XmlElement("Show")] public Show_DisplayControl _Show; */
    Show_DisplayControl _Show;

    //  Настройки сетки.
    /* [XmlElement("Grid")] public Grid _Grid; */
    Grid _Grid;

    // Настройка отображения: настройки видимости слоёв.
    /* [XmlArray("LayersVisualOptions")][XmlArrayItem("LayerOptions")] public List<LayerOptions> _LayersVisualOptions; */
    std::vector<LayerOptions> _LayersVisualOptions;
    bool ShouldSerialize_LayersVisualOptions();

    // Отображение цепей особым цветом.
    /* [XmlElement("ColorNets")] public ColorNets _ColorNets; */
    ColorNets _ColorNets;

    // Фильтр отображения связей.
    /* [XmlElement("FilterNetlines")] public FilterNetlines _FilterNetlines; */
    FilterNetlines _FilterNetlines;

    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DisplayControl. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/

    /**************************************************************************/
};

} // namespace TopoR_PCB_Classes
