#pragma once

#include "../xmlserializertypes.h"
#include "Enums.h"
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
    XmlAttr<QString> name; // Имя объекта или ссылка на именованный объект.
};

// Ссылка на атрибут.
struct AttributeRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на тип слоя.
struct LayerTypeRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> type;
    operator QString() const { return type; }
};

// Ссылка на группу слоёв.
struct LayerGroupRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на слой.
/// \note !Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.
// struct LayerRef : BaseRef { };

struct LayerRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
    // Тип слоя или ссылка на именованный cлой
    /// \note В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено
    // TODO:
    // XmlAttribute("type", typeof(type_layer)),
};

// Ссылка на тип переходного отверстия.
struct ViastackRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на стек контактных площадок.
struct NetRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на группу компонентов.
struct CompGroupRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на компонент на плате.
struct CompInstanceRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на группу цепей.
struct NetGroupRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на волновое сопротивление.
struct ImpedanceRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на сигнал.
struct SignalRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на группу сигналов..
struct SignalGroupRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на дифференциальный сигнал.
struct DiffSignalRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на контакт.
struct PinRef {
    XmlAttr<QString> compName; // Имя компонента, используется для ссылки на компонент.
    XmlAttr<QString> pinName;  // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт источника сигнала.
struct SourcePinRef /*: PinRef*/ { // using PinRef::PinRef;
    XmlAttr<QString> compName;     // Имя компонента, используется для ссылки на компонент.
    XmlAttr<QString> pinName;      // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт приёмника сигнала.
struct ReceiverPinRef /*: PinRef*/ { // using PinRef::PinRef;
    XmlAttr<QString> compName;       // Имя компонента, используется для ссылки на компонент.
    XmlAttr<QString> pinName;        // Имя контакта компонента, используется для ссылки.
};

// Ссылка на стек контактных площадок.
struct PadstackRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на стиль надписей.
struct TextStyleRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на схемный компонент.
struct ComponentRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на посадочное место.
struct FootprintRef /*: BaseRef*/ { // using BaseRef::BaseRef;
    XmlAttr<QString> name;
    operator QString() const { return name; }
};

// Ссылка на вывод посадочного места.
struct PadRef {
    // Ссылка на имя компонента
    XmlAttr<QString> compName; // Имя компонента, используется для ссылки на компонент.
    XmlAttr<int> padNum;       // Номер контактной площадки (вывода) посадочного места.
};

} // namespace Reference_Types
using namespace Reference_Types;

namespace Coordinates {
struct base_coordinat {
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// координаты точки, вершины.
struct Dot /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Центр круга (окружности), овала.
struct Center /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Начальная точка линии, дуги.
struct Start /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Средняя точка дуги.
struct Middle /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Конечная точка линии, дуги.
struct End /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Точка привязки объекта.
struct Org /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Cмещение точки привязки или объекта по осям x и y.
struct Shift /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
};

// Вытягивание по осям x и y.
struct Stretch /*: base_coordinat*/ { // using base_coordinat::base_coordinat;
    XmlAttr<float> x, y;
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
    // [XmlElement("End")] public End end;
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
    // [XmlElement("Center")] public Center center;
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
    // [XmlElement("Center")] public Center center;
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
    XmlAttr<float> angle;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.
struct SegmentArcByMiddle /*: SegmentLine*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    End end;
    // Конечная точка линии, дуги.
    // [XmlElement("Middle")] public Middle middle;
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
    // [XmlElement("Center")] public Center center;
    Center center;
    // Начальная точка линии, дуги.
    // [XmlElement("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [XmlElement("End")] public End end;
    End end;
};

// Дуга, заданная центром. Обход по часовой стрелке.
struct ArcCW /*: ArcCCW*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using ArcCCW::ArcCCW;
    // Центр круга (окружности), овала.
    // [XmlElement("Center")] public Center center;
    Center center;
    // Начальная точка линии, дуги.
    // [XmlElement("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [XmlElement("End")] public End end;
    End end;
};

// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
struct ArcByAngle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Задаёт угол в градусах c точностью до тысячных долей.
    XmlAttr<float> angle;
    // Начальная точка линии, дуги.
    // [XmlElement("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [XmlElement("End")] public End end;
    End end;
};

// Дуга, заданная тремя точками: начало, середина и конец.
struct ArcByMiddle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Начальная точка линии, дуги.
    // [XmlElement("Start")] public Start start;
    Start start;
    // Конечная точка линии, дуги.
    // [XmlElement("Middle")] public Middle middle;
    Middle middle;
    // Конечная точка линии, дуги.
    // [XmlElement("End")] public End end;
    End end;
};

// Описание окружности (незалитого круга).
struct Circle /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Диаметр окружности, круга, овала.
    XmlAttr<float> diameter;
    // Центр круга (окружности), овала.
    // [XmlElement("Center")] public Center center;
    Center center;
};

// Описание линии.
struct Line /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Массив координат точек, вершин.
    // [XmlElement("Dot")] public List<Dot> Dots_;
    XmlArray<Dot> Dots;
};

// Описание полилинии.
struct Polyline /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Начальная точка линии, дуги.
    // [XmlElement("Start")] public Start start;
    Start start;
    // Сегменты.
    // [XmlElement(SegmentLine),XmlElement(SegmentArcByAngle),XmlElement(SegmentArcCCW),XmlElement(SegmentArcCW),XmlElement(SegmentArcByMiddle)] public List<Object> Segments_;
    XmlArray<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct Contour /*: Polyline*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Polyline::Polyline;
    Start start;
    XmlArray<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
struct Rect /*: Line*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Line::Line;
    XmlArray<Dot> Dots;
};

// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct FilledContour /*: Polyline*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Polyline::Polyline;
    Start start;
    XmlArray<XmlVariant<SegmentArcByAngle, SegmentArcByMiddle, SegmentArcCCW, SegmentArcCW, SegmentLine>> Segments;
};

// Описание круга.// TODO: требует уточнения
struct FilledCircle /*: Circle*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Circle::Circle;
    XmlAttr<float> diameter;
    Center center;
};

// Описание залитого прямоугольника.
struct FilledRect /*: Rect*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Rect::Rect;
    XmlArray<Dot> Dots;
};

// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
struct Polygon /*: Line*/ {
    [[deprecated("Следует использовать тег FilledContour")]] void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // using Line::Line;
    XmlArray<Dot> Dots;
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
    XmlAttr<QString> serpRef;
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
    XmlAttr<QString> serpRef;
};

// Описание прямолинейного сегмента проводника.
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackLine /*: IBaseFigure*/ {
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
    // Конечная точка линии, дуги.
    // [XmlElement("End")] public End end;
    End end;
    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    XmlAttr<QString> serpRef;
};

} // namespace Figures
using namespace Figures;

namespace Rules_Area {
// Устанавливает область действия правила: все слои.
struct AllLayers {
    // [XmlElement("AllLayers")] public string AllLayers_;
    // QString AllLayers;// FIXME maybe need
};

// Устанавливает область действия правила: все компоненты.
struct AllComps {
    // [XmlElement("AllComps")] public string AllComps_;
    // QString AllComps;
};

// Устанавливает область действия правила: все цепи.
struct AllNets {
    // [XmlElement("AllNets")] public string AllNets_;
    // QString AllNets;
};

// Устанавливает область действия правила: все внутренние слои.
struct AllLayersInner {
    // [XmlElement("AllLayersInner")] public string AllLayersInner_;
    // QString AllLayersInner;
};

// Устанавливает область действия правила: все внутренние сигнальные слои.
struct AllLayersInnerSignal {
    // [XmlElement("AllLayersInnerSignal")] public string AllLayersInnerSignal_;
    // QString AllLayersInnerSignal;
};

// Устанавливает область действия правила: все сигнальные слои.
struct AllLayersSignal {
    // [XmlElement("AllLayersSignal")] public string AllLayersSignal_;
    // QString AllLayersSignal;
};

// Устанавливает область действия правила: все внешние слои.
struct AllLayersOuter {
    // [XmlElement("AllLayersOuter")] public string AllLayersOuter_;
    // QString AllLayersOuter;
};

// Устанавливает доступные типы переходных отверстий для правила: все типы.
struct AllViastacks {
    // [XmlElement("AllViastacks")] public string AllViastacks_;
    // QString AllViastacks;
};

// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
struct AllViastacksThrough {
    // [XmlElement("AllViastacksThrough")] public string AllViastacksThrough_;
    // QString AllViastacksThrough;
};

// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
struct AllViastacksNotThrough {
    // [XmlElement("AllViastacksNotThrough")] public string AllViastacksNotThrough_;
    // QString AllViastacksNotThrough;
};

} // namespace Rules_Area
using namespace Rules_Area;

namespace Thermal_Detail_Text_ObjectSignal {
// Описание термобарьера.
struct Thermal { // Параметры термобарьера:
    // Число спиц.! В TopoR поддерживается только одно значение – 4.
    XmlAttr<int> spokeNum{4};
    // Минимальное число спиц.
    XmlAttr<int> minSpokeNum;
    // Задаёт угол в градусах c точностью до тысячных долей.
    XmlAttr<float> angle;
    // Ширина спицы.
    XmlAttr<float> spokeWidth;
    // Зазор между контактной площадкой и областью металлизации.
    XmlAttr<float> backoff;
};

// Описание детали.
struct Detail {
    XmlAttr<float> lineWidth; // Толщина линии.
    LayerRef layerRef;        // Ссылка на слой.
    XmlVariant<               // Описание фигуры.
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

// Описание надписи.
struct Text {
    // Параметр надписи: текст надписи.
    XmlAttr<QString> text;
    // Параметр надписей (ярлыков): способ выравнивания текста.
    XmlAttr<align> align_;

    // Задаёт угол в градусах c точностью до тысячных долей.
    XmlAttr<float> angle;
    // Параметр надписей и ярлыков: зеркальность отображения.
    XmlAttr<Bool> mirror;

    /* public bool mirrorSpecified_ */
    // Ссылка на слой.
    // [XmlElement("LayerRef")] public LayerRef LayerRef_;
    LayerRef layerRef;
    // Ссылка на стиль надписей.
    // [XmlElement("TextStyleRef")] public TextStyleRef TextStyleRef_;
    TextStyleRef textStyleRef;
    // Точка привязки объекта.
    // [XmlElement("Org")] public Org Org_;
    Org org;
    // TODO: конвертировать текстовые стили по ссылке
    // <param name="in_units"></param>
    // <param name="out_units"></param>
};

// Сигналы воздействия правила
struct ObjectSignal {
    XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef> ObjectSignal /* NOTE Refs_*/; // FIXME ???
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
    static float UnitsConvert(dist inUnits, dist outUnits);
};

} // namespace TopoR
using namespace TopoR;
