#pragma once

#include "Enums.h"
#include "xmlserializertypes.h"
#include <QPainterPath>

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
    operator QString() const { return name; }
};

#define REF(NAME)                                 \
    struct NAME {                                 \
        Xml::Attr<QString> name;                  \
        operator QString() const { return name; } \
    };

REF(AttributeRef)    // Ссылка на атрибут.
REF(LayerTypeRef)    // Ссылка на тип слоя.
REF(LayerGroupRef)   // Ссылка на группу слоёв.
REF(LayerRef)        // Ссылка на слой.
                     /// \note !Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.
                     // struct LayerRef : BaseRef { };
                     // Тип слоя или ссылка на именованный cлой
                     /// \note В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено
                     // TODO:
                     // Xml::Attribute("type", typeof(type_layer)),
REF(ViastackRef)     // Ссылка на тип переходного отверстия.
REF(NetRef)          // Ссылка на стек контактных площадок.
REF(CompGroupRef)    // Ссылка на группу компонентов.
REF(CompInstanceRef) // Ссылка на компонент на плате.
REF(NetGroupRef)     // Ссылка на группу цепей.
REF(ImpedanceRef)    // Ссылка на волновое сопротивление.
REF(SignalRef)       // Ссылка на сигнал.
REF(SignalGroupRef)  // Ссылка на группу сигналов..
REF(DiffSignalRef)   // Ссылка на дифференциальный сигнал.
REF(PadstackRef)     // Ссылка на стек контактных площадок.
REF(TextStyleRef)    // Ссылка на стиль надписей.
REF(ComponentRef)    // Ссылка на схемный компонент.
REF(FootprintRef)    // Ссылка на посадочное место.

// Ссылка на контакт.
struct PinRef {
    Xml::Attr<QString> compName; // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;  // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт источника сигнала.
struct SourcePinRef /*: PinRef */ { // using PinRef::PinRef;
    Xml::Attr<QString> compName;    // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;     // Имя контакта компонента, используется для ссылки.
};

// Ссылка на контакт приёмника сигнала.
struct ReceiverPinRef /*: PinRef */ { // using PinRef::PinRef;
    Xml::Attr<QString> compName;      // Имя компонента, используется для ссылки на компонент.
    Xml::Attr<QString> pinName;       // Имя контакта компонента, используется для ссылки.
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

struct BaseCoordinat {
    BaseCoordinat(double x, double y)
        : x{x}, y{y} { }

    Xml::Attr<double, NoOpt> x, y;
    operator QPointF() const { return {x, y}; }
    QPointF toPoint() const { return *this; }
    template <int I> friend auto get(const BaseCoordinat&);

    // template <size_t I>
    // auto& get() & {
    //     if constexpr(I == 0) return x;
    //     if constexpr(I == 1) return y;
    // }
    // template <size_t I>
    // auto const& get() const& {
    //     if constexpr(I == 0) return x;
    //     if constexpr(I == 1) return y;
    // }
    // template <size_t I>
    // auto&& get() && {
    //     if constexpr(I == 0) return std::move(x);
    //     if constexpr(I == 1) return std::move(y);
    // }
};

// using Dot = Xml::Named<BaseCoordinat, "Dot">;         // координаты точки, вершины.
// using Center = Xml::Named<BaseCoordinat, "Center">;   // Центр круга (окружности), овала.
// using Start = Xml::Named<BaseCoordinat, "Start">;     // Начальная точка линии, дуги.
// using Middle = Xml::Named<BaseCoordinat, "Middle">;   // Средняя точка дуги.
// using End = Xml::Named<BaseCoordinat, "End">;         // Конечная точка линии, дуги.
// using Org = Xml::Named<BaseCoordinat, "Org">;         // Точка привязки объекта.
// using Shift = Xml::Named<BaseCoordinat, "Shift">;     // Cмещение точки привязки или объекта по осям x и y.
// using Stretch = Xml::Named<BaseCoordinat, "Stretch">; // Вытягивание по осям x и y.

#define COORDINAT(NAME)                             \
    struct NAME {                                   \
        Xml::Attr<double, NoOpt> x, y;              \
        operator QPointF() const { return {x, y}; } \
        QPointF toPoint() const { return *this; }   \
    };

COORDINAT(Center)  // Центр круга (окружности), овала.
COORDINAT(Dot)     // координаты точки, вершины.
COORDINAT(End)     // Конечная точка линии, дуги.
COORDINAT(Middle)  // Средняя точка дуги.
COORDINAT(Org)     // Точка привязки объекта.
COORDINAT(Shift)   // Cмещение точки привязки или объекта по осям x и y.
COORDINAT(Start)   // Начальная точка линии, дуги.
COORDINAT(Stretch) // Вытягивание по осям x и y.

} // namespace Coordinates
using namespace Coordinates;

namespace Segments {
// Интерфейс IBaseSegment создан для реализации удобного доступа к одинаковым методам разных объектов
struct IBaseFigure { };
// Описание прямолинейного сегмента контура.
struct SegmentLine /*: IBaseSegment */ {
    End end; // Конечная точка линии, дуги.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход против часовой стрелки.
struct SegmentArcCCW /*: SegmentLine */ {
    End end;       // SegmentLine
    Center center; // Центр круга (окружности), овала.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход по часовой стрелки.
struct SegmentArcCW /*: SegmentArcCCW */ {
    End end;       // SegmentLine
    Center center; // Центр круга (окружности), овала. SegmentArcCCW
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.
struct SegmentArcByAngle /*: SegmentLine */ {
    End end;                 // SegmentLine
    Xml::Attr<double> angle; // Задаёт угол в градусах c точностью до тысячных долей.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.
struct SegmentArcByMiddle /*: SegmentLine */ {
    End end;       // SegmentLine
    Middle middle; // Конечная точка линии, дуги.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

} // namespace Segments
using namespace Segments;

namespace Figures {

// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов
struct IBaseFigure { };

// Дуга, заданная центром. Обход против часовой стрелки.
struct ArcCCW /*: IBaseFigure */ {
    Center center; // Центр круга (окружности), овала.
    Start start;   // Начальная точка линии, дуги.
    End end;       // Конечная точка линии, дуги.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Дуга, заданная центром. Обход по часовой стрелке.
struct ArcCW /*: ArcCCW */ {
    Center center; // Центр круга (окружности), овала. ArcCCW
    Start start;   // Начальная точка линии, дуги. ArcCCW
    End end;       // Конечная точка линии, дуги. ArcCCW
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
struct ArcByAngle /*: IBaseFigure */ {
    Xml::Attr<double> angle; // Задаёт угол в градусах c точностью до тысячных долей.
    Start start;             // Начальная точка линии, дуги.
    End end;                 // Конечная точка линии, дуги.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Дуга, заданная тремя точками: начало, середина и конец.
struct ArcByMiddle /*: IBaseFigure */ {
    Start start;   // Начальная точка линии, дуги.
    Middle middle; // Конечная точка линии, дуги.
    End end;       // Конечная точка линии, дуги.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание окружности (незалитого круга).
struct Circle /*: IBaseFigure */ {
    Xml::Attr<double> diameter; // Диаметр окружности, круга, овала.
    Center center;              // Центр круга (окружности), овала.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание линии.
struct Line /*: IBaseFigure */ {
    Xml::Array<Dot> Dots; // Массив координат точек, вершин.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание полилинии.
struct Polyline /*: IBaseFigure */ {
    Start start; // Начальная точка линии, дуги.
    Xml::Array<Xml::Variant<
        SegmentArcByAngle,
        SegmentArcByMiddle,
        SegmentArcCCW,
        SegmentArcCW,
        SegmentLine>>
        Segments; // Сегменты.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct Contour /*: Polyline */ {
    Start start;
    Xml::Array<Xml::Variant<
        SegmentArcByAngle,
        SegmentArcByMiddle,
        SegmentArcCCW,
        SegmentArcCW,
        SegmentLine>>
        Segments;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
struct Rect /*: Line */ {
    Xml::Array<Dot> Dots;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
struct FilledContour /*: Polyline */ {
    Start start;
    Xml::Array<Xml::Variant<
        SegmentArcByAngle,
        SegmentArcByMiddle,
        SegmentArcCCW,
        SegmentArcCW,
        SegmentLine>>
        Segments;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание круга.// TODO: требует уточнения
struct FilledCircle /*: Circle */ {
    Xml::Attr<double> diameter;
    Center center;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание залитого прямоугольника.
struct FilledRect /*: Rect */ {
    Xml::Array<Dot> Dots;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
struct Polygon /*: Line */ {
    Xml::Array<Dot> Dots;
    [[deprecated("Следует использовать тег FilledContour")]] void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента проводника (дуга по часовой стрелке).
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackArcCW /*: IBaseFigure */ {
    Center center;              // Центр круга (окружности), овала.
    End end;                    // Конечная точка линии, дуги.
    Xml::Attr<QString> serpRef; // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание дугообразного сегмента проводника (дуга против часовой стрелки).
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackArc {
    Center center; // TrackArcCW
    End end;       // TrackArcCW
    Xml::Attr<QString> serpRef;
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

// Описание прямолинейного сегмента проводника.
/// \note Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.
struct TrackLine /*: IBaseFigure */ {
    End end;                    // Конечная точка линии, дуги.
    Xml::Attr<QString> serpRef; // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    void drawTo(QPainterPath& path) const;
    QPainterPath toPPath() const;
    operator QPainterPath() const { return toPPath(); }
};

} // namespace Figures
using namespace Figures;

namespace Rules_Area {             // Xml::Element empty tag always
struct AllLayers { };              // Устанавливает область действия правила: все слои.
struct AllComps { };               // Устанавливает область действия правила: все компоненты.
struct AllNets { };                // Устанавливает область действия правила: все цепи.
struct AllLayersInner { };         // Устанавливает область действия правила: все внутренние слои.
struct AllLayersInnerSignal { };   // Устанавливает область действия правила: все внутренние сигнальные слои.
struct AllLayersSignal { };        // Устанавливает область действия правила: все сигнальные слои.
struct AllLayersOuter { };         // Устанавливает область действия правила: все внешние слои.
struct AllViastacks { };           // Устанавливает доступные типы переходных отверстий для правила: все типы.
struct AllViastacksThrough { };    // Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
struct AllViastacksNotThrough { }; // Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
} // namespace Rules_Area
using namespace Rules_Area;

namespace Thermal_Detail_Text_ObjectSignal {
// Описание термобарьера.
struct Thermal {                  // Параметры термобарьера:
    Xml::Attr<int> spokeNum{4};   // Число спиц.! В TopoR поддерживается только одно значение – 4.
    Xml::Attr<int> minSpokeNum;   // Минимальное число спиц.
    Xml::Attr<double> angle;      // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<double> spokeWidth; // Ширина спицы.
    Xml::Attr<double> backoff;    // Зазор между контактной площадкой и областью металлизации.
};

// Описание детали.
struct Detail {
    Xml::Attr<double> lineWidth; // Толщина линии.
    LayerRef layerRef;           // Ссылка на слой.
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
    Xml::Attr<QString> text;   // Параметр надписи: текст надписи.
    Xml::Attr<align> align_;   // Параметр надписей (ярлыков): способ выравнивания текста.
    Xml::Attr<double> angle;   // Задаёт угол в градусах c точностью до тысячных долей.
    Xml::Attr<Bool> mirror;    // Параметр надписей и ярлыков: зеркальность отображения.
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

template <int I>
auto& get(const BaseCoordinat& c) {
    if constexpr(I == 0) return c.x;
    if constexpr(I == 1) return c.y;
}

namespace std {

template <> struct tuple_size<BaseCoordinat> : integral_constant<size_t, 2> { };
template <> struct tuple_element<0, BaseCoordinat> {
    using type = double;
};
template <> struct tuple_element<1, BaseCoordinat> {
    using type = double;
};

} // namespace std
