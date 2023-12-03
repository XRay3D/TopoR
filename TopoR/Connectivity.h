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
        /* [XmlAttribute("fixed")] public Bool fixed_; */
        XmlAttr<Bool> fixed;

        /* public bool fixedSpecified_ */
        // Ссылка на тип переходного отверстия.
        /* [XmlElement("ViastackRef")] public ViastackRef ViastackRef_; */
        ViastackRef ViastackRef_;

        // Ссылка на цепь.
        /* [XmlElement("NetRef")] public NetRef NetRef_; */
        NetRef NetRef_;

        // Точка привязки объекта.
        /* [XmlElement("Org")] public Org org; */
        Org org;
    };

    // Описание змейки.
    // <remarks>! Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)</remarks>
    struct Serpent {
        // Идентификатор неименованных объектов.
        /* [XmlAttribute("id")] public string id_; */
        XmlAttr<QString> id;

        // Параметр змейки: требуемая длина.
        /* [XmlAttribute("Count", DataType ="float")] public float Count_; */
        XmlAttr<float> Count;

        // Параметр змейки: зазор между соседними изломами.
        /* [XmlAttribute("gap", DataType = "float")] public float gap_; */
        XmlAttr<float> gap;

        // Параметр змейки: высота h1 (см. описание змейки Serpent).
        /* [XmlAttribute("h1", DataType = "float")] public float h1_; */
        XmlAttr<float> h1;

        // Параметр змейки: высота h2 (см. описание змейки Serpent).
        /* [XmlAttribute("h2", DataType = "float")] public float h2_; */
        XmlAttr<float> h2;

        // Параметр змейки: высота h3 (см. описание змейки Serpent).
        /* [XmlAttribute("h3", DataType = "float")] public float h3_; */
        XmlAttr<float> h3;

        // Параметр змейки: высота h4 (см. описание змейки Serpent).
        /* [XmlAttribute("h4", DataType = "float")] public float h4_; */
        XmlAttr<float> h4;
    };

    // Описание застёгнутой пары проводников.
    // <remarks>! Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.</remarks>
    struct ZippedWire {

        // Идентификатор неименованных объектов.
        /* [XmlAttribute("id")] public string id_; */
        XmlAttr<QString> id;

        // Признак фиксации.
        /* [XmlAttribute("fixed")] public Bool fixed_; */
        XmlAttr<Bool> fixed;

        /* public bool fixedSpecified_ */

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
        LayerRef LayerRef_;

        // Ссылка на дифференциальный сигнал.
        /* [XmlElement("DiffSignalRef")] public DiffSignalRef DiffSignalRef_; */
        DiffSignalRef DiffSignalRef_;

        // Начальная точка линии, дуги.
        /* [XmlElement("Start")] public Start start; */
        Start start;

        // Описание(я) сегмента проводника.
        // <remarks>! В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.</remarks>
        /* [XmlElement("TrackLine", typeof(TrackLine)),
        XmlElement("TrackArc", typeof(TrackArc)),
        XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> Tracks_; */
        std::vector<XmlVariant<TrackLine, TrackArc, TrackArcCW>> Tracks;
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
                /* [XmlElement("Dot")] public List<Dot> Dots_; */
                std::vector<Dot> Dots;
            };

            // Признак фиксации.
            /* [XmlAttribute("fixed")] public Bool fixed_; */
            XmlAttr<Bool> fixed;

            /* public bool fixedSpecified_ */

            // Ширина проводника.
            /* [XmlAttribute("width", DataType = "float")] public float width_; */
            XmlAttr<float> width;

            // Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.
            /* [XmlAttribute("zipwireRef")] public string zipwireRef_; */
            XmlAttr<QString> zipwireRef;

            // Описание «капелек» для Subwire.
            // <remarks>От KilkennyCat: сделал как массив, в спецификации не так, но так удобней</remarks>
            /* [XmlArray("Teardrops")][XmlArrayItem("Teardrop")] public List<Teardrop> Teardrops_; */
            std::vector<Teardrop> Teardrops;

            // Начальная точка линии, дуги.
            /* [XmlElement("Start")] public Start start; */
            Start start;

            // Описание(я) сегмента проводника.
            // <remarks>! В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.</remarks>
            /* [XmlElement("TrackLine", typeof(TrackLine)),
                XmlElement("TrackArc", typeof(TrackArc)),
                XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> Tracks_; */
            std::vector<XmlVariant<TrackLine, TrackArc, TrackArcCW>> Tracks;
        };

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
        LayerRef LayerRef_;

        // Ссылка на цепь.
        /* [XmlElement("NetRef")] public NetRef NetRef_; */
        NetRef NetRef_;

        // Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
        /* [XmlElement("Subwire")] public List<Subwire> Subwires_; */
        XmlAarray<Subwire> Subwires;
    };

    // Описание заливаемой области металлизации (полигона).
    // <remarks>! Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.</remarks>
    struct Copper_Connectivity {

        // Описание термобарьера для подключения контактных площадок к области металлизации.
        struct ThermalPad {
            // Описание термобарьера.
            /* [XmlElement("Thermal")] public Thermal thermal; */
            Thermal thermal;
        };

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        struct ThermalVia {
            // Описание термобарьера.
            /* [XmlElement("Thermal")] public Thermal thermal; */
            Thermal thermal;
        };

        // Описание контура заливаемой области металлизации.
        struct Shape_Copper {
            // Описание залитой фигуры.
            /* [XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object FilledFigure_; */
            XmlVariant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
        };

        // Описание островка области металлизации.
        struct Island {

            // Описание спицы термобарьера, присутствующего на плате
            struct ThermalSpoke {
                // Толщина линии.
                /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
                XmlAttr<float> lineWidth;

                // Описания координат точек, вершин.
                // <remarks>! В случае отсутствия - весь ThermalSpoke будет проигнорирован.</remarks>
                /* [XmlElement("Dot")] public List<Dot> Dots_; */
                std::vector<Dot> Dots;
            };

            // Описание многоугольника.
            /* [XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object Polygon_; */
            XmlVariant<Polygon, FilledContour> Polygon_;

            // Вырезы в островке области металлизации.
            // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
            /* [XmlArray("Voids")][XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> Voids_; */
            std::vector<XmlVariant<Polygon, FilledContour>> Voids;

            // Описание спиц термобарьеров, присутствующих на плате
            /* [XmlElement("ThermalSpoke")] public List<ThermalSpoke> ThermalSpokes_; */
            std::vector<ThermalSpoke> ThermalSpokes;
        };

        // Параметр области металлизации (полигона): приоритет заливки.
        /* [XmlAttribute("priority", DataType ="int")] public int priority_; */
        XmlAttr<int> priority;

        // Параметр области металлизации (полигона): использовать указанный зазор.
        /* [XmlAttribute("useBackoff")] public Bool useBackoff_; */
        XmlAttr<Bool> useBackoff;

        /* public bool useBackoffSpecified_ */

        // Параметр области металлизации (полигона): зазор до области металлизации.
        /* [XmlAttribute("backoff", DataType ="float")] public float backoff_; */
        XmlAttr<float> backoff;

        // Параметр области металлизации (полигона) стека: подключение контактных площадок.
        /* [XmlAttribute("connectPad")] public connectPad connectPad_; */
        XmlAttr<connectPad> connectPad_;

        // Параметр области металлизации (полигона): подключение площадок переходных отверстий.
        /* [XmlAttribute("connectVia")] public connectVia connectVia_; */
        XmlAttr<connectVia> connectVia_;

        // Толщина линии.
        /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
        XmlAttr<float> lineWidth;

        // Параметр области металлизации (полигона): зазор между линиями штриховки.
        /* [XmlAttribute("lineClr", DataType = "float")] public float lineClr_; */
        XmlAttr<float> lineClr;

        // Параметр области металлизации (полигона): минимальная площадь островка.
        /* [XmlAttribute("minSquare", DataType = "float")] public float minSquare_; */
        XmlAttr<float> minSquare;

        // Параметр области металлизации (полигона): точность аппроксимации контура.
        /* [XmlAttribute("precision")] public precision precision_; */
        XmlAttr<precision> precision_;

        // Параметр области металлизации (полигона): удалять неподключенные островки.
        /* [XmlAttribute("deleteUnconnected")] public Bool deleteUnconnected_; */
        XmlAttr<Bool> deleteUnconnected;

        /* public bool deleteUnconnectedSpecified_ */

        // Параметр области металлизации (полигона): состояние.
        /* [XmlAttribute("state")] public state state_; */
        XmlAttr<state> state_;

        // Параметр области металлизации (полигона): тип заливки.
        /* [XmlAttribute("fillType")] public fillType fillType_; */
        XmlAttr<fillType> fillType_;

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
        LayerRef LayerRef_;

        // Ссылка на цепь.
        /* [XmlElement("NetRef")] public NetRef NetRef_; */
        NetRef NetRef_;

        // Описание термобарьера для подключения контактных площадок к области металлизации.
        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
        /* [XmlElement("ThermalPad")] public ThermalPad ThermalPad_; */
        ThermalPad ThermalPad_;

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
        /* [XmlElement("ThermalVia")] public ThermalVia ThermalVia_; */
        ThermalVia ThermalVia_;

        // Описание контура заливаемой области металлизации..
        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
        /* [XmlElement("Shape")] public Shape_Copper Shape_; */
        Shape_Copper Shape_;

        // Вырезы в областях металлизации (полигонах) заданные пользователем.
        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
        /* [XmlArray("Voids")][XmlArrayItem("FilledCircle", typeof(FilledCircle)), XmlArrayItem("FilledRect", typeof(FilledRect)), XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> Voids_; */
        std::vector<XmlVariant<
            ArcCCW,
            ArcCW,
            ArcByAngle,
            ArcByMiddle,
            Circle,
            Line,
            Polyline,
            Rect,
            Contour>>
            Voids_;

        // Островки области металлизации.
        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
        /* [XmlArray("Islands")][XmlArrayItem("Island")] public List<Island> Islands_; */
        std::vector<Island> Islands;

        // Заливка областей металлизации (полигонов) линиями.
        // <remarks>! TopoR при импорте игнорирует эту информацию и строит заливку заново.</remarks>
        /* [XmlArray("Fill")][XmlArrayItem("Line")] public List<Line> Fill_lines_; */
        std::vector<Line> Fill_lines;
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
                XmlElement("Contour", typeof(Contour))] public Object FigureContPoliline_; */
            XmlVariant<ArcCCW,
                ArcCW,
                ArcByAngle,
                ArcByMiddle,
                Circle,
                Line,
                Polyline,
                Rect,
                Contour>
                FigureContPoliline_;
        };

        // Толщина линии.
        /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
        XmlAttr<float> lineWidth;

        // Ссылка на слой.
        /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
        LayerRef LayerRef_;

        // Ссылка на цепь.
        /* [XmlElement("NetRef")] public NetRef NetRef_; */
        NetRef NetRef_;

        // Описание контура незаливаемой области металлизации.
        /* [XmlElement("Shape")] public Shape_NonfilledCopper Shape_; */
        Shape_NonfilledCopper Shape_;
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;

    // Переходные отверстия на плате.
    /* [XmlArray("Vias")][XmlArrayItem("Via")] public List<Via> Vias_; */
    std::vector<Via> Vias;

    // Змейки
    /* [XmlArray("Serpents")][XmlArrayItem("Serpent")] public List<Serpent> Serpents_; */
    std::vector<Serpent> Serpents;

    // Застёгнутые пары проводников.
    /* [XmlArray("ZippedWires")][XmlArrayItem("ZippedWire")] public List<ZippedWire> ZippedWires_; */
    std::vector<ZippedWire> ZippedWires;

    // Проводники.
    /* [XmlArray("Wires")][XmlArrayItem("Wire")] public List<Wire> Wires_; */
    std::vector<Wire> Wires;

    // Oбласти металлизации (полигонов).
    /* [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Connectivity> Coppers_; */
    std::vector<Copper_Connectivity> Coppers;

    // Незаливаемые области металлизации.
    /* [XmlArray("NonfilledCoppers")][XmlArrayItem("NonfilledCopper")] public List<NonfilledCopper> NonfilledCoppers_; */
    std::vector<NonfilledCopper> NonfilledCoppers;

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Connectivity. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
