#pragma once
#include "Commons.h"
#include <QColor>
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
namespace TopoR {
// Раздел «Соединения на плате».
/// \note В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
struct Connectivity {
    // Переходное отверстие на плате.
    struct Via {
        // Признак фиксации.
        // [XmlAttribute("fixed")] public Bool fixed_;
        Optional<XmlAttr<Bool>> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на тип переходного отверстия.
        // [XmlElement("ViastackRef")] public ViastackRef viastackRef;
        ViastackRef viastackRef;
        // Ссылка на цепь.
        // [XmlElement("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Точка привязки объекта.
        // [XmlElement("Org")] public Org org;
        Org org;
    };
    // Описание змейки.
    /// \note !Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)
    struct Serpent {
        // Идентификатор неименованных объектов.
        // [XmlAttribute("id")] public string id_;
        XmlAttr<QString> id;
        // Параметр змейки: зазор между соседними изломами.
        // [XmlAttribute("gap", DataType = "double")] public double gap_;
        XmlAttr<double> gap;
        // Параметр змейки: высота h1 (см. описание змейки Serpent).
        // [XmlAttribute("h1", DataType = "double")] public double h1_;
        XmlAttr<double> h1;
        // Параметр змейки: высота h2 (см. описание змейки Serpent).
        // [XmlAttribute("h2", DataType = "double")] public double h2_;
        XmlAttr<double> h2;
        // Параметр змейки: высота h3 (см. описание змейки Serpent).
        // [XmlAttribute("h3", DataType = "double")] public double h3_;
        XmlAttr<double> h3;
        // Параметр змейки: высота h4 (см. описание змейки Serpent).
        // [XmlAttribute("h4", DataType = "double")] public double h4_;
        XmlAttr<double> h4;
        // Параметр змейки: требуемая длина.
        // [XmlAttribute("Count", DataType ="double")] public double Count_;
        XmlAttr<double> length;
    };
    // Описание застёгнутой пары проводников.
    /// \note !Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.
    struct ZippedWire {
        // Идентификатор неименованных объектов.
        // [XmlAttribute("id")] public string id_;
        XmlAttr<QString> id;
        // Признак фиксации.
        // [XmlAttribute("fixed")] public Bool fixed_;
        Optional<XmlAttr<Bool>> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на слой.
        // [XmlElement("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на дифференциальный сигнал.
        // [XmlElement("DiffSignalRef")] public DiffSignalRef diffSignalRef;
        DiffSignalRef diffSignalRef;
        // Начальная точка линии, дуги.
        // [XmlElement("Start")] public Start start;
        Start start;
        // Описание(я) сегмента проводника.
        /// \note !В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.
        // [XmlElement(TrackLine),
        //  XmlElement(TrackArc),
        //  XmlElement(TrackArcCW)] public List<Object> Tracks_;
        XmlArray<XmlVariant<TrackLine, TrackArc, TrackArcCW>> Tracks;
    };
    // Описание проводника.
    struct Wire {
        // Описание части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
        /// \note !Атрибут zipwireRef (ссылка на застёгнутую пару проводников) используется, если описываемая часть проводника входит в застёгнутую пару проводников ZippedWire (см. пример описания проводника дифференциальной пары).
        struct Subwire {
            // Описание «капельки» четырёхугольником. Первая вершина соответствует точке привязки контакта (переходного отверстия). Остальные вершины описывают контур четырёхугольника против часовой стрелки.
            /// \note !TopoR при импорте игнорирует информацию о капельках.
            struct Teardrop {
                // координаты точки, вершины.
                // [XmlElement("Dot")] public List<Dot> Dots_;
                XmlArray<Dot> Dots;
            };
            // Признак фиксации.
            // [XmlAttribute("fixed")] public Bool fixed_;
            Optional<XmlAttr<Bool>> fixed;
            /* public bool fixedSpecified_ */
            // Ширина проводника.
            // [XmlAttribute("width", DataType = "double")] public double width_;
            XmlAttr<double> width;
            // Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.
            // [XmlAttribute("zipwireRef")] public string zipwireRef_;
            XmlAttr<QString> zipwireRef;
            // Описание «капелек» для Subwire.
            /// \note От KilkennyCat: сделал как массив, в спецификации не так, но так удобней
            // [XmlArray("Teardrops")][XmlArrayItem("Teardrop")] public List<Teardrop> Teardrops_;
            XmlArrayElem<Teardrop> Teardrops;
            // Начальная точка линии, дуги.
            // [XmlElement("Start")] public Start start;
            Start start;
            // Описание(я) сегмента проводника.
            /// \note !В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.
            // [XmlElement(TrackLine),
            //  XmlElement(TrackArc),
            //  XmlElement(TrackArcCW)] public List<Object> Tracks_;
            XmlArray<XmlVariant<TrackLine, TrackArc, TrackArcCW>> Tracks;

            QGraphicsItem* graphicsItem(const QColor& color = Qt::red) const;
        };
        // Ссылка на слой.
        // [XmlElement("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [XmlElement("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
        // [XmlElement("Subwire")] public List<Subwire> Subwires_;
        XmlArray<Subwire> Subwires;
    };
    // Описание заливаемой области металлизации (полигона).
    /// \note !Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.
    struct Copper {
        // Описание термобарьера для подключения контактных площадок к области металлизации.
        struct ThermalPad {
            // Описание термобарьера.
            // [XmlElement("Thermal")] public Thermal thermal;
            Optional<Thermal> thermal;
        };
        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        struct ThermalVia {
            // Описание термобарьера.
            // [XmlElement("Thermal")] public Thermal thermal;
            Optional<Thermal> thermal;
        };
        // Описание контура заливаемой области металлизации.
        struct Shape {
            // Описание залитой фигуры.
            // [XmlElement(FilledCircle),
            //  XmlElement(FilledRect),
            //  XmlElement(Polygon),
            //  XmlElement(FilledContour)] public Object FilledFigure_;
            XmlVariant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
        };
        // Описание островка области металлизации.
        struct Island {
            // Описание спицы термобарьера, присутствующего на плате
            struct ThermalSpoke {
                // Толщина линии.
                // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
                XmlAttr<double> lineWidth;
                // Описания координат точек, вершин.
                /// \note !В случае отсутствия - весь ThermalSpoke будет проигнорирован.
                // [XmlElement("Dot")] public List<Dot> Dots_;
                XmlArrayElem<Dot> Dots;
            };
            // Описание многоугольника.
            // [XmlElement(Polygon),
            //  XmlElement(FilledContour)] public Object Polygon_;
            XmlVariant<Polygon, FilledContour> Polygon_;
            // Вырезы в островке области металлизации.
            /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
            // [XmlArray("Voids")][XmlArrayItem(Polygon), XmlArrayItem(FilledContour)] public List<Object> Voids_;
            XmlArrayElem<XmlVariant<Polygon, FilledContour>> Voids;
            // Описание спиц термобарьеров, присутствующих на плате
            // [XmlElement("ThermalSpoke")] public List<ThermalSpoke> ThermalSpokes_;
            XmlArrayElem<ThermalSpoke> ThermalSpokes;
        };
        // Параметр области металлизации (полигона): приоритет заливки.
        // [XmlAttribute("priority", DataType ="int")] public int priority_;
        XmlAttr<int> priority;
        // Параметр области металлизации (полигона): использовать указанный зазор.
        // [XmlAttribute("useBackoff")] public Bool useBackoff_;
        XmlAttr<Bool> useBackoff;
        /* public bool useBackoffSpecified_ */
        // Параметр области металлизации (полигона): зазор до области металлизации.
        // [XmlAttribute("backoff", DataType ="double")] public double backoff_;
        XmlAttr<double> backoff;
        // Параметр области металлизации (полигона) стека: подключение контактных площадок.
        // [XmlAttribute("connectPad")] public connectPad connectPad_;
        XmlAttr<connectPad> connectPad_;
        // Параметр области металлизации (полигона): подключение площадок переходных отверстий.
        // [XmlAttribute("connectVia")] public connectVia connectVia_;
        XmlAttr<connectVia> connectVia_;
        // Толщина линии.
        // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
        XmlAttr<double> lineWidth;
        // Параметр области металлизации (полигона): зазор между линиями штриховки.
        // [XmlAttribute("lineClr", DataType = "double")] public double lineClr_;
        XmlAttr<double> lineClr;
        // Параметр области металлизации (полигона): минимальная площадь островка.
        // [XmlAttribute("minSquare", DataType = "double")] public double minSquare_;
        XmlAttr<double> minSquare;
        // Параметр области металлизации (полигона): точность аппроксимации контура.
        // [XmlAttribute("precision")] public precision precision_;
        XmlAttr<precision> precision_;
        // Параметр области металлизации (полигона): удалять неподключенные островки.
        // [XmlAttribute("deleteUnconnected")] public Bool deleteUnconnected_;
        XmlAttr<Bool> deleteUnconnected;
        /* public bool deleteUnconnectedSpecified_ */
        // Параметр области металлизации (полигона): состояние.
        // [XmlAttribute("state")] public state state_;
        XmlAttr<state> state_;
        // Параметр области металлизации (полигона): тип заливки.
        // [XmlAttribute("fillType")] public fillType fillType_;
        XmlAttr<fillType> fillType_;
        // Ссылка на слой.
        // [XmlElement("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [XmlElement("NetRef")] public NetRef netRef;
        Optional<NetRef> netRef;
        // Описание термобарьера для подключения контактных площадок к области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [XmlElement("ThermalPad")] public ThermalPad thermalPad;
        ThermalPad thermalPad;
        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [XmlElement("ThermalVia")] public ThermalVia thermalVia;
        ThermalVia thermalVia;
        // Описание контура заливаемой области металлизации..
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [XmlElement("Shape")] public Shape Shape_;
        Shape Shape_;
        // Вырезы в областях металлизации (полигонах) заданные пользователем.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [XmlArray("Voids")][XmlArrayItem(FilledCircle), XmlArrayItem(FilledRect), XmlArrayItem(Polygon), XmlArrayItem(FilledContour)] public List<Object> Voids_;
        XmlArrayElem<XmlVariant<
            ArcCCW,
            ArcCW,
            ArcByAngle,
            ArcByMiddle,
            Circle,
            Line,
            Polyline,
            Rect,
            Contour>>
            Voids;
        // Островки области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [XmlArray("Islands")][XmlArrayItem("Island")] public List<Island> Islands_;
        XmlArrayElem<Island> Islands;
        // Заливка областей металлизации (полигонов) линиями.
        /// \note !TopoR при импорте игнорирует эту информацию и строит заливку заново.
        // [XmlArray("Fill")][XmlArrayItem("Line")] public List<Line> Fill_lines_;
        XmlArrayElem<Line> Fill;
    };
    // Описание незаливаемой области металлизации.
    struct NonfilledCopper {
        // Описание контура незаливаемой области металлизации.
        struct Shape {
            // Описание фигуры.
            // [XmlElement(ArcCCW),
            //  XmlElement(ArcCW),
            //  XmlElement(ArcByAngle),
            //  XmlElement(ArcByMiddle),
            //  XmlElement(Circle),
            //  XmlElement(Line),
            //  XmlElement(Polyline),
            //  XmlElement(Rect),
            //  XmlElement(Contour)] public Object FigureContPoliline_;
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
        // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
        XmlAttr<double> lineWidth;
        // Ссылка на слой.
        // [XmlElement("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [XmlElement("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Описание контура незаливаемой области металлизации.
        // [XmlElement("Shape")] public Shape Shape_;
        Shape Shape_;
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Переходные отверстия на плате.
    // [XmlArray("Vias")][XmlArrayItem("Via")] public List<Via> Vias_;
    XmlArrayElem<Via> Vias;
    // Змейки
    // [XmlArray("Serpents")][XmlArrayItem("Serpent")] public List<Serpent> Serpents_;
    XmlArrayElem<Serpent> Serpents;
    // Застёгнутые пары проводников.
    // [XmlArray("ZippedWires")][XmlArrayItem("ZippedWire")] public List<ZippedWire> ZippedWires_;
    XmlArrayElem<ZippedWire> ZippedWires;
    // Проводники.
    // [XmlArray("Wires")][XmlArrayItem("Wire")] public List<Wire> Wires_;
    XmlArrayElem<Wire> Wires;
    // Oбласти металлизации (полигонов).
    // [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Connectivity> Coppers_;
    XmlArrayElem<Copper> Coppers;
    // Незаливаемые области металлизации.
    // [XmlArray("NonfilledCoppers")][XmlArrayItem("NonfilledCopper")] public List<NonfilledCopper> NonfilledCoppers_;
    XmlArrayElem<NonfilledCopper> NonfilledCoppers;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Connectivity. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
};
} // namespace TopoR
