#pragma once

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace TopoR_PCB_Classes {
class Shift;
}

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

//	#region Enumerations //Все enum в алфавитном порядке

// Параметр надписей (ярлыков): способ выравнивания текста. Значение по умолчанию – CM.

enum class align {

    // по центру

    // [XmlEnum("CM")] CM,
    CM,

    // по левому верхнему углу

    // [XmlEnum("LT")] LT,
    LT,

    // по верхнему краю

    // [XmlEnum("CT")] CT,
    CT,

    // по правому верхнему углу

    // [XmlEnum("RT")] RT,
    RT,

    // по левому краю

    // [XmlEnum("LM")] LM,
    LM,

    // по правому краю

    // [XmlEnum("RM")] RM,
    RM,

    // по левому нижнему углу

    // [XmlEnum("LB")] LB,
    LB,

    // по нижнему краю

    // [XmlEnum("CB")] CB,
    CB,

    // по правому нижнему углу

    // [XmlEnum("RB")] RB
    RB
};

// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.

enum class autoEqu {

    // не использовать функциональную эквивалентность

    // [XmlEnum("None")] None,
    None,

    // переназначать выводы компонента

    // [XmlEnum("Pins")] Pins,
    Pins,

    // переназначать вентили компонентов (не поддерживается)

    // [XmlEnum("Gates")] Gates,
    Gates,

    // разрешить все переназначения (не поддерживается)

    // [XmlEnum("Full")] Full
    Full
};

// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.

enum class automove {

    // двигаются только переходы

    // [XmlEnum("MoveVias")] MoveVias,
    MoveVias,

    // двигаются только переходы; в процессе движения выполняется перекладка проводников

    // [XmlEnum("MoveViasWithRefine")] MoveViasWithRefine,
    MoveViasWithRefine,

    // двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников

    // [XmlEnum("MoveCompsWithRefine")] MoveCompsWithRefine
    MoveCompsWithRefine
};

// Флаг, значение по умолчанию – off.

enum class Bool {

    // [XmlEnum("off")] off,
    off,

    // [XmlEnum("on")] on
    on
};

// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.

enum class connectPad {

    // прямое подключение

    // [XmlEnum("Direct")] Direct,
    Direct,

    // подключение с помощью термобарьера

    // [XmlEnum("Thermal")] Thermal
    Thermal
};

// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.

enum class connectVia {

    // прямое подключение

    // [XmlEnum("Direct")] Direct,
    Direct,

    // подключение с помощью термобарьера

    // [XmlEnum("Thermal")] Thermal
    Thermal
};

// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).

enum class dist {

    // миллиметр

    // [XmlEnum("mm")] mm,
    mm,

    // микрометр

    // [XmlEnum("mkm")] mkm,
    mkm,

    // сантиметр

    // [XmlEnum("cm")] cm,
    cm,

    // дециметр

    // [XmlEnum("dm")] dm,
    dm,

    // метр

    // [XmlEnum("m")] m,
    m,

    // мил(тысячная дюйма)

    // [XmlEnum("mil")] mil,
    mil,

    // дюйм

    // [XmlEnum("inch")] inch
    inch
};

// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.

enum class fillType {

    // сплошная заливка

    // [XmlEnum("Solid")] Solid,
    Solid,

    // штриховка сеткой

    // [XmlEnum("Hatched")] Hatched,
    Hatched,

    // диагональная штриховка сеткой

    // [XmlEnum("CRHatched")] CRHatched
    CRHatched
};

// Настройка отображения сетки: тип сетки.

enum class gridKind {

    // [XmlEnum("Dots")] Dots,
    Dots,

    // [XmlEnum("Lines")] Lines
    Lines
};

// Тип слоя. Значение по умолчанию – Signal.

enum class layer_type {

    // сигнальный слой

    // [XmlEnum("Signal")] Signal,
    Signal,

    // сборочный слой (слой очертаний компонентов)

    // [XmlEnum("Assy")] Assy,
    Assy,

    // слой паяльной пасты

    // [XmlEnum("Paste")] Paste,
    Paste,

    // слой шелкографии

    // [XmlEnum("Silk")] Silk,
    Silk,

    // слой маски

    // [XmlEnum("Mask")] Mask,
    Mask,

    // опорный слой

    // [XmlEnum("Plane")] Plane,
    Plane,

    // механический слой

    // [XmlEnum("Mechanical")] Mechanical,
    Mechanical,

    // документирующий слой

    // [XmlEnum("Doc")] Doc,
    Doc,

    // диэлектрический слой

    // [XmlEnum("Dielectric")] Dielectric
    Dielectric
};

// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.

enum class mode_Autoroute {

    // многослойная трассировка

    // [XmlEnum("Multilayer")] Multilayer,
    Multilayer,

    // однослойная трассировка на верхнем слое

    // [XmlEnum("SinglelayerTop")] SinglelayerTop,
    SinglelayerTop,

    // однослойная трассировка на нижнем слое

    // [XmlEnum("SinglelayerBottom")] SinglelayerBottom
    SinglelayerBottom
};

// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.

enum class mode_PadConnectSettings {

    // возможность подключения к углам КП определяется автоматически.

    // [XmlEnum("AutoConnect")] AutoConnect,
    AutoConnect,

    // разрешено подключаться к углам всех КП

    // [XmlEnum("AllPads")] AllPads
    AllPads
};

// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.

enum class precision {

    // средняя точность

    // [XmlEnum("Med")] Med,
    Med,

    // низкая точность

    // [XmlEnum("Low")] Low,
    Low,

    // высокая точность

    // [XmlEnum("High")] High
    High
};

// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.

enum class preference {

    // метрические (конкретные единицы выбираются в зависимости от параметра)

    // [XmlEnum("Metric")] Metric,
    Metric,

    // микрометр

    // [XmlEnum("mkm")] mkm,
    mkm,

    // миллиметр

    // [XmlEnum("mm")] mm,
    mm,

    // сантиметр

    // [XmlEnum("cm")] cm,
    cm,

    // дециметр

    // [XmlEnum("dm")] dm,
    dm,

    // метр

    // [XmlEnum("m")] m,
    m,

    // английские (конкретные единицы выбираются в зависимости от параметра)

    // [XmlEnum("Imperial")] Imperial,
    Imperial,

    // мил(тысячная дюйма)

    // [XmlEnum("mil")] mil,
    mil,

    // дюйм

    // [XmlEnum("inch")] inch
    inch
};

// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.

enum class refine {

    // разрешён перенос проводников на другой слой.

    // [XmlEnum("ChangeLayer")] ChangeLayer,
    ChangeLayer,

    // без переноса проводников на другой слой.

    // [XmlEnum("NoChangeLayer")] NoChangeLayer
    NoChangeLayer
};

// Тип запрета трассировки. Значение по умолчанию – Wires

enum class role {

    // запрет проводников

    // [XmlEnum("Wires")] Wires,
    Wires,

    // запрет переходных отверстий

    // [XmlEnum("Vias")] Vias,
    Vias,

    // запрет проводников и переходных отверстий

    // [XmlEnum("Wires and Vias")] WiresАndVias
    WiresАndVias
};

// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.

enum class showWarnings {

    // показывать только отмеченные предупреждения

    // [XmlEnum("ShowChecked")] ShowChecked,
    ShowChecked,

    // показывать все предупреждения

    // [XmlEnum("ShowAll")] ShowAll,
    ShowAll,

    // ничего не показывать

    // [XmlEnum("ShowNothing")] ShowNothing
    ShowNothing
};

// Сторона объекта.

// <remarks>! Значение Both возможно только при описании запретов размещения.</remarks>
enum class side {

    // верх

    // [XmlEnum("Top")] Top,
    Top,

    // низ

    // [XmlEnum("Bottom")] Bottom,
    Bottom,

    // обе стороны

    // [XmlEnum("Both")] Both
    Both
};

// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.

enum class state {

    // незалитая

    // [XmlEnum("Unpoured")] Unpoured,
    Unpoured,

    // залитая

    // [XmlEnum("Poured")] Poured,
    Poured,

    // залитая и зафиксированная

    // [XmlEnum("Locked")] Locked
    Locked
};

// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).

enum class time {

    // пикосекунда

    // [XmlEnum("ps")] ps,
    ps,

    // фемтосекунда

    // [XmlEnum("fs")] fs,
    fs,

    // наносекунда

    // [XmlEnum("ns")] ns,
    ns,

    // микросекунда

    // [XmlEnum("us")] us
    us
};

// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes

enum class type {

    // позиционное обозначение

    // [XmlEnum("RefDes")] RefDes,
    RefDes,

    // PartName

    // [XmlEnum("PartName")] PartName
    PartName
};

// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.

enum class type_connectToCopper {

    // тип подключения не задан(используются настройки полигона)

    // [XmlEnum("NoneConnect")] NoneConnect,
    NoneConnect,

    // прямое подключение

    // [XmlEnum("Direct")] Direct,
    Direct,

    // подключение с помощью термобарьера

    // [XmlEnum("Thermal")] Thermal
    Thermal
};

// Тип обработки углов прямоугольной контактной площадки.

enum class type_handling {

    // без обработки

    // [XmlEnum("None")] None,
    None,

    // скругление

    // [XmlEnum("Rounding")] Rounding,
    Rounding,

    // срез

    // [XmlEnum("Chamfer")] Chamfer
    Chamfer
};

// Тип стека контактных площадок. Значение по умолчанию – Through.

enum class type_padstack {

    // сквозной

    // [XmlEnum("Through")] Through,
    Through,

    // планарный

    // [XmlEnum("SMD")] SMD,
    SMD,

    // монтажное отверстие

    // [XmlEnum("MountHole")] MountHole
    MountHole
};

// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.

enum class units {

    // миллиметр

    // [XmlEnum("mm")] mm,
    mm,

    // мил (тысячная дюйма)

    // [XmlEnum("mil")] mil
    mil
};

// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist

enum class valueType {

    // длина

    // [XmlEnum("Dist")] Dist,
    Dist,

    // время

    // [XmlEnum("Time")] Time
    Time
};

// Параметр автоматической трассировки: форма проводников.

enum class wireShape {

    // Polyline

    // [XmlEnum("Polyline")] Polyline,
    Polyline,

    // Arcs

    // [XmlEnum("Arcs")] Arcs
    Arcs
};

//	#endregion Enumerations

//	#region Reference Types

// базовый класс ссылок.

class BaseRef {

    // Имя объекта или ссылка на именованный объект.

public:
    // [XmlAttribute("name")] public string _ReferenceName;
    std::string _ReferenceName;
};

// Ссылка на атрибут.

class AttributeRef : public BaseRef {
};

// Ссылка на тип слоя.

class LayerTypeRef {

    // Тип слоя.

public:
    // [XmlAttribute("type")] public layer_type _type;
    layer_type _type{};
};

// Ссылка на группу слоёв.

class LayerGroupRef : public BaseRef {
};

// Ссылка на слой.

// <remarks>! Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.</remarks>
class LayerRef : public BaseRef {

    // Тип слоя или ссылка на именованный cлой

    // <remarks>В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено</remarks>
    // TODO:
    //   XmlAttribute("type", typeof(type_layer)),
};

// Ссылка на тип переходного отверстия.

class ViastackRef : public BaseRef {
};

// Ссылка на стек контактных площадок.

class NetRef : public BaseRef {
};

// Ссылка на группу компонентов.

class CompGroupRef : public BaseRef {
};

// Ссылка на компонент на плате.

class CompInstanceRef : public BaseRef {
};

// Ссылка на группу цепей.

class NetGroupRef : public BaseRef {
};

// Ссылка на волновое сопротивление.

class ImpedanceRef : public BaseRef {
};

// Ссылка на сигнал.

class SignalRef : public BaseRef {
};

// Ссылка на группу сигналов..

class SignalGroupRef : public BaseRef {
};

// Ссылка на дифференциальный сигнал.

class DiffSignalRef : public BaseRef {
};

// Ссылка на контакт.

class PinRef {

    // Имя компонента, используется для ссылки на компонент.

public:
    // [XmlAttribute("compName")] public string _compName;
    std::string _compName;

    // Имя контакта компонента, используется для ссылки.

    // [XmlAttribute("pinName")] public string _pinName;
    std::string _pinName;
};

// Ссылка на контакт источника сигнала.

class SourcePinRef : public PinRef {
};

// Ссылка на контакт приёмника сигнала.

class ReceiverPinRef : public PinRef {
};

// Ссылка на стек контактных площадок.

class PadstackRef : public BaseRef {
};

// Ссылка на стиль надписей.

class TextStyleRef : public BaseRef {
};

// Ссылка на схемный компонент.

class ComponentRef : public BaseRef {
};

// Ссылка на посадочное место.

class FootprintRef : public BaseRef {
};

// Ссылка на вывод посадочного места.

class PadRef {

    // Ссылка на имя компонента

public:
    // [XmlAttribute("compName")] public string _compName;
    std::string _compName;

    // Номер контактной площадки (вывода) посадочного места.

    // [XmlAttribute("padNum", DataType = "int")] public int _padNum;
    int _padNum = 0;
};
//	#endregion Reference Type

//	#region Coordinates

class base_coordinat {
public:
    // [XmlAttribute("x", DataType = "float")] public float _x;
    float _x = 0.0F;

    // [XmlAttribute("y", DataType = "float")] public float _y;
    float _y = 0.0F;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};

// координаты точки, вершины.

class Dot : public base_coordinat {
};

// Центр круга (окружности), овала.

class Center : public base_coordinat {
};

// Начальная точка линии, дуги.

class Start : public base_coordinat {
};

// Средняя точка дуги.

class Middle : public base_coordinat {
};

// Конечная точка линии, дуги.

class End : public base_coordinat {
};

// Точка привязки объекта.

class Org : public base_coordinat {
};

// Cмещение точки привязки или объекта по осям x и y.

class Shift : public base_coordinat {
};

// Вытягивание по осям x и y.

class Stretch : public base_coordinat {
};

//	#endregion Coordinates

//	#region Segments
class IBaseSegment {
public:
    virtual void Shift(float x, float y) = 0;
    virtual void UnitsConvert(dist in_units, dist out_units) = 0;
};

// Описание прямолинейного сегмента контура.

class SegmentLine : public IBaseSegment {

    // Конечная точка линии, дуги.

public:
    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход против часовой стрелки.

class SegmentArcCCW : public SegmentLine {

    // Центр круга (окружности), овала.

public:
    // [XmlElement("Center")] public Center _Center;
    std::optional<Center> _Center;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся центром. Обход по часовой стрелки.

class SegmentArcCW : public SegmentArcCCW {
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.

class SegmentArcByAngle : public SegmentLine {

    // Задаёт угол в градусах c точностью до тысячных долей.

public:
    // [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;
};

// Описание дугообразного сегмента контура.
// Дуга, задаётся тремя точками: начало, середина и конец.

class SegmentArcByMiddle : public SegmentLine {

    // Конечная точка линии, дуги.

public:
    // [XmlElement("Middle")] public Middle _Middle;
    std::optional<Middle> _Middle;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};
//	#endregion Segments

//	#region Figures

// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов

class IBaseFigure {
public:
    virtual void UnitsConvert(dist in_units, dist out_units) = 0;
    virtual void Shift(float x, float y) = 0;
};

// Дуга, заданная центром. Обход против часовой стрелки.

class ArcCCW : public IBaseFigure {

    // Центр круга (окружности), овала.

public:
    // [XmlElement("Center")] public Center _Center;
    std::optional<Center> _Center;

    // Начальная точка линии, дуги.

    // [XmlElement("Start")] public Start _Start;
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.

    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Дуга, заданная центром. Обход по часовой стрелке.

class ArcCW : public ArcCCW {
};

// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.

class ArcByAngle : public IBaseFigure {

    // Задаёт угол в градусах c точностью до тысячных долей.

public:
    // [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    // Начальная точка линии, дуги.

    // [XmlElement("Start")] public Start _Start;
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.

    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Дуга, заданная тремя точками: начало, середина и конец.

class ArcByMiddle : public IBaseFigure {

    // Начальная точка линии, дуги.

public:
    // [XmlElement("Start")] public Start _Start;
    std::optional<Start> _Start;

    // Конечная точка линии, дуги.

    // [XmlElement("Middle")] public Middle _Middle;
    std::optional<Middle> _Middle;

    // Конечная точка линии, дуги.

    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание окружности (незалитого круга).

class Circle : public IBaseFigure {

    // Диаметр окружности, круга, овала.

public:
    // [XmlAttribute("diameter", DataType = "float")] public float _diameter;
    float _diameter = 0.0F;

    // Центр круга (окружности), овала.

    // [XmlElement("Center")] public Center _Center;
    std::optional<Center> _Center;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание линии.

class Line : public IBaseFigure {

    // Массив координат точек, вершин.

public:
    // [XmlElement("Dot")] public List<Dot> _Dots;
    std::vector<std::optional<Dot>> _Dots;
    bool ShouldSerialize_Dots();

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание полилинии.

class Polyline : public IBaseFigure {

    // Начальная точка линии, дуги.

public:
    // [XmlElement("Start")] public Start _Start;
    std::optional<Start> _Start;

    // Сегменты.

    // [XmlElement("SegmentLine", typeof(SegmentLine)), XmlElement("SegmentArcByAngle", typeof(SegmentArcByAngle)), XmlElement("SegmentArcCCW", typeof(SegmentArcCCW)), XmlElement("SegmentArcCW", typeof(SegmentArcCW)), XmlElement("SegmentArcByMiddle", typeof(SegmentArcByMiddle))] public List<Object> _Segments;
    std::vector<std::any> _Segments;
    bool ShouldSerialize_Segments();
    void Shift(float x, float y) override;
    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание незалитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.

class Contour : public Polyline {
};

// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины

class Rect : public Line {
};

// Описание залитого контура.
// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.

class FilledContour : public Polyline {

}; // TODO: требует уточнения

// Описание круга.

class FilledCircle : public Circle {
};

// Описание залитого прямоугольника.

class FilledRect : public Rect {
};

// Описание многоугольника.
// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.

class Polygon : public Line {
};

// Описание дугообразного сегмента проводника (дуга по часовой стрелке).

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackArcCW : public IBaseFigure {

    // Центр круга (окружности), овала.

public:
    // [XmlElement("Center")] public Center _Center;
    std::optional<Center> _Center;

    // Конечная точка линии, дуги.

    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.

    // [XmlAttribute("serpRef")] public string _serpRef;
    std::string _serpRef;

    void Shift(float x, float y) override;
    void UnitsConvert(dist in_units, dist out_units) override;
};

// Описание дугообразного сегмента проводника (дуга против часовой стрелки).

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackArc : public TrackArcCW {
};

// Описание прямолинейного сегмента проводника.

// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackLine : public IBaseFigure {

    // Конечная точка линии, дуги.

public:
    // [XmlElement("End")] public End _End;
    std::optional<End> _End;

    // Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.

    // [XmlAttribute("serpRef")] public string _serpRef;
    std::string _serpRef;

    void Shift(float x, float y) override;

    void UnitsConvert(dist in_units, dist out_units) override;
};

//	#endregion Figures

//	#region Rules area

// Устанавливает область действия правила: все слои.

class AllLayers {
public:
    // [XmlElement("AllLayers")] public string _AllLayers;
    std::string _AllLayers;
};

// Устанавливает область действия правила: все компоненты.

class AllComps {
public:
    // [XmlElement("AllComps")] public string _AllComps;
    std::string _AllComps;
};

// Устанавливает область действия правила: все цепи.

class AllNets {
public:
    // [XmlElement("AllNets")] public string _AllNets;
    std::string _AllNets;
};

// Устанавливает область действия правила: все внутренние слои.

class AllLayersInner {
public:
    // [XmlElement("AllLayersInner")] public string _AllLayersInner;
    std::string _AllLayersInner;
};

// Устанавливает область действия правила: все внутренние сигнальные слои.

class AllLayersInnerSignal {
public:
    // [XmlElement("AllLayersInnerSignal")] public string _AllLayersInnerSignal;
    std::string _AllLayersInnerSignal;
};

// Устанавливает область действия правила: все сигнальные слои.

class AllLayersSignal {
public:
    // [XmlElement("AllLayersSignal")] public string _AllLayersSignal;
    std::string _AllLayersSignal;
};

// Устанавливает область действия правила: все внешние слои.

class AllLayersOuter {
public:
    // [XmlElement("AllLayersOuter")] public string _AllLayersOuter;
    std::string _AllLayersOuter;
};

// Устанавливает доступные типы переходных отверстий для правила: все типы.

class AllViastacks {
public:
    // [XmlElement("AllViastacks")] public string _AllViastacks;
    std::string _AllViastacks;
};

// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.

class AllViastacksThrough {
public:
    // [XmlElement("AllViastacksThrough")] public string _AllViastacksThrough;
    std::string _AllViastacksThrough;
};

// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.

class AllViastacksNotThrough {
public:
    // [XmlElement("AllViastacksNotThrough")] public string _AllViastacksNotThrough;
    std::string _AllViastacksNotThrough;
};
//	#endregion Rules area

//	#region Thermal Detail Text ObjectSignal

// Описание термобарьера.

class Thermal {

    // Параметр термобарьера: число спиц.! В TopoR поддерживается только одно значение – 4.

public:
    // [XmlAttribute("spokeNum", DataType = "int")] public int _spokeNum;
    int _spokeNum = 0;

    // Параметр термобарьера: минимальное число спиц.

    // [XmlAttribute("minSpokeNum", DataType = "int")] public int _minSpokeNum;
    int _minSpokeNum = 0;

    // Задаёт угол в градусах c точностью до тысячных долей.

    // [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    // Параметр термобарьера: ширина спицы.

    // [XmlAttribute("spokeWidth", DataType = "float")] public float _spokeWidth;
    float _spokeWidth = 0.0F;

    // Параметр термобарьера: зазор между контактной площадкой и областью металлизации.

    // [XmlAttribute("backoff", DataType = "float")] public float _backoff;
    float _backoff = 0.0F;

    void UnitsConvert(dist in_units, dist out_units);
};

// Описание детали.

class Detail {

    // Толщина линии.

public:
    // [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
    float _lineWidth = 0.0F;

    // Ссылка на слой.

    // [XmlElement("LayerRef")] public LayerRef _LayerRef;
    std::optional<LayerRef> _LayerRef;

    // Описание фигуры.

    // [XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Line", typeof(Line)), XmlElement("Circle", typeof(Circle)), XmlElement("Rect", typeof(Rect)), XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("Polyline", typeof(Polyline)), XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure;
    std::any _Figure;

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);
};

// Описание надписи.

class Text {

    // Параметр надписи: текст надписи.

public:
    // [XmlAttribute("text")] public string _text;
    std::string _text;

    // Параметр надписей (ярлыков): способ выравнивания текста.

    // [XmlAttribute("align")] public align _align;
    align _align{};

    // Задаёт угол в градусах c точностью до тысячных долей.

    // [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    // Параметр надписей и ярлыков: зеркальность отображения.

    // [XmlAttribute("mirror")] public Bool _mirror;
    Bool _mirror{};

    // [XmlIgnore] public bool _mirrorSpecified
    bool getMirrorSpecified() const;

    // Ссылка на слой.

    // [XmlElement("LayerRef")] public LayerRef _LayerRef;
    std::optional<LayerRef> _LayerRef;

    // Ссылка на стиль надписей.

    // [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef;
    std::optional<TextStyleRef> _TextStyleRef;

    // Точка привязки объекта.

    // [XmlElement("Org")] public Org _Org;
    std::optional<Org> _Org;

    void Shift(float x, float y);

    // TODO: конвертировать текстовые стили по ссылке

    // <param name="in_units"></param>
    // <param name="out_units"></param>
    void UnitsConvert(dist in_units, dist out_units);
};

// Сигналы воздействия правила

class ObjectSignal {
public:
    // [XmlElement("SignalRef", typeof(SignalRef)), XmlElement("DiffSignalRef", typeof(DiffSignalRef)), XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object _Refs;
    std::any _Refs;
};
//	#endregion

// Различные сервисные функции

class Ut final {

    // Конвертация единиц измерения

    // <param name="value">значение</param>
    // <param name="in_units">текущие единицы измерения</param>
    // <param name="out_units">выходные единицы измерения</param>
    // <returns>Возвращает сконвертированное значение</returns>
public:
    static float UnitsConvert(float value, dist in_units, dist out_units);
};
} // namespace TopoR_PCB_Classes
