#pragma once

#include "Commons.h"
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Соединения на плате».

// <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
struct Connectivity {

    // Переходное отверстие на плате.

    struct Via {

        // Признак фиксации.

        /* [XmlAttribute("fixed")] public Bool _fixed; */
        Bool _fixed{};

        /* [XmlIgnore] public bool _fixedSpecified */
        bool getFixedSpecified() const;

        // Ссылка на тип переходного отверстия.

        /* [XmlElement("ViastackRef")] public ViastackRef _ViastackRef; */
        ViastackRef _ViastackRef;

        // Ссылка на цепь.

        /* [XmlElement("NetRef")] public NetRef _NetRef; */
        NetRef _NetRef;

        // Точка привязки объекта.

        /* [XmlElement("Org")] public Org _Org; */
        Org _Org;
    };

    // Описание змейки.

    // <remarks>! Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)</remarks>

    struct Serpent {

        // Идентификатор неименованных объектов.

        /* [XmlAttribute("id")] public string _id; */
        QString _id;

        // Параметр змейки: требуемая длина.

        /* [XmlAttribute("Count", DataType ="float")] public float _Count; */
        float _Count = 0.0F;

        // Параметр змейки: зазор между соседними изломами.

        /* [XmlAttribute("gap", DataType = "float")] public float _gap; */
        Attribute<float> gap;
        float _gap = 0.0F;

        // Параметр змейки: высота h1 (см. описание змейки Serpent).

        /* [XmlAttribute("h1", DataType = "float")] public float _h1; */
        Attribute<float> h1;
        float _h1 = 0.0F;

        // Параметр змейки: высота h2 (см. описание змейки Serpent).

        /* [XmlAttribute("h2", DataType = "float")] public float _h2; */
        Attribute<float> h2;
        float _h2 = 0.0F;

        // Параметр змейки: высота h3 (см. описание змейки Serpent).

        /* [XmlAttribute("h3", DataType = "float")] public float _h3; */
        Attribute<float> h3;
        float _h3 = 0.0F;

        // Параметр змейки: высота h4 (см. описание змейки Serpent).

        /* [XmlAttribute("h4", DataType = "float")] public float _h4; */
        Attribute<float> h4;
        float _h4 = 0.0F;
    };

    // Описание застёгнутой пары проводников.

    // <remarks>! Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.</remarks>

    struct ZippedWire {

        // Идентификатор неименованных объектов.

        /* [XmlAttribute("id")] public string _id; */
        QString _id;

        // Признак фиксации.

        /* [XmlAttribute("fixed")] public Bool _fixed; */
        Bool _fixed{};

        /* [XmlIgnore] public bool _fixedSpecified */
        bool getFixedSpecified() const;

        // Ссылка на слой.

        /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
        LayerRef _LayerRef;

        // Ссылка на дифференциальный сигнал.

        /* [XmlElement("DiffSignalRef")] public DiffSignalRef _DiffSignalRef; */
        DiffSignalRef _DiffSignalRef;

        // Начальная точка линии, дуги.

        /* [XmlElement("Start")] public Start _Start; */
        Start _Start;

        // Описание(я) сегмента проводника.

        // <remarks>! В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.</remarks>

        /* [XmlElement("TrackLine", typeof(TrackLine)),
        XmlElement("TrackArc", typeof(TrackArc)),
        XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks; */
        std::vector<std::variant<TrackLine, TrackArc, TrackArcCW>> _Tracks;
        bool ShouldSerialize_Tracks();
    };

    // Описание проводника.

    struct Wire {

        // Описание части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).

        // <remarks>! Атрибут zipwireRef (ссылка на застёгнутую пару проводников) используется, если описываемая часть проводника входит в застёгнутую пару проводников ZippedWire (см. пример описания проводника дифференциальной пары).</remarks>

        struct Subwire {

            // Описание «капельки» четырёхугольником. Первая вершина соответствует точке привязки контакта (переходного отверстия). Остальные вершины описывают контур четырёхугольника против часовой стрелки.

            // <remarks> ! TopoR при импорте игнорирует информацию о капельках.</remarks>

            struct Teardrop {

                // координаты точки, вершины.

                /* [XmlElement("Dot")] public List<Dot> _Dots; */
                std::vector<Dot> _Dots;
                bool ShouldSerialize_Dots();
            };

            // Признак фиксации.

            /* [XmlAttribute("fixed")] public Bool _fixed; */
            Bool _fixed{};

            /* [XmlIgnore] public bool _fixedSpecified */
            bool getFixedSpecified() const;

            // Ширина проводника.

            /* [XmlAttribute("width", DataType = "float")] public float _width; */
            Attribute<float> width;
            float _width = 0.0F;

            // Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.

            /* [XmlAttribute("zipwireRef")] public string _zipwireRef; */
            QString _zipwireRef;

            // Описание «капелек» для Subwire.

            // <remarks>От KilkennyCat: сделал как массив, в спецификации не так, но так удобней</remarks>

            /* [XmlArray("Teardrops")][XmlArrayItem("Teardrop")] public List<Teardrop> _Teardrops; */
            std::vector<Teardrop> _Teardrops;
            bool ShouldSerialize_Teardrops();

            // Начальная точка линии, дуги.

            /* [XmlElement("Start")] public Start _Start; */
            Start _Start;

            // Описание(я) сегмента проводника.

            // <remarks>! В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.</remarks>

            /* [XmlElement("TrackLine", typeof(TrackLine)),
XmlElement("TrackArc", typeof(TrackArc)),
XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks; */
            std::vector<std::variant<TrackLine, TrackArc, TrackArcCW>> _Tracks;
            bool ShouldSerialize_Tracks();
        };

        // Ссылка на слой.

        /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
        LayerRef _LayerRef;

        // Ссылка на цепь.

        /* [XmlElement("NetRef")] public NetRef _NetRef; */
        NetRef _NetRef;

        // Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).

        /* [XmlElement("Subwire")] public List<Subwire> _Subwires; */
        std::vector<Subwire> _Subwires;
        bool ShouldSerialize_Subwires();
    };

    // Описание заливаемой области металлизации (полигона).

    // <remarks>! Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.</remarks>

    struct Copper_Connectivity {

        // Описание термобарьера для подключения контактных площадок к области металлизации.

        struct ThermalPad {

            // Описание термобарьера.

            /* [XmlElement("Thermal")] public Thermal _Thermal; */
            Thermal _Thermal;
        };

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.

        struct ThermalVia {

            // Описание термобарьера.

            /* [XmlElement("Thermal")] public Thermal _Thermal; */
            Thermal _Thermal;
        };

        // Описание контура заливаемой области металлизации.

        struct Shape_Copper {

            // Описание залитой фигуры.

            /* [XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object _FilledFigure; */
            std::variant<FilledCircle, FilledRect, Polygon, FilledContour> _FilledFigure;
        };

        // Описание островка области металлизации.

        struct Island {

            // Описание спицы термобарьера, присутствующего на плате

            struct ThermalSpoke {

                // Толщина линии.

                /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
                Attribute<float> lineWidth;
                float _lineWidth = 0.0F;

                // Описания координат точек, вершин.

                // <remarks>! В случае отсутствия - весь ThermalSpoke будет проигнорирован.</remarks>

                /* [XmlElement("Dot")] public List<Dot> _Dots; */
                std::vector<Dot> _Dots;
                bool ShouldSerialize_Dots();
            };

            // Описание многоугольника.

            /* [XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object _Polygon; */
            std::variant<Polygon, FilledContour> _Polygon;

            // Вырезы в островке области металлизации.

            // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

            /* [XmlArray("Voids")][XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids; */
            std::vector<std::variant<Polygon, FilledContour>> _Voids;

            // Описание спиц термобарьеров, присутствующих на плате

            /* [XmlElement("ThermalSpoke")] public List<ThermalSpoke> _ThermalSpokes; */
            std::vector<ThermalSpoke> _ThermalSpokes;
            bool ShouldSerialize_ThermalSpokes();
        };

        // Параметр области металлизации (полигона): приоритет заливки.

        /* [XmlAttribute("priority", DataType ="int")] public int _priority; */
        int _priority = 0;

        // Параметр области металлизации (полигона): использовать указанный зазор.

        /* [XmlAttribute("useBackoff")] public Bool _useBackoff; */
        Bool _useBackoff{};

        /* [XmlIgnore] public bool _useBackoffSpecified */
        bool getUseBackoffSpecified() const;

        // Параметр области металлизации (полигона): зазор до области металлизации.

        /* [XmlAttribute("backoff", DataType ="float")] public float _backoff; */
        float _backoff = 0.0F;

        // Параметр области металлизации (полигона) стека: подключение контактных площадок.

        /* [XmlAttribute("connectPad")] public connectPad _connectPad; */
        connectPad _connectPad{};

        // Параметр области металлизации (полигона): подключение площадок переходных отверстий.

        /* [XmlAttribute("connectVia")] public connectVia _connectVia; */
        connectVia _connectVia{};

        // Толщина линии.

        /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
        Attribute<float> lineWidth;
        float _lineWidth = 0.0F;

        // Параметр области металлизации (полигона): зазор между линиями штриховки.

        /* [XmlAttribute("lineClr", DataType = "float")] public float _lineClr; */
        Attribute<float> lineClr;
        float _lineClr = 0.0F;

        // Параметр области металлизации (полигона): минимальная площадь островка.

        /* [XmlAttribute("minSquare", DataType = "float")] public float _minSquare; */
        Attribute<float> minSquare;
        float _minSquare = 0.0F;

        // Параметр области металлизации (полигона): точность аппроксимации контура.

        /* [XmlAttribute("precision")] public precision _precision; */
        precision _precision{};

        // Параметр области металлизации (полигона): удалять неподключенные островки.

        /* [XmlAttribute("deleteUnconnected")] public Bool _deleteUnconnected; */
        Bool _deleteUnconnected{};

        /* [XmlIgnore] public bool _deleteUnconnectedSpecified */
        bool getDeleteUnconnectedSpecified() const;

        // Параметр области металлизации (полигона): состояние.

        /* [XmlAttribute("state")] public state _state; */
        state _state{};

        // Параметр области металлизации (полигона): тип заливки.

        /* [XmlAttribute("fillType")] public fillType _fillType; */
        fillType _fillType{};

        // Ссылка на слой.

        /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
        LayerRef _LayerRef;

        // Ссылка на цепь.

        /* [XmlElement("NetRef")] public NetRef _NetRef; */
        NetRef _NetRef;

        // Описание термобарьера для подключения контактных площадок к области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        /* [XmlElement("ThermalPad")] public ThermalPad _ThermalPad; */
        ThermalPad _ThermalPad;

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        /* [XmlElement("ThermalVia")] public ThermalVia _ThermalVia; */
        ThermalVia _ThermalVia;

        // Описание контура заливаемой области металлизации..

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        /* [XmlElement("Shape")] public Shape_Copper _Shape; */
        Shape_Copper _Shape;

        // Вырезы в областях металлизации (полигонах) заданные пользователем.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        /* [XmlArray("Voids")][XmlArrayItem("FilledCircle", typeof(FilledCircle)), XmlArrayItem("FilledRect", typeof(FilledRect)), XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids; */
        std::vector<std::variant<
            ArcCCW,
            ArcCW,
            ArcByAngle,
            ArcByMiddle,
            Circle,
            Line,
            Polyline,
            Rect,
            Contour>>
            _Voids;

        // Островки области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        /* [XmlArray("Islands")][XmlArrayItem("Island")] public List<Island> _Islands; */
        std::vector<Island> _Islands;

        // Заливка областей металлизации (полигонов) линиями.

        // <remarks>! TopoR при импорте игнорирует эту информацию и строит заливку заново.</remarks>

        /* [XmlArray("Fill")][XmlArrayItem("Line")] public List<Line> _Fill_lines; */
        std::vector<Line> _Fill_lines;
        bool ShouldSerialize_Fill_lines();
    };

    // Описание незаливаемой области металлизации.

    struct NonfilledCopper {

        // Описание контура незаливаемой области металлизации.

        struct Shape_NonfilledCopper {

            // Описание фигуры.

            /* [XmlElement("ArcCCW", typeof(ArcCCW)),
                XmlElement("ArcCW", typeof(ArcCW)),
                XmlElement("ArcByAngle", typeof(ArcByAngle)),
                XmlElement("ArcByMiddle", typeof(ArcByMiddle)),
                XmlElement("Circle", typeof(Circle)),
                XmlElement("Line", typeof(Line)),
                XmlElement("Polyline", typeof(Polyline)),
                XmlElement("Rect", typeof(Rect)),
                XmlElement("Contour", typeof(Contour))] public Object _FigureContPoliline; */
            std::variant<ArcCCW,
                ArcCW,
                ArcByAngle,
                ArcByMiddle,
                Circle,
                Line,
                Polyline,
                Rect,
                Contour>
                _FigureContPoliline;
        };

        // Толщина линии.

        /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
        Attribute<float> lineWidth;
        float _lineWidth = 0.0F;

        // Ссылка на слой.

        /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
        LayerRef _LayerRef;

        // Ссылка на цепь.

        /* [XmlElement("NetRef")] public NetRef _NetRef; */
        NetRef _NetRef;

        // Описание контура незаливаемой области металлизации.

        /* [XmlElement("Shape")] public Shape_NonfilledCopper _Shape; */
        Shape_NonfilledCopper _Shape;
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string _version; */
    QString _version;

    // Переходные отверстия на плате.

    /* [XmlArray("Vias")][XmlArrayItem("Via")] public List<Via> _Vias; */
    std::vector<Via> _Vias;
    bool ShouldSerialize_Vias();

    // Змейки

    /* [XmlArray("Serpents")][XmlArrayItem("Serpent")] public List<Serpent> _Serpents; */
    std::vector<Serpent> _Serpents;
    bool ShouldSerialize_Serpents();

    // Застёгнутые пары проводников.

    /* [XmlArray("ZippedWires")][XmlArrayItem("ZippedWire")] public List<ZippedWire> _ZippedWires; */
    std::vector<ZippedWire> _ZippedWires;
    bool ShouldSerialize_ZippedWires();

    // Проводники.

    /* [XmlArray("Wires")][XmlArrayItem("Wire")] public List<Wire> _Wires; */
    std::vector<Wire> _Wires;
    bool ShouldSerialize_Wires();

    // Oбласти металлизации (полигонов).

    /* [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Connectivity> _Coppers; */
    std::vector<Copper_Connectivity> _Coppers;
    bool ShouldSerialize_Coppers();

    // Незаливаемые области металлизации.

    /* [XmlArray("NonfilledCoppers")][XmlArrayItem("NonfilledCopper")] public List<NonfilledCopper> _NonfilledCoppers; */
    std::vector<NonfilledCopper> _NonfilledCoppers;
    bool ShouldSerialize_NonfilledCoppers();

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Connectivity. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
