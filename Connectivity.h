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
class Connectivity {

    // Переходное отверстие на плате.

public:
    class Via {

        // Признак фиксации.

    public:
        //[XmlAttribute("fixed")] public Bool _fixed;
        Bool _fixed{};

        //[XmlIgnore] public bool _fixedSpecified
        bool getFixedSpecified() const;

        // Ссылка на тип переходного отверстия.

        //[XmlElement("ViastackRef")] public ViastackRef _ViastackRef;
        std::optional<ViastackRef> _ViastackRef;

        // Ссылка на цепь.

        //[XmlElement("NetRef")] public NetRef _NetRef;
        std::optional<NetRef> _NetRef;

        // Точка привязки объекта.

        //[XmlElement("Org")] public Org _Org;
        std::optional<Org> _Org;
    };

    // Описание змейки.

    // <remarks>! Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)</remarks>
public:
    class Serpent {

        // Идентификатор неименованных объектов.

    public:
        //[XmlAttribute("id")] public string _id;
        std::string _id;

        // Параметр змейки: требуемая длина.

        //[XmlAttribute("Count", DataType ="float")] public float _Count;
        float _Count = 0.0F;

        // Параметр змейки: зазор между соседними изломами.

        //[XmlAttribute("gap", DataType = "float")] public float _gap;
        float _gap = 0.0F;

        // Параметр змейки: высота h1 (см. описание змейки Serpent).

        //[XmlAttribute("h1", DataType = "float")] public float _h1;
        float _h1 = 0.0F;

        // Параметр змейки: высота h2 (см. описание змейки Serpent).

        //[XmlAttribute("h2", DataType = "float")] public float _h2;
        float _h2 = 0.0F;

        // Параметр змейки: высота h3 (см. описание змейки Serpent).

        //[XmlAttribute("h3", DataType = "float")] public float _h3;
        float _h3 = 0.0F;

        // Параметр змейки: высота h4 (см. описание змейки Serpent).

        //[XmlAttribute("h4", DataType = "float")] public float _h4;
        float _h4 = 0.0F;
    };

    // Описание застёгнутой пары проводников.

    // <remarks>! Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.</remarks>
public:
    class ZippedWire {

        // Идентификатор неименованных объектов.

    public:
        //[XmlAttribute("id")] public string _id;
        std::string _id;

        // Признак фиксации.

        //[XmlAttribute("fixed")] public Bool _fixed;
        Bool _fixed{};

        //[XmlIgnore] public bool _fixedSpecified
        bool getFixedSpecified() const;

        // Ссылка на слой.

        //[XmlElement("LayerRef")] public LayerRef _LayerRef;
        std::optional<LayerRef> _LayerRef;

        // Ссылка на дифференциальный сигнал.

        //[XmlElement("DiffSignalRef")] public DiffSignalRef _DiffSignalRef;
        std::optional<DiffSignalRef> _DiffSignalRef;

        // Начальная точка линии, дуги.

        //[XmlElement("Start")] public Start _Start;
        std::optional<Start> _Start;

        // Описание(я) сегмента проводника.

        // <remarks>! В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.</remarks>

        //[XmlElement("TrackLine", typeof(TrackLine)), XmlElement("TrackArc", typeof(TrackArc)), XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks;
        std::vector<std::any> _Tracks;
        bool ShouldSerialize_Tracks();
    };

    // Описание проводника.

public:
    class Wire {

        // Описание части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).

        // <remarks>! Атрибут zipwireRef (ссылка на застёгнутую пару проводников) используется, если описываемая часть проводника входит в застёгнутую пару проводников ZippedWire (см. пример описания проводника дифференциальной пары).</remarks>
    public:
        class Subwire {

            // Описание «капельки» четырёхугольником. Первая вершина соответствует точке привязки контакта (переходного отверстия). Остальные вершины описывают контур четырёхугольника против часовой стрелки.

            // <remarks> ! TopoR при импорте игнорирует информацию о капельках.</remarks>
        public:
            class Teardrop {

                // координаты точки, вершины.

            public:
                //[XmlElement("Dot")] public List<Dot> _Dots;
                std::vector<std::optional<Dot>> _Dots;
                bool ShouldSerialize_Dots();
            };

            // Признак фиксации.

        public:
            //[XmlAttribute("fixed")] public Bool _fixed;
            Bool _fixed{};

            //[XmlIgnore] public bool _fixedSpecified
            bool getFixedSpecified() const;

            // Ширина проводника.

            //[XmlAttribute("width", DataType = "float")] public float _width;
            float _width = 0.0F;

            // Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.

            //[XmlAttribute("zipwireRef")] public string _zipwireRef;
            std::string _zipwireRef;

            // Описание «капелек» для Subwire.

            // <remarks>От KilkennyCat: сделал как массив, в спецификации не так, но так удобней</remarks>

            //[XmlArray("Teardrops")][XmlArrayItem("Teardrop")] public List<Teardrop> _Teardrops;
            std::vector<std::optional<Teardrop>> _Teardrops;
            bool ShouldSerialize_Teardrops();

            // Начальная точка линии, дуги.

            //[XmlElement("Start")] public Start _Start;
            std::optional<Start> _Start;

            // Описание(я) сегмента проводника.

            // <remarks>! В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.</remarks>

            //[XmlElement("TrackLine", typeof(TrackLine)), XmlElement("TrackArc", typeof(TrackArc)), XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks;
            std::vector<std::any> _Tracks;
            bool ShouldSerialize_Tracks();
        };

        // Ссылка на слой.

    public:
        //[XmlElement("LayerRef")] public LayerRef _LayerRef;
        std::optional<LayerRef> _LayerRef;

        // Ссылка на цепь.

        //[XmlElement("NetRef")] public NetRef _NetRef;
        std::optional<NetRef> _NetRef;

        // Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).

        //[XmlElement("Subwire")] public List<Subwire> _Subwires;
        std::vector<std::optional<Subwire>> _Subwires;
        bool ShouldSerialize_Subwires();
    };

    // Описание заливаемой области металлизации (полигона).

    // <remarks>! Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.</remarks>
public:
    class Copper_Connectivity {

        // Описание термобарьера для подключения контактных площадок к области металлизации.

    public:
        class ThermalPad {

            // Описание термобарьера.

        public:
            //[XmlElement("Thermal")] public Thermal _Thermal;
            std::optional<Thermal> _Thermal;
        };

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.

    public:
        class ThermalVia {

            // Описание термобарьера.

        public:
            //[XmlElement("Thermal")] public Thermal _Thermal;
            std::optional<Thermal> _Thermal;
        };

        // Описание контура заливаемой области металлизации.

    public:
        class Shape_Copper {

            // Описание залитой фигуры.

        public:
            //[XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("FilledContour", typeof(FilledContour))] public Object _FilledFigure;
            std::any _FilledFigure;
        };

        // Описание островка области металлизации.

    public:
        class Island {

            // Описание спицы термобарьера, присутствующего на плате

        public:
            class ThermalSpoke {

                // Толщина линии.

            public:
                //[XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
                float _lineWidth = 0.0F;

                // Описания координат точек, вершин.

                // <remarks>! В случае отсутствия - весь ThermalSpoke будет проигнорирован.</remarks>

                //[XmlElement("Dot")] public List<Dot> _Dots;
                std::vector<std::optional<Dot>> _Dots;
                bool ShouldSerialize_Dots();
            };

            // Описание многоугольника.

        public:
            //[XmlElement("Polygon", typeof(Polygon)), XmlElement("FilledContour", typeof(FilledContour))] public Object _Polygon;
            std::any _Polygon;

            // Вырезы в островке области металлизации.

            // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

            //[XmlArray("Voids")][XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids;
            std::vector<std::any> _Voids;

            // Описание спиц термобарьеров, присутствующих на плате

            //[XmlElement("ThermalSpoke")] public List<ThermalSpoke> _ThermalSpokes;
            std::vector<std::optional<ThermalSpoke>> _ThermalSpokes;
            bool ShouldSerialize_ThermalSpokes();
        };

        // Параметр области металлизации (полигона): приоритет заливки.

    public:
        //[XmlAttribute("priority", DataType ="int")] public int _priority;
        int _priority = 0;

        // Параметр области металлизации (полигона): использовать указанный зазор.

        //[XmlAttribute("useBackoff")] public Bool _useBackoff;
        Bool _useBackoff{};

        //[XmlIgnore] public bool _useBackoffSpecified
        bool getUseBackoffSpecified() const;

        // Параметр области металлизации (полигона): зазор до области металлизации.

        //[XmlAttribute("backoff", DataType ="float")] public float _backoff;
        float _backoff = 0.0F;

        // Параметр области металлизации (полигона) стека: подключение контактных площадок.

        //[XmlAttribute("connectPad")] public connectPad _connectPad;
        connectPad _connectPad{};

        // Параметр области металлизации (полигона): подключение площадок переходных отверстий.

        //[XmlAttribute("connectVia")] public connectVia _connectVia;
        connectVia _connectVia{};

        // Толщина линии.

        //[XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
        float _lineWidth = 0.0F;

        // Параметр области металлизации (полигона): зазор между линиями штриховки.

        //[XmlAttribute("lineClr", DataType = "float")] public float _lineClr;
        float _lineClr = 0.0F;

        // Параметр области металлизации (полигона): минимальная площадь островка.

        //[XmlAttribute("minSquare", DataType = "float")] public float _minSquare;
        float _minSquare = 0.0F;

        // Параметр области металлизации (полигона): точность аппроксимации контура.

        //[XmlAttribute("precision")] public precision _precision;
        precision _precision{};

        // Параметр области металлизации (полигона): удалять неподключенные островки.

        //[XmlAttribute("deleteUnconnected")] public Bool _deleteUnconnected;
        Bool _deleteUnconnected{};

        //[XmlIgnore] public bool _deleteUnconnectedSpecified
        bool getDeleteUnconnectedSpecified() const;

        // Параметр области металлизации (полигона): состояние.

        //[XmlAttribute("state")] public state _state;
        state _state{};

        // Параметр области металлизации (полигона): тип заливки.

        //[XmlAttribute("fillType")] public fillType _fillType;
        fillType _fillType{};

        // Ссылка на слой.

        //[XmlElement("LayerRef")] public LayerRef _LayerRef;
        std::optional<LayerRef> _LayerRef;

        // Ссылка на цепь.

        //[XmlElement("NetRef")] public NetRef _NetRef;
        std::optional<NetRef> _NetRef;

        // Описание термобарьера для подключения контактных площадок к области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        //[XmlElement("ThermalPad")] public ThermalPad _ThermalPad;
        std::optional<ThermalPad> _ThermalPad;

        // Описание термобарьера для подключения площадок переходных отверстий к области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        //[XmlElement("ThermalVia")] public ThermalVia _ThermalVia;
        std::optional<ThermalVia> _ThermalVia;

        // Описание контура заливаемой области металлизации..

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        //[XmlElement("Shape")] public Shape_Copper _Shape;
        std::optional<Shape_Copper> _Shape;

        // Вырезы в областях металлизации (полигонах) заданные пользователем.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        //[XmlArray("Voids")][XmlArrayItem("FilledCircle", typeof(FilledCircle)), XmlArrayItem("FilledRect", typeof(FilledRect)), XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids;
        std::vector<std::any> _Voids;

        // Островки области металлизации.

        // <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>

        //[XmlArray("Islands")][XmlArrayItem("Island")] public List<Island> _Islands;
        std::vector<std::optional<Island>> _Islands;

        // Заливка областей металлизации (полигонов) линиями.

        // <remarks>! TopoR при импорте игнорирует эту информацию и строит заливку заново.</remarks>

        //[XmlArray("Fill")][XmlArrayItem("Line")] public List<Line> _Fill_lines;
        std::vector<std::optional<Line>> _Fill_lines;
        bool ShouldSerialize_Fill_lines();
    };

    // Описание незаливаемой области металлизации.

public:
    class NonfilledCopper {

        // Описание контура незаливаемой области металлизации.

    public:
        class Shape_NonfilledCopper {

            // Описание фигуры.

        public:
            //[XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Circle", typeof(Circle)), XmlElement("Line", typeof(Line)), XmlElement("Polyline", typeof(Polyline)), XmlElement("Rect", typeof(Rect)), XmlElement("Contour", typeof(Contour))] public Object _FigureContPoliline;
            std::any _FigureContPoliline;
        };

        // Толщина линии.

    public:
        //[XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
        float _lineWidth = 0.0F;

        // Ссылка на слой.

        //[XmlElement("LayerRef")] public LayerRef _LayerRef;
        std::optional<LayerRef> _LayerRef;

        // Ссылка на цепь.

        //[XmlElement("NetRef")] public NetRef _NetRef;
        std::optional<NetRef> _NetRef;

        // Описание контура незаливаемой области металлизации.

        //[XmlElement("Shape")] public Shape_NonfilledCopper _Shape;
        std::optional<Shape_NonfilledCopper> _Shape;
    };

    // Версия раздела.

public:
    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Переходные отверстия на плате.

    //[XmlArray("Vias")][XmlArrayItem("Via")] public List<Via> _Vias;
    std::vector<std::optional<Via>> _Vias;
    bool ShouldSerialize_Vias();

    // Змейки

    //[XmlArray("Serpents")][XmlArrayItem("Serpent")] public List<Serpent> _Serpents;
    std::vector<std::optional<Serpent>> _Serpents;
    bool ShouldSerialize_Serpents();

    // Застёгнутые пары проводников.

    //[XmlArray("ZippedWires")][XmlArrayItem("ZippedWire")] public List<ZippedWire> _ZippedWires;
    std::vector<std::optional<ZippedWire>> _ZippedWires;
    bool ShouldSerialize_ZippedWires();

    // Проводники.

    //[XmlArray("Wires")][XmlArrayItem("Wire")] public List<Wire> _Wires;
    std::vector<std::optional<Wire>> _Wires;
    bool ShouldSerialize_Wires();

    // Oбласти металлизации (полигонов).

    //[XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Connectivity> _Coppers;
    std::vector<std::optional<Copper_Connectivity>> _Coppers;
    bool ShouldSerialize_Coppers();

    // Незаливаемые области металлизации.

    //[XmlArray("NonfilledCoppers")][XmlArrayItem("NonfilledCopper")] public List<NonfilledCopper> _NonfilledCoppers;
    std::vector<std::optional<NonfilledCopper>> _NonfilledCoppers;
    bool ShouldSerialize_NonfilledCoppers();

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Connectivity. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    /************************************************************************/
};
} // namespace TopoR_PCB_Classes
