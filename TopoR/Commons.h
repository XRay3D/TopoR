#pragma once
// #include "enumerator.h"
#include "Enums.h"
#include <QPoint>
#include <QString>
#include <QTransform>
#include <array>
#include <limits>
#include <optional>
#include <string>
#include <variant>
#include <vector>
class QGraphicsItem;
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};
template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;
template <typename T>
using Optional = std::optional<T>;
namespace TopoR_PCB_Classes {
struct Shift;
struct base_coordinat;
template <typename T>
struct XmlAttr {
    T value{};
    operator T&() noexcept { return value; }
    operator const T&() const noexcept { return value; }
    T& operator=(const T& val) noexcept { return value = val; }
    T& operator=(T&& val) noexcept { return value = val; }
};
template <typename T>
struct XmlArray : std::vector<T>, std::false_type {
    using std::vector<T>::vector;
};
// template <typename T>
// struct XmlAarrayElem : std::vector<T>, std::true_type {
//     using std::vector<T>::vector;
// };
template <typename... Ts>
struct XmlVariant : std::variant<Ts...> {
    using std::variant<Ts...>::variant;
    template <typename Func>
    auto visit(Func&& func) {
        return std::visit(std::forward<Func>(func), *this);
    }
    template <typename Func>
    auto visit(Func&& func) const {
        return std::visit(std::forward<Func>(func), *this);
    }
    template <typename... Funcs>
    auto visit(Funcs&&... funcs) {
        return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    }
    template <typename... Funcs>
    auto visit(Funcs&&... funcs) const {
        return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    }
};
// #region Reference Types
// базовый класс ссылок.
struct BaseRef {
    // Имя объекта или ссылка на именованный объект.
    /* [XmlAttribute("name")] public string ReferenceName_; */
    XmlAttr<QString> name;
};
// Ссылка на атрибут.
struct AttributeRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на тип слоя.
struct LayerTypeRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на группу слоёв.
struct LayerGroupRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на слой.
// <remarks>! Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.</remarks>
struct LayerRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
    // Тип слоя или ссылка на именованный cлой
    // <remarks>В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено</remarks>
    // TODO:
    // XmlAttribute("type", typeof(type_layer)),
};
// Ссылка на тип переходного отверстия.
struct ViastackRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на стек контактных площадок.
struct NetRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на группу компонентов.
struct CompGroupRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на компонент на плате.
struct CompInstanceRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на группу цепей.
struct NetGroupRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на волновое сопротивление.
struct ImpedanceRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на сигнал.
struct SignalRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на группу сигналов..
struct SignalGroupRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на дифференциальный сигнал.
struct DiffSignalRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на контакт.
struct PinRef {
    // Имя компонента, используется для ссылки на компонент.
    /* [XmlAttribute("compName")] public string compName_; */
    XmlAttr<QString> compName;
    // Имя контакта компонента, используется для ссылки.
    /* [XmlAttribute("pinName")] public string pinName_; */
    XmlAttr<QString> pinName;
};
// Ссылка на контакт источника сигнала.
struct SourcePinRef /*: PinRef*/ {
    // using PinRef::PinRef;
    XmlAttr<QString> compName;
    XmlAttr<QString> pinName;
};
// Ссылка на контакт приёмника сигнала.
struct ReceiverPinRef /*: PinRef*/ {
    // using PinRef::PinRef;
    XmlAttr<QString> compName;
    XmlAttr<QString> pinName;
};
// Ссылка на стек контактных площадок.
struct PadstackRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на стиль надписей.
struct TextStyleRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на схемный компонент.
struct ComponentRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на посадочное место.
struct FootprintRef /*: BaseRef*/ {
    // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};
// Ссылка на вывод посадочного места.
struct PadRef {
    // Ссылка на имя компонента
    /* [XmlAttribute("compName")] public string compName_; */
    XmlAttr<QString> compName;
    // Номер контактной площадки (вывода) посадочного места.
    /* [XmlAttribute("padNum", DataType = "int")] public int padNum_; */
    XmlAttr<int> padNum; // int padNum_ = 0;
};
// #endregion Reference Type
// #region Coordinates
struct base_coordinat {
    /* [XmlAttribute("x", DataType = "float")] public float x_; */
    XmlAttr<float> x;
    /* [XmlAttribute("y", DataType = "float")] public float y_; */
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
    // void Shift(float x, float y);
    // void UnitsConvert(dist in_units, dist out_units);
};
// координаты точки, вершины.
struct Dot /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Центр круга (окружности), овала.
struct Center /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Начальная точка линии, дуги.
struct Start /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Средняя точка дуги.
struct Middle /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Конечная точка линии, дуги.
struct End /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Точка привязки объекта.
struct Org /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Cмещение точки привязки или объекта по осям x и y.
struct Shift /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// Вытягивание по осям x и y.
struct Stretch /*: base_coordinat*/ {
    // using base_coordinat::base_coordinat;
    XmlAttr<float> x;
    XmlAttr<float> y;
    operator QPointF() const { return {x, y}; }
};
// #endregion Coordinates
// #region Segments
// struct IBaseSegment {
// virtual void Shift(float x, float y) = 0;
// virtual void UnitsConvert(dist in_units, dist out_units) = 0;
// };
// Описание прямолинейного сегмента контура.
struct SegmentLine /*: IBaseSegment*/ {
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход против часовой стрелки.
struct SegmentArcCCW /*: SegmentLine*/ {
    End end;
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
    // void Shift(float x, float y);
    // void UnitsConvert(dist in_units, dist out_units);
};
// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход по часовой стрелки.
struct SegmentArcCW /*: SegmentArcCCW*/ {
    // using SegmentArcCCW::SegmentArcCCW;
    End end;
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
};
// Описание дугообразного сегмента контура.
// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.
struct SegmentArcByAngle /*: SegmentLine*/ {
    End end;
    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
    XmlAttr<float> angle; // float angle_ = 0.0F;
};
// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.
struct SegmentArcByMiddle /*: SegmentLine*/ {
    End end;
    // Конечная точка линии, дуги.
    /* [XmlElement("Middle")] public Middle middle; */
    Middle middle;
    // void Shift(float x, float y);
    // void UnitsConvert(dist in_units, dist out_units);
};
// #endregion Segments
// #region Figures
// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов
struct IBaseFigure {
    // virtual void UnitsConvert(dist in_units, dist out_units) = 0;
    // virtual void Shift(float x, float y) = 0;
};
// Дуга, заданная центром. Обход против часовой стрелки.
struct ArcCCW /*: IBaseFigure*/ {
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start start; */
    Start start;
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Дуга, заданная центром. Обход по часовой стрелке.
struct ArcCW /*: ArcCCW*/ {
    // using ArcCCW::ArcCCW;
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start start; */
    Start start;
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
};
// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
struct ArcByAngle /*: IBaseFigure*/
{
    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
    XmlAttr<float> angle; // float angle_ = 0.0F;
    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start start; */
    Start start;
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Дуга, заданная тремя точками: начало, середина и конец.
struct ArcByMiddle /*: IBaseFigure*/ {
    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start start; */
    Start start;
    // Конечная точка линии, дуги.
    /* [XmlElement("Middle")] public Middle middle; */
    Middle middle;
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание окружности (незалитого круга).
struct Circle /*: IBaseFigure*/ {
    // Диаметр окружности, круга, овала.
    /* [XmlAttribute("diameter", DataType = "float")] public float diameter_; */
    XmlAttr<float> diameter; // float diameter_ = 0.0F;
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание линии.
struct Line /*: IBaseFigure*/ {
    // Массив координат точек, вершин.
    /* [XmlElement("Dot")] public List<Dot> Dots_; */
    std::vector<Dot> Dots;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание полилинии.
struct Polyline /*: IBaseFigure*/
{
    // Начальная точка линии, дуги.
    /* [XmlElement("Start")] public Start start; */
    Start start;
    // Сегменты.
    /* [XmlElement("SegmentLine", typeof(SegmentLine)),
XmlElement("SegmentArcByAngle", typeof(SegmentArcByAngle)),
XmlElement("SegmentArcCCW", typeof(SegmentArcCCW)),
XmlElement("SegmentArcCW", typeof(SegmentArcCW)),
XmlElement("SegmentArcByMiddle", typeof(SegmentArcByMiddle))
] public List<Object> Segments_; */
    std::vector<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments_;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct Contour /*: Polyline*/ {
    // using Polyline::Polyline;
    Start start;
    std::vector<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments_;
};
// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
struct Rect /*: Line*/ {
    // using Line::Line;
    std::vector<Dot> Dots;
};
// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct FilledContour /*: Polyline*/ {
    // using Polyline::Polyline;
    Start start;
    std::vector<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments_;
}; // TODO: требует уточнения
// Описание круга.
struct FilledCircle /*: Circle*/ {
    // using Circle::Circle;
    XmlAttr<float> diameter;
    Center center;
};
// Описание залитого прямоугольника.
struct FilledRect /*: Rect*/ {
    // using Rect::Rect;
    std::vector<Dot> Dots;
};
// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
struct Polygon /*: Line*/ {
    // using Line::Line;
    std::vector<Dot> Dots;
};
// Описание дугообразного сегмента проводника (дуга по часовой стрелке).
// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackArcCW /*: IBaseFigure*/ {
    // Центр круга (окружности), овала.
    /* [XmlElement("Center")] public Center center; */
    Center center;
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /* [XmlAttribute("serpRef")] public string serpRef_; */
    XmlAttr<QString> serpRef;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// Описание дугообразного сегмента проводника (дуга против часовой стрелки).
// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackArc /*: TrackArcCW*/ {
    // using TrackArcCW::TrackArcCW;
    Center center;
    End end;
    XmlAttr<QString> serpRef;
};
// Описание прямолинейного сегмента проводника.
// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
struct TrackLine /*: IBaseFigure*/
{
    // Конечная точка линии, дуги.
    /* [XmlElement("End")] public End end; */
    End end;
    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /* [XmlAttribute("serpRef")] public string serpRef_; */
    XmlAttr<QString> serpRef;
    // void Shift(float x, float y) /*override*/;
    // void UnitsConvert(dist in_units, dist out_units) /*override*/;
};
// #endregion Figures
// #region Rules area
// Устанавливает область действия правила: все слои.
struct AllLayers {
    /* [XmlElement("AllLayers")] public string AllLayers_; */
    QString AllLayers;
};
// Устанавливает область действия правила: все компоненты.
struct AllComps {
    /* [XmlElement("AllComps")] public string AllComps_; */
    QString AllComps;
};
// Устанавливает область действия правила: все цепи.
struct AllNets {
    /* [XmlElement("AllNets")] public string AllNets_; */
    QString AllNets;
};
// Устанавливает область действия правила: все внутренние слои.
struct AllLayersInner {
    /* [XmlElement("AllLayersInner")] public string AllLayersInner_; */
    QString AllLayersInner;
};
// Устанавливает область действия правила: все внутренние сигнальные слои.
struct AllLayersInnerSignal {
    /* [XmlElement("AllLayersInnerSignal")] public string AllLayersInnerSignal_; */
    QString AllLayersInnerSignal;
};
// Устанавливает область действия правила: все сигнальные слои.
struct AllLayersSignal {
    /* [XmlElement("AllLayersSignal")] public string AllLayersSignal_; */
    QString AllLayersSignal;
};
// Устанавливает область действия правила: все внешние слои.
struct AllLayersOuter {
    /* [XmlElement("AllLayersOuter")] public string AllLayersOuter_; */
    QString AllLayersOuter;
};
// Устанавливает доступные типы переходных отверстий для правила: все типы.
struct AllViastacks {
    /* [XmlElement("AllViastacks")] public string AllViastacks_; */
    QString AllViastacks;
};
// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
struct AllViastacksThrough {
    /* [XmlElement("AllViastacksThrough")] public string AllViastacksThrough_; */
    QString AllViastacksThrough;
};
// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
struct AllViastacksNotThrough {
    /* [XmlElement("AllViastacksNotThrough")] public string AllViastacksNotThrough_; */
    QString AllViastacksNotThrough;
};
// #endregion Rules area
// #region Thermal Detail Text ObjectSignal
// Описание термобарьера.
struct Thermal {
    // Параметр термобарьера: число спиц.! В TopoR поддерживается только одно значение – 4.
    /* [XmlAttribute("spokeNum", DataType = "int")] public int spokeNum_; */
    XmlAttr<int> spokeNum; // int spokeNum_ = 0;
    // Параметр термобарьера: минимальное число спиц.
    /* [XmlAttribute("minSpokeNum", DataType = "int")] public int minSpokeNum_; */
    XmlAttr<int> minSpokeNum; // int minSpokeNum_ = 0;
    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
    XmlAttr<float> angle; // float angle_ = 0.0F;
    // Параметр термобарьера: ширина спицы.
    /* [XmlAttribute("spokeWidth", DataType = "float")] public float spokeWidth_; */
    XmlAttr<float> spokeWidth; // float spokeWidth_ = 0.0F;
    // Параметр термобарьера: зазор между контактной площадкой и областью металлизации.
    /* [XmlAttribute("backoff", DataType = "float")] public float backoff_; */
    XmlAttr<float> backoff; // float backoff_ = 0.0F;
    // void UnitsConvert(dist in_units, dist out_units);
};
// Описание детали.
struct Detail {
    // Толщина линии.
    /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
    XmlAttr<float> lineWidth; // float lineWidth_ = 0.0F;
    // Ссылка на слой.
    /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
    LayerRef layerRef;
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
        XmlElement("FilledContour", typeof(FilledContour))] public Object Figure_; */
    XmlVariant<ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon, Polyline, FilledContour> Figure_;
    // void Shift(float x, float y);
    // void UnitsConvert(dist in_units, dist out_units);
};
// Описание надписи.
struct Text {
    // Параметр надписи: текст надписи.
    /* [XmlAttribute("text")] public string text_; */
    XmlAttr<QString> text;
    // Параметр надписей (ярлыков): способ выравнивания текста.
    /* [XmlAttribute("align")] public align align_; */
    XmlAttr<align> align_{};
    // Задаёт угол в градусах c точностью до тысячных долей.
    /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
    XmlAttr<float> angle; // float angle_ = 0.0F;
    // Параметр надписей и ярлыков: зеркальность отображения.
    /* [XmlAttribute("mirror")] public Bool mirror_; */
    XmlAttr<Bool> mirror_{};
    /* public bool mirrorSpecified_ */
    // Ссылка на слой.
    /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
    LayerRef layerRef;
    // Ссылка на стиль надписей.
    /* [XmlElement("TextStyleRef")] public TextStyleRef TextStyleRef_; */
    TextStyleRef textStyleRef;
    // Точка привязки объекта.
    /* [XmlElement("Org")] public Org Org_; */
    Org org;
    // void Shift(float x, float y);
    // TODO: конвертировать текстовые стили по ссылке
    // <param name="in_units"></param>
    // <param name="out_units"></param>
    // void UnitsConvert(dist in_units, dist out_units);
};
// Сигналы воздействия правила
struct ObjectSignal {
    /* [XmlElement("SignalRef", typeof(SignalRef)),
        XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
        XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object Refs_; */
    XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef> Refs_;
};
// #endregion
// Различные сервисные функции
struct Ut final {
    // Конвертация единиц измерения
    /// \param value \brief значение
    /// \param in_units \brief текущие единицы измерения
    /// \param out_units \brief выходные единицы измерения
    // <returns>Возвращает сконвертированное значение</returns>
    static float UnitsConvert(float value, dist in_units, dist out_units);
};
} // namespace TopoR_PCB_Classes
