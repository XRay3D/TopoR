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
        // [Xml::Attribute("fixed")] public Bool fixed_;
        Xml::Attr<Bool> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на тип переходного отверстия.
        // [Xml::Element("ViastackRef")] public ViastackRef viastackRef;
        ViastackRef viastackRef;
        // Ссылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Точка привязки объекта.
        // [Xml::Element("Org")] public Org org;
        Org org;
    };
    // Описание змейки.
    /// \note !Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)
    struct Serpent {
        // Идентификатор неименованных объектов.
        // [Xml::Attribute("id")] public string id_;
        Xml::Attr<QString> id;
        // Параметр змейки: зазор между соседними изломами.
        // [Xml::Attribute("gap", DataType = "double")] public double gap_;
        Xml::Attr<double> gap;
        // Параметр змейки: высота h1 (см. описание змейки Serpent).
        // [Xml::Attribute("h1", DataType = "double")] public double h1_;
        Xml::Attr<double> h1;
        // Параметр змейки: высота h2 (см. описание змейки Serpent).
        // [Xml::Attribute("h2", DataType = "double")] public double h2_;
        Xml::Attr<double> h2;
        // Параметр змейки: высота h3 (см. описание змейки Serpent).
        // [Xml::Attribute("h3", DataType = "double")] public double h3_;
        Xml::Attr<double> h3;
        // Параметр змейки: высота h4 (см. описание змейки Serpent).
        // [Xml::Attribute("h4", DataType = "double")] public double h4_;
        Xml::Attr<double> h4;
        // Параметр змейки: требуемая длина.
        // [Xml::Attribute("Count", DataType ="double")] public double Count_;
        Xml::Attr<double> length;
    };
    // Описание застёгнутой пары проводников.
    /// \note !Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.
    struct ZippedWire {
        // Идентификатор неименованных объектов.
        // [Xml::Attribute("id")] public string id_;
        Xml::Attr<QString> id;
        // Признак фиксации.
        // [Xml::Attribute("fixed")] public Bool fixed_;
        Xml::Attr<Bool> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на слой.
        // [Xml::Element("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на дифференциальный сигнал.
        // [Xml::Element("DiffSignalRef")] public DiffSignalRef diffSignalRef;
        DiffSignalRef diffSignalRef;
        // Начальная точка линии, дуги.
        // [Xml::Element("Start")] public Start start;
        Start start;
        // Описание(я) сегмента проводника.
        /// \note !В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.
        // [Xml::Element(TrackLine),
        //  Xml::Element(TrackArc),
        //  Xml::Element(TrackArcCW)] public List<Object> Tracks_;
        Xml::Array<Xml::Variant<TrackLine, TrackArc, TrackArcCW>> Tracks;
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
                // [Xml::Element("Dot")] public List<Dot> Dots_;
                Xml::Array<Dot> Dots;
            };
            // Признак фиксации.
            // [Xml::Attribute("fixed")] public Bool fixed_;
            Xml::Attr<Bool> fixed;
            /* public bool fixedSpecified_ */
            // Ширина проводника.
            // [Xml::Attribute("width", DataType = "double")] public double width_;
            Xml::Attr<double> width;
            // Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.
            // [Xml::Attribute("zipwireRef")] public string zipwireRef_;
            Xml::Attr<QString> zipwireRef;
            // Описание «капелек» для Subwire.
            /// \note От KilkennyCat: сделал как массив, в спецификации не так, но так удобней
            // [Xml::Array("Teardrops")][Xml::ArrayItem("Teardrop")] public List<Teardrop> Teardrops_;
            Xml::ArrayElem<Teardrop> Teardrops;
            // Начальная точка линии, дуги.
            // [Xml::Element("Start")] public Start start;
            Start start;
            // Описание(я) сегмента проводника.
            /// \note !В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.
            // [Xml::Element(TrackLine),
            //  Xml::Element(TrackArc),
            //  Xml::Element(TrackArcCW)] public List<Object> Tracks_;
            Xml::Array<Xml::Variant<TrackLine, TrackArc, TrackArcCW>> Tracks;

            QGraphicsItem* graphicsItem(const QColor& color = Qt::red) const;
        };
        // Ссылка на слой.
        // [Xml::Element("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
        // [Xml::Element("Subwire")] public List<Subwire> Subwires_;
        Xml::Array<Subwire> Subwires;
    };
    // Описание заливаемой области металлизации (полигона).
    /// \note !Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.
    struct Copper {
        // Описание термобарьера для подключения контактных площадок к области металлизации.
        struct ThermalPad {
            // Описание термобарьера.
            // [Xml::Element("Thermal")] public Thermal thermal;
            Xml::Optional<Thermal> thermal;
        };
        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        struct ThermalVia {
            // Описание термобарьера.
            // [Xml::Element("Thermal")] public Thermal thermal;
            Xml::Optional<Thermal> thermal;
        };
        // Описание контура заливаемой области металлизации.
        struct Shape {
            // Описание залитой фигуры.
            // [Xml::Element(FilledCircle),
            //  Xml::Element(FilledRect),
            //  Xml::Element(Polygon),
            //  Xml::Element(FilledContour)] public Object FilledFigure_;
            Xml::Variant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
        };
        // Описание островка области металлизации.
        struct Island {
            // Описание спицы термобарьера, присутствующего на плате
            struct ThermalSpoke {
                // Толщина линии.
                // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
                Xml::Attr<double> lineWidth;
                // Описания координат точек, вершин.
                /// \note !В случае отсутствия - весь ThermalSpoke будет проигнорирован.
                // [Xml::Element("Dot")] public List<Dot> Dots_;
                Xml::ArrayElem<Dot> Dots;
            };
            // Описание многоугольника.
            // [Xml::Element(Polygon),
            //  Xml::Element(FilledContour)] public Object Polygon_;
            Xml::Variant<Polygon, FilledContour> Polygon_;
            // Вырезы в островке области металлизации.
            /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
            // [Xml::Array("Voids")][Xml::ArrayItem(Polygon), Xml::ArrayItem(FilledContour)] public List<Object> Voids_;
            Xml::ArrayElem<Xml::Variant<Polygon, FilledContour>, Xml::DontSkip> Voids;
            // Описание спиц термобарьеров, присутствующих на плате
            // [Xml::Element("ThermalSpoke")] public List<ThermalSpoke> ThermalSpokes_;
            Xml::ArrayElem<ThermalSpoke> ThermalSpokes;
        };
        // Параметр области металлизации (полигона): приоритет заливки.
        // [Xml::Attribute("priority", DataType ="int")] public int priority_;
        Xml::Attr<int> priority;
        // Параметр области металлизации (полигона): использовать указанный зазор.
        // [Xml::Attribute("useBackoff")] public Bool useBackoff_;
        Xml::Attr<Bool> useBackoff;
        /* public bool useBackoffSpecified_ */
        // Параметр области металлизации (полигона): зазор до области металлизации.
        // [Xml::Attribute("backoff", DataType ="double")] public double backoff_;
        Xml::Attr<double> backoff;
        // Параметр области металлизации (полигона) стека: подключение контактных площадок.
        // [Xml::Attribute("connectPad")] public connectPad connectPad_;
        Xml::Attr<connectPad> connectPad_;
        // Параметр области металлизации (полигона): подключение площадок переходных отверстий.
        // [Xml::Attribute("connectVia")] public connectVia connectVia_;
        Xml::Attr<connectVia> connectVia_;
        // Толщина линии.
        // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
        Xml::Attr<double> lineWidth;
        // Параметр области металлизации (полигона): зазор между линиями штриховки.
        // [Xml::Attribute("lineClr", DataType = "double")] public double lineClr_;
        Xml::Attr<double> lineClr;
        // Параметр области металлизации (полигона): минимальная площадь островка.
        // [Xml::Attribute("minSquare", DataType = "double")] public double minSquare_;
        Xml::Attr<double> minSquare;
        // Параметр области металлизации (полигона): точность аппроксимации контура.
        // [Xml::Attribute("precision")] public precision precision_;
        Xml::Attr<precision> precision_;
        // Параметр области металлизации (полигона): удалять неподключенные островки.
        // [Xml::Attribute("deleteUnconnected")] public Bool deleteUnconnected_;
        Xml::Attr<Bool> deleteUnconnected;
        /* public bool deleteUnconnectedSpecified_ */
        // Параметр области металлизации (полигона): состояние.
        // [Xml::Attribute("state")] public state state_;
        Xml::Attr<state> state_;
        // Параметр области металлизации (полигона): тип заливки.
        // [Xml::Attribute("fillType")] public fillType fillType_;
        Xml::Attr<fillType> fillType_;
        // Ссылка на слой.
        // [Xml::Element("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
        Xml::Optional<NetRef> netRef;
        // Описание термобарьера для подключения контактных площадок к области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [Xml::Element("ThermalPad")] public ThermalPad thermalPad;
        ThermalPad thermalPad;
        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [Xml::Element("ThermalVia")] public ThermalVia thermalVia;
        ThermalVia thermalVia;
        // Описание контура заливаемой области металлизации..
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [Xml::Element("Shape")] public Shape Shape_;
        Shape Shape_;
        // Вырезы в областях металлизации (полигонах) заданные пользователем.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [Xml::Array("Voids")][Xml::ArrayItem(FilledCircle), Xml::ArrayItem(FilledRect), Xml::ArrayItem(Polygon), Xml::ArrayItem(FilledContour)] public List<Object> Voids_;
        Xml::ArrayElem<Xml::Variant<
                           ArcCCW,
                           ArcCW,
                           ArcByAngle,
                           ArcByMiddle,
                           Circle,
                           Line,
                           Polyline,
                           Rect,
                           Contour>,
            Xml::DontSkip>
            Voids;
        // Островки области металлизации.
        /// \note !В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.
        // [Xml::Array("Islands")][Xml::ArrayItem("Island")] public List<Island> Islands_;
        Xml::ArrayElem<Island> Islands;
        // Заливка областей металлизации (полигонов) линиями.
        /// \note !TopoR при импорте игнорирует эту информацию и строит заливку заново.
        // [Xml::Array("Fill")][Xml::ArrayItem("Line")] public List<Line> Fill_lines_;
        Xml::ArrayElem<Line> Fill;
    };
    // Описание незаливаемой области металлизации.
    struct NonfilledCopper {
        // Описание контура незаливаемой области металлизации.
        struct Shape {
            // Описание фигуры.
            // [Xml::Element(ArcCCW),
            //  Xml::Element(ArcCW),
            //  Xml::Element(ArcByAngle),
            //  Xml::Element(ArcByMiddle),
            //  Xml::Element(Circle),
            //  Xml::Element(Line),
            //  Xml::Element(Polyline),
            //  Xml::Element(Rect),
            //  Xml::Element(Contour)] public Object FigureContPoliline_;
            Xml::Variant<ArcCCW,
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
        // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
        Xml::Attr<double> lineWidth;
        // Ссылка на слой.
        // [Xml::Element("LayerRef")] public LayerRef layerRef;
        LayerRef layerRef;
        // Ссылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
        Xml::Optional<NetRef> netRef;
        // Описание контура незаливаемой области металлизации.
        // [Xml::Element("Shape")] public Shape Shape_;
        Shape Shape_;
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Переходные отверстия на плате.
    // [Xml::Array("Vias")][Xml::ArrayItem("Via")] public List<Via> Vias_;
    Xml::ArrayElem<Via> Vias;
    // Змейки
    // [Xml::Array("Serpents")][Xml::ArrayItem("Serpent")] public List<Serpent> Serpents_;
    Xml::ArrayElem<Serpent> Serpents;
    // Застёгнутые пары проводников.
    // [Xml::Array("ZippedWires")][Xml::ArrayItem("ZippedWire")] public List<ZippedWire> ZippedWires_;
    Xml::ArrayElem<ZippedWire> ZippedWires;
    // Проводники.
    // [Xml::Array("Wires")][Xml::ArrayItem("Wire")] public List<Wire> Wires_;
    Xml::ArrayElem<Wire> Wires;
    // Oбласти металлизации (полигонов).
    // [Xml::Array("Coppers")][Xml::ArrayItem("Copper")] public List<Copper_Connectivity> Coppers_;
    Xml::ArrayElem<Copper> Coppers;
    // Незаливаемые области металлизации.
    // [Xml::Array("NonfilledCoppers")][Xml::ArrayItem("NonfilledCopper")] public List<NonfilledCopper> NonfilledCoppers_;
    Xml::ArrayElem<NonfilledCopper> NonfilledCoppers;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Connectivity. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
};
} // namespace TopoR
