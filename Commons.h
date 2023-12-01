#pragma once

// #include "enumerator.h"
#include "Enums.h"
#include <QString>
#include <array>
#include <limits>
#include <optional>
#include <string>
#include <variant>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// struct Shift;
struct base_coordinat;

template <typename T>
struct XmlAttr {
    T value{};
    operator T&() noexcept { return value; }
    operator const T&() const noexcept { return value; }
    T& operator=(const T& val) noexcept { return value = val; }
    T& operator=(T&& val) noexcept { return value = val; }
};

//	#region Reference Types

// базовый класс ссылок.

// struct BaseRef {
//     // Имя объекта или ссылка на именованный объект.
//     /* [XmlAttribute("name")] public string _ReferenceName; */
//     std::string _ReferenceName;
// };

// Ссылка на атрибут.

struct AttributeRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на тип слоя.
struct LayerTypeRef {
    // Тип слоя.
    /* [XmlAttribute("type")] public layer_type _type; */
    layer_type _type{};
};

// Ссылка на группу слоёв.

struct LayerGroupRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на слой.
// <remarks>! Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.</remarks>
struct LayerRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;

    // Тип слоя или ссылка на именованный cлой

    // <remarks>В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено</remarks>
    // TODO:
    //   XmlAttribute("type", typeof(type_layer)),
};

// Ссылка на тип переходного отверстия.

struct ViastackRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на стек контактных площадок.

struct NetRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на группу компонентов.

struct CompGroupRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на компонент на плате.

struct CompInstanceRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на группу цепей.

struct NetGroupRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на волновое сопротивление.

struct ImpedanceRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на сигнал.

struct SignalRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на группу сигналов..

struct SignalGroupRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на дифференциальный сигнал.

struct DiffSignalRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на контакт.

struct PinRef {
    // Имя компонента, используется для ссылки на компонент.
    /* [XmlAttribute("compName")] public string _compName; */
    std::string _compName;
    // Имя контакта компонента, используется для ссылки.
    /* [XmlAttribute("pinName")] public string _pinName; */
    std::string _pinName;
};

// Ссылка на контакт источника сигнала.

struct SourcePinRef /*: public PinRef*/ {
    // Имя компонента, используется для ссылки на компонент.
    /* [XmlAttribute("compName")] public string _compName; */
    std::string _compName;
    // Имя контакта компонента, используется для ссылки.
    /* [XmlAttribute("pinName")] public string _pinName; */
    std::string _pinName;
};

// Ссылка на контакт приёмника сигнала.

struct ReceiverPinRef /*: public PinRef*/ {
    // Имя компонента, используется для ссылки на компонент.
    /* [XmlAttribute("compName")] public string _compName; */
    std::string _compName;
    // Имя контакта компонента, используется для ссылки.
    /* [XmlAttribute("pinName")] public string _pinName; */
    std::string _pinName;
};

// Ссылка на стек контактных площадок.

struct PadstackRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на стиль надписей.

struct TextStyleRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на схемный компонент.

struct ComponentRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на посадочное место.

struct FootprintRef /*: public BaseRef */ {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string _ReferenceName; */
    std::string _ReferenceName;
};

// Ссылка на вывод посадочного места.

struct PadRef {
    // Ссылка на имя компонента
    /* [XmlAttribute("compName")] public string _compName; */
    std::string _compName;
    // Номер контактной площадки (вывода) посадочного места.
    /* [XmlAttribute("padNum", DataType = "int")] public int _padNum; */
    XmlAttr<int> padNum; // int _padNum = 0;
};
//	#endregion Reference Type

//	#region Coordinates

struct base_coordinat {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
    void Shift(float x, float y);
    void UnitsConvert(dist in_units, dist out_units);
};

// координаты точки, вершины.
struct Dot /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Центр круга (окружности), овала.
struct Center /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Начальная точка линии, дуги.
struct Start /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Средняя точка дуги.
struct Middle /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Конечная точка линии, дуги.
struct End /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Точка привязки объекта.
struct Org /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Cмещение точки привязки или объекта по осям x и y.
struct Shift /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

// Вытягивание по осям x и y.
struct Stretch /*: public base_coordinat*/ {
    /* [XmlAttribute("x", DataType = "float")] public float _x; */
    XmlAttr<float> x; // float _x = 0.0F;
    /* [XmlAttribute("y", DataType = "float")] public float _y; */
    XmlAttr<float> y; // float _y = 0.0F;
};

//	#endregion Coordinates

//	#region Segments
// struct IBaseSegment {
//     virtual void Shift(float x, float y) = 0;
//     virtual void UnitsConvert(dist in_units, dist out_units) = 0;
// };

// Описание прямолинейного сегмента контура.

struct SegmentLine /*: public IBaseSegment*/ {
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;
    void Shift(float x, float y) /*override*/;
    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход против часовой стрелки.

struct SegmentArcCCW : public SegmentLine {
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center _Center; */
    std::optional<Center> _Center;
    void Shift(float x, float y);
    void UnitsConvert(dist in_units, dist out_units);
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход по часовой стрелки.

struct SegmentArcCW : public SegmentArcCCW {
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.

struct SegmentArcByAngle : public SegmentLine {

    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
    XmlAttr<float> angle; // float _angle = 0.0F;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.

struct SegmentArcByMiddle : public SegmentLine {

    // Конечная точка линии, дуги.
    /* [XmlElement("Middle")] public Middle _Middle; */
    std::optional<Middle> _Middle;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};
//	#endregion Segments

//	#region Figures

// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов

struct IBaseFigure {

    virtual void UnitsConvert(dist in_units, dist out_units) = 0;
    virtual void Shift(float x, float y) = 0;
};

// Дуга, заданная центром. Обход против часовой стрелки.

struct ArcCCW /*: public IBaseFigure*/ {

    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center _Center; */
    std::optional<Center> _Center;

    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start _Start; */
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Дуга, заданная центром. Обход по часовой стрелке.

struct ArcCW : public ArcCCW {
};

// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.

struct ArcByAngle /*: public IBaseFigure*/ {

    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
    XmlAttr<float> angle; // float _angle = 0.0F;

    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start _Start; */
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Дуга, заданная тремя точками: начало, середина и конец.

struct ArcByMiddle /*: public IBaseFigure*/ {

    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start _Start; */
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.
    /* [XmlElement("Middle")] public Middle _Middle; */
    std::optional<Middle> _Middle;

    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание окружности (незалитого круга).

struct Circle /*: public IBaseFigure*/ {

    // Диаметр окружности, круга, овала.
    /* [XmlAttribute("diameter", DataType = "float")] public float _diameter; */
    XmlAttr<float> diameter; // float _diameter = 0.0F;

    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center _Center; */
    std::optional<Center> _Center;

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание линии.

struct Line /*: public IBaseFigure*/ {

    // Массив координат точек, вершин.
    /* [XmlElement("Dot")] public List<Dot> _Dots; */
    std::vector<std::optional<Dot>> _Dots;
    bool ShouldSerialize_Dots();

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание полилинии.

struct Polyline /*: public IBaseFigure*/ {

    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start _Start; */
    std::optional<Start> _Start;

    // Сегменты.
    /* [XmlElement("SegmentLine", typeof(SegmentLine)),
XmlElement("SegmentArcByAngle", typeof(SegmentArcByAngle)),
XmlElement("SegmentArcCCW", typeof(SegmentArcCCW)),
XmlElement("SegmentArcCW", typeof(SegmentArcCW)),
XmlElement("SegmentArcByMiddle", typeof(SegmentArcByMiddle))
] public List<Object> _Segments; */
    std::vector<std::variant<
        SegmentArcByAngle,
        SegmentArcByMiddle,
        SegmentArcCCW,
        SegmentArcCW,
        SegmentLine>>
        _Segments;
    bool ShouldSerialize_Segments();
    void Shift(float x, float y) /*override*/;
    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.

struct Contour : public Polyline {
    using Polyline::Polyline;
};

// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины

struct Rect : public Line {
    using Line::Line;
};

// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.

struct FilledContour : public Polyline {

}; // TODO: требует уточнения

// Описание круга.

struct FilledCircle : public Circle {
};

// Описание залитого прямоугольника.

struct FilledRect : public Rect {
};

// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.

struct Polygon : public Line {
};

// Описание дугообразного сегмента проводника (дуга по часовой стрелке).

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackArcCW /*: public IBaseFigure*/ {

    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center _Center; */
    std::optional<Center> _Center;

    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;

    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /* [XmlAttribute("serpRef")] public string _serpRef; */
    std::string _serpRef;

    void Shift(float x, float y) /*override*/;
    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

// Описание дугообразного сегмента проводника (дуга против часовой стрелки).

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackArc : public TrackArcCW {
};

// Описание прямолинейного сегмента проводника.

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackLine /*: public IBaseFigure*/ {

    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End _End; */
    std::optional<End> _End;

    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /* [XmlAttribute("serpRef")] public string _serpRef; */
    std::string _serpRef;

    void Shift(float x, float y) /*override*/;

    void UnitsConvert(dist in_units, dist out_units) /*override*/;
};

//	#endregion Figures

//	#region Rules area

// Устанавливает область действия правила: все слои.

struct AllLayers {
    /* [XmlElement("AllLayers")] public string _AllLayers; */
    std::string _AllLayers;
};

// Устанавливает область действия правила: все компоненты.

struct AllComps {
    /* [XmlElement("AllComps")] public string _AllComps; */
    std::string _AllComps;
};

// Устанавливает область действия правила: все цепи.

struct AllNets {
    /* [XmlElement("AllNets")] public string _AllNets; */
    std::string _AllNets;
};

// Устанавливает область действия правила: все внутренние слои.

struct AllLayersInner {
    /* [XmlElement("AllLayersInner")] public string _AllLayersInner; */
    std::string _AllLayersInner;
};

// Устанавливает область действия правила: все внутренние сигнальные слои.

struct AllLayersInnerSignal {
    /* [XmlElement("AllLayersInnerSignal")] public string _AllLayersInnerSignal; */
    std::string _AllLayersInnerSignal;
};

// Устанавливает область действия правила: все сигнальные слои.

struct AllLayersSignal {
    /* [XmlElement("AllLayersSignal")] public string _AllLayersSignal; */
    std::string _AllLayersSignal;
};

// Устанавливает область действия правила: все внешние слои.

struct AllLayersOuter {
    /* [XmlElement("AllLayersOuter")] public string _AllLayersOuter; */
    std::string _AllLayersOuter;
};

// Устанавливает доступные типы переходных отверстий для правила: все типы.

struct AllViastacks {
    /* [XmlElement("AllViastacks")] public string _AllViastacks; */
    std::string _AllViastacks;
};

// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.

struct AllViastacksThrough {
    /* [XmlElement("AllViastacksThrough")] public string _AllViastacksThrough; */
    std::string _AllViastacksThrough;
};

// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.

struct AllViastacksNotThrough {
    /* [XmlElement("AllViastacksNotThrough")] public string _AllViastacksNotThrough; */
    std::string _AllViastacksNotThrough;
};
//	#endregion Rules area

//	#region Thermal Detail Text ObjectSignal

// Описание термобарьера.

struct Thermal {

    // Параметр термобарьера: число спиц.! В TopoR поддерживается только одно значение – 4.
    /* [XmlAttribute("spokeNum", DataType = "int")] public int _spokeNum; */
    XmlAttr<int> spokeNum; // int _spokeNum = 0;

    // Параметр термобарьера: минимальное число спиц.
    /* [XmlAttribute("minSpokeNum", DataType = "int")] public int _minSpokeNum; */
    XmlAttr<int> minSpokeNum; // int _minSpokeNum = 0;

    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
    XmlAttr<float> angle; // float _angle = 0.0F;

    // Параметр термобарьера: ширина спицы.
    /* [XmlAttribute("spokeWidth", DataType = "float")] public float _spokeWidth; */
    XmlAttr<float> spokeWidth; // float _spokeWidth = 0.0F;

    // Параметр термобарьера: зазор между контактной площадкой и областью металлизации.
    /* [XmlAttribute("backoff", DataType = "float")] public float _backoff; */
    XmlAttr<float> backoff; // float _backoff = 0.0F;

    void UnitsConvert(dist in_units, dist out_units);
};

// Описание детали.

struct Detail {

    // Толщина линии.
    /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
    XmlAttr<float> lineWidth; // float _lineWidth = 0.0F;

    // Ссылка на слой.
    /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
    std::optional<LayerRef> _LayerRef;

    // Описание фигуры.
    /* [XmlElement("ArcCCW", typeof(ArcCCW)),
        XmlElement("ArcCW", typeof(ArcCW)),
        XmlElement("ArcByAngle", typeof(ArcByAngle)),
        XmlElement("ArcByMiddle", typeof(ArcByMiddle)),
        XmlElement("Line", typeof(Line)),
        XmlElement("Circle", typeof(Circle)),
        XmlElement("Rect", typeof(Rect)),
        XmlElement("FilledCircle", typeof(FilledCircle)),
        XmlElement("FilledRect", typeof(FilledRect)),
        XmlElement("Polygon", typeof(Polygon)),
        XmlElement("Polyline", typeof(Polyline)),
        XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure; */
    std::variant<ArcCCW,
        ArcCW,
        ArcByAngle,
        ArcByMiddle,
        Line,
        Circle,
        Rect,
        FilledCircle,
        FilledRect,
        Polygon,
        Polyline,
        FilledContour>
        _Figure;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};

// Описание надписи.
struct Text {

    // Параметр надписи: текст надписи.
    /* [XmlAttribute("text")] public string _text; */
    std::string _text;

    // Параметр надписей (ярлыков): способ выравнивания текста.
    /* [XmlAttribute("align")] public align _align; */
    align _align{};

    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
    XmlAttr<float> angle; // float _angle = 0.0F;

    // Параметр надписей и ярлыков: зеркальность отображения.
    /* [XmlAttribute("mirror")] public Bool _mirror; */
    Bool _mirror{};
    /* public bool _mirrorSpecified */
    bool getMirrorSpecified() const;

    // Ссылка на слой.
    /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
    std::optional<LayerRef> _LayerRef;

    // Ссылка на стиль надписей.
    /* [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef; */
    std::optional<TextStyleRef> _TextStyleRef;

    // Точка привязки объекта.
    /* [XmlElement("Org")] public Org _Org; */
    std::optional<Org> _Org;

    void Shift(float x, float y);

    // TODO: конвертировать текстовые стили по ссылке

    // <param name="in_units"></param>
    // <param name="out_units"></param>
    void UnitsConvert(dist in_units, dist out_units);
};

// Сигналы воздействия правила
struct ObjectSignal {
    /* [XmlElement("SignalRef", typeof(SignalRef)),
        XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
        XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object _Refs; */
    std::variant<SignalRef, DiffSignalRef, SignalGroupRef> _Refs;
};

//	#endregion

// Различные сервисные функции
struct Ut final {

    // Конвертация единиц измерения

    // <param name="value">значение</param>
    // <param name="in_units">текущие единицы измерения</param>
    // <param name="out_units">выходные единицы измерения</param>
    // <returns>Возвращает сконвертированное значение</returns>

    static float UnitsConvert(float value, dist in_units, dist out_units);
};

} // namespace TopoR_PCB_Classes
