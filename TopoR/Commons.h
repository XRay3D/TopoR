#pragma once

#include "Enums.h"
#include "xmlserializertypes.h"
#include <QPainterPath>
#include <QPoint>
#include <QTransform>

class QGraphicsItem;
class QPainterPath;
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

#define COMPONENTSONBOARD 1
#define CONNECTIVITY      1
#define CONSTRUCTIVE      1
#define DIALOGSETTINGS    1
#define DISPLAYCONTROL    1
#define GROUPS            1
#define HEADER            1
#define HISPEEDRULES      1
#define LAYERS            1
#define LOCALLIBRARY      1
#define NETLIST           1
#define RULES             1
#define SETTINGS          1
#define TEXTSTYLES        1

namespace TopoR {

namespace Reference_Types {
// базовый класс ссылок.
struct BaseRef {
    Xml::Attr<QString> name; // Имя объекта или ссылка на именованный объект.
};

// Ссылка на атрибут.
struct AttributeRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на тип слоя.
struct LayerTypeRef {
    Xml::Attr<QString> type; // BaseRef with attribute name
    operator QString() const { return type; }
};

// Ссылка на группу слоёв.
struct LayerGroupRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на слой.
/// \note !Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.
// struct LayerRef : BaseRef { };

struct LayerRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
    // Тип слоя или ссылка на именованный cлой
    /// \note В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено
    // TODO:
    // Xml::Attribute("type", typeof(type_layer)),
};

// Ссылка на тип переходного отверстия.
struct ViastackRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на стек контактных площадок.
struct NetRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на группу компонентов.
struct CompGroupRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на компонент на плате.
struct CompInstanceRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на группу цепей.
struct NetGroupRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на волновое сопротивление.
struct ImpedanceRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на сигнал.
struct SignalRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на группу сигналов..
struct SignalGroupRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на дифференциальный сигнал.
struct DiffSignalRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на контакт.
struct PinRef {
    Xml::Attr<QString> compName; // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;  // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт источника сигнала.
struct SourcePinRef /*: PinRef*/ { // using PinRef::PinRef;
    Xml::Attr<QString> compName;     // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;      // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт приёмника сигнала.
struct ReceiverPinRef /*: PinRef*/ { // using PinRef::PinRef;
    Xml::Attr<QString> compName;       // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;        // Имя контакта компонента, используется для ссылки.
};

// Ссылка на стек контактных площадок.
struct PadstackRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на стиль надписей.
struct TextStyleRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на схемный компонент.
struct ComponentRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на посадочное место.
struct FootprintRef {
    Xml::Attr<QString> name; // BaseRef with attribute name
    operator QString() const { return name; }
};

// Ссылка на вывод посадочного места.
struct PadRef {
    // Ссылка на имя компонента
    Xml::Attr<QString> compName; // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<int> padNum;       // Номер контактной площадки (вывода) посадочного места.
};

} // namespace Reference_Types
using namespace Reference_Types;

namespace Coordinates {
struct base_coordinat {
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// координаты точки, вершины.
struct Dot /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Центр круга (окружности), овала.
struct Center /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Начальная точка линии, дуги.
struct Start /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Средняя точка дуги.
struct Middle /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Конечная точка линии, дуги.
struct End /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Точка привязки объекта.
struct Org /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Cмещение точки привязки или объекта по осям x и y.
struct Shift /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Вытягивание по осям x и y.
struct Stretch /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

} // namespace Coordinates
using namespace Coordinates;

namespace Segments {
// struct IBaseSegment {
// };

// Описание прямолинейного сегмента контура.
struct SegmentLine /*: IBaseSegment*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход против часовой стрелки.
struct SegmentArcCCW /*: SegmentLine*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    End end;
    // Центр круга (окружности), овала.
    // [Xml::Element("Center")] public Center center;
    Center center;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход по часовой стрелки.
struct SegmentArcCW /*: SegmentArcCCW*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using SegmentArcCCW::SegmentArcCCW;
    End end;
    // Центр круга (окружности), овала.
    // [Xml::Element("Center")] public Center center;
    Center center;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.
struct SegmentArcByAngle /*: SegmentLine*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    End end;
    // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<double> angle;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.
struct SegmentArcByMiddle /*: SegmentLine*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    End end;
    // Конечная точка линии, дуги.
    // [Xml::Element("Middle")] public Middle middle;
    Middle middle;
};

} // namespace Segments
using namespace Segments;

namespace Figures {
// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов
struct IBaseFigure {
};

// Дуга, заданная центром. Обход против часовой стрелки.
struct ArcCCW /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Центр круга (окружности), овала.
    // [Xml::Element("Center")] public Center center;
    Center center;
    // Начальная точка линии, дуги.
    // [Xml::Element("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
};

// Дуга, заданная центром. Обход по часовой стрелке.
struct ArcCW /*: ArcCCW*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using ArcCCW::ArcCCW;
    // Центр круга (окружности), овала.
    // [Xml::Element("Center")] public Center center;
    Center center;
    // Начальная точка линии, дуги.
    // [Xml::Element("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
};

// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
struct ArcByAngle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<double> angle;
    // Начальная точка линии, дуги.
    // [Xml::Element("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
};

// Дуга, заданная тремя точками: начало, середина и конец.
struct ArcByMiddle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Начальная точка линии, дуги.
    // [Xml::Element("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [Xml::Element("Middle")] public Middle middle;
    Middle middle;
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
};

// Описание окружности (незалитого круга).
struct Circle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Диаметр окружности, круга, овала.
    Xml::Attr<double> diameter;
    // Центр круга (окружности), овала.
    // [Xml::Element("Center")] public Center center;
    Center center;
};

// Описание линии.
struct Line /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Массив координат точек, вершин.
    // [Xml::Element("Dot")] public List<Dot> Dots_;
    Xml::Array<Dot> Dots;
};

// Описание полилинии.
struct Polyline /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Начальная точка линии, дуги.
    // [Xml::Element("Start")] public Start start;
    Start start;
    // Сегменты.
    // [Xml::Element(SegmentLine),Xml::Element(SegmentArcByAngle),Xml::Element(SegmentArcCCW),Xml::Element(SegmentArcCW),Xml::Element(SegmentArcByMiddle)] public List<Object> Segments_;
    Xml::Array<Xml::Variant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct Contour /*: Polyline*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Polyline::Polyline;
    Start start;
    Xml::Array<Xml::Variant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
struct Rect /*: Line*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Line::Line;
    Xml::Array<Dot> Dots;
};

// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct FilledContour /*: Polyline*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Polyline::Polyline;
    Start start;
    Xml::Array<Xml::Variant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание круга.// TODO: требует уточнения
struct FilledCircle /*: Circle*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Circle::Circle;
    Xml::Attr<double> diameter;
    Center center;
};

// Описание залитого прямоугольника.
struct FilledRect /*: Rect*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Rect::Rect;
    Xml::Array<Dot> Dots;
};

// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
struct Polygon /*: Line*/ {
    [[deprecated("Следует использовать тег FilledContour")]] void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Line::Line;
    Xml::Array<Dot> Dots;
};

// Описание дугообразного сегмента проводника (дуга по часовой стрелке).
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackArcCW /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Центр круга (окружности), овала.
    Center center;
    // Конечная точка линии, дуги.
    End end;
    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    Xml::Attr<QString> serpRef;
};

// Описание дугообразного сегмента проводника (дуга против часовой стрелки).
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackArc /*: TrackArcCW*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using TrackArcCW::TrackArcCW;
    Center center;
    End end;
    Xml::Attr<QString> serpRef;
};

// Описание прямолинейного сегмента проводника.
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackLine /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Конечная точка линии, дуги.
    // [Xml::Element("End")] public End end;
    End end;
    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    Xml::Attr<QString> serpRef;
};

} // namespace Figures
using namespace Figures;

namespace Rules_Area {

// Устанавливает область действия правила: все слои.
struct AllLayers { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все компоненты.
struct AllComps { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все цепи.
struct AllNets { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все внутренние слои.
struct AllLayersInner { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все внутренние сигнальные слои.
struct AllLayersInnerSignal { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все сигнальные слои.
struct AllLayersSignal { }; // Xml::Element empty tag always

// Устанавливает область действия правила: все внешние слои.
struct AllLayersOuter { }; // Xml::Element empty tag always

// Устанавливает доступные типы переходных отверстий для правила: все типы.
struct AllViastacks { }; // Xml::Element empty tag always

// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
struct AllViastacksThrough { }; // Xml::Element empty tag always

// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
struct AllViastacksNotThrough { }; // Xml::Element empty tag always

} // namespace Rules_Area
using namespace Rules_Area;

namespace Thermal_Detail_Text_ObjectSignal {
// Описание термобарьера.
struct Thermal {                // Параметры термобарьера:
    Xml::Attr<int> spokeNum{4};   // Число спиц.! В TopoR поддерживается только одно значение – 4.
    Xml::Attr<int> minSpokeNum;   // Минимальное число спиц.
    Xml::Attr<double> angle;      // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<double> spokeWidth; // Ширина спицы.
    Xml::Attr<double> backoff;    // Зазор между контактной площадкой и областью металлизации.
};

// Описание детали.
struct Detail {
    Xml::Attr<double> lineWidth; // Толщина линии.
    LayerRef layerRef;         // Ссылка на слой.
    Xml::Variant<                // Описание фигуры.
        ArcByAngle,
        ArcByMiddle,
        ArcCCW,
        ArcCW,
        Circle,
        FilledCircle,
        FilledContour,
        FilledRect,
        Line,
        Polygon,
        Polyline,
        Rect>
        Figure;
};

struct Text {                  // Описание надписи.
    Xml::Attr<QString> text;     // Параметр надписи: текст надписи.
    Xml::Attr<align> align_;     // Параметр надписей (ярлыков): способ выравнивания текста.
    Xml::Attr<double> angle;     // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<Bool> mirror;      // Параметр надписей и ярлыков: зеркальность отображения.
    LayerRef layerRef;         // Ссылка на слой.
    TextStyleRef textStyleRef; // Ссылка на стиль надписей.
    Org org;                   // Точка привязки объекта.
    // TODO: конвертировать текстовые стили по ссылке
    // <param name="in_units"></param>
    // <param name="out_units"></param>
};

// Сигналы воздействия правила
struct ObjectSignal {
    Xml::Variant<SignalRef, DiffSignalRef, SignalGroupRef> objectSignal /* NOTE Refs_*/; // FIXME ???
};

} // namespace Thermal_Detail_Text_ObjectSignal
using namespace Thermal_Detail_Text_ObjectSignal;
// #endregion
// Различные сервисные функции
struct Ut final {
    // Конвертация единиц измерения
    /// \param value \brief значение
    /// \param inUnits \brief текущие единицы измерения
    /// \param outUnits \brief выходные единицы измерения
    /// \return  Возвращает сконвертированное значение
    static double UnitsConvert(dist inUnits, dist outUnits);
};

} // namespace TopoR
using namespace TopoR;
