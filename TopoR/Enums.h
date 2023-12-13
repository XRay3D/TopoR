#pragma once

#include "ctre.hpp"
#include <QString>
#include <algorithm>
#include <array>
#include <limits>
#include <ranges>
#include <string_view>

using namespace std::literals;

namespace TopoR_PCB_Classes {

//	#region Enumerations //Все enum в алфавитном порядке

template <class Ty>
inline constexpr bool hasStrings = false;

namespace Impl {

using sv = std::string_view;
namespace ranges = std::ranges;

template <class Ty>
inline constexpr Ty Tokens = Ty{};

consteval size_t enum_size(sv enums) {
    return ranges::count(enums, ',') + !enums.ends_with(',');
}

template <size_t N, class Enum>
inline consteval auto tokenize_enum(sv base) {
    std::array<std::pair<sv, Enum>, N> tokens;
    std::underlying_type_t<Enum> val{};
    for (auto it = tokens.begin();
         auto&& [whole, name, value]:
         ctre::range<R"((\w+)(?: = (\w+))?,?)">(base)) {
        if (value)
            val = value.to_number();
        if (it != tokens.end())
            *it++ = {name.to_view(), static_cast<Enum>(val++)};
    }
    return tokens;
}

} // namespace Impl

#define ENUM(Enum, ...)                                                                              \
    enum class Enum : int {                                                                          \
        __VA_ARGS__                                                                                  \
    };                                                                                               \
    inline auto operator+(Enum e) noexcept { return std::underlying_type_t<Enum>(e); }               \
    template <>                                                                                      \
    inline constexpr auto hasStrings<Enum> = true;                                                   \
    namespace Impl {                                                                                 \
    template <>                                                                                      \
    inline constexpr auto Tokens<Enum> = tokenize_enum<enum_size(#__VA_ARGS__), Enum>(#__VA_ARGS__); \
    }

template <class E>
    requires hasStrings<E>
inline constexpr auto enumToString(E e) {
    auto it = std::ranges::find(Impl::Tokens<E>, e, &std::pair<Impl::sv, E>::second);
    return it == Impl::Tokens<E>.end() ? Impl::sv{} : it->first;
}

template <class E>
    requires hasStrings<E>
inline constexpr E stringToEnum(Impl::sv str) {
    auto it = std::ranges::find(Impl::Tokens<E>, str, &std::pair<Impl::sv, E>::first);
    return it == Impl::Tokens<E>.end()
        ? static_cast<E>(std::numeric_limits<std::underlying_type_t<E>>::min())
        : it->second;
}

template <class E>
inline constexpr Impl::sv enumToString(E e) { return "!!!"sv; }
template <class E>
inline constexpr E stringToEnum(Impl::sv str) { return E(std::numeric_limits<std::underlying_type_t<E>>::max()); }

// Параметр надписей (ярлыков): способ выравнивания текста. Значение по умолчанию – CM.
ENUM(align,
    // по центру
    /* [XmlEnum("CM")] CM, */
    CM,
    // по левому верхнему углу
    /* [XmlEnum("LT")] LT, */
    LT,
    // по верхнему краю
    /* [XmlEnum("CT")] CT, */
    CT,
    // по правому верхнему углу
    /* [XmlEnum("RT")] RT, */
    RT,
    // по левому краю
    /* [XmlEnum("LM")] LM, */
    LM,
    // по правому краю
    /* [XmlEnum("RM")] RM, */
    RM,
    // по левому нижнему углу
    /* [XmlEnum("LB")] LB, */
    LB,
    // по нижнему краю
    /* [XmlEnum("CB")] CB, */
    CB,
    // по правому нижнему углу
    /* [XmlEnum("RB")] RB */
    RB)

static_assert(hasStrings<align>);

// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.
ENUM(autoEqu,
    // не использовать функциональную эквивалентность
    /* [XmlEnum("None")] None, */
    None,
    // переназначать выводы компонента
    /* [XmlEnum("Pins")] Pins, */
    Pins,
    // переназначать вентили компонентов (не поддерживается)
    /* [XmlEnum("Gates")] Gates, */
    Gates,
    // разрешить все переназначения (не поддерживается)
    /* [XmlEnum("Full")] Full */
    Full)

// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.
ENUM(automove,
    // двигаются только переходы
    /* [XmlEnum("MoveVias")] MoveVias, */
    MoveVias,
    // двигаются только переходы; в процессе движения выполняется перекладка проводников
    /* [XmlEnum("MoveViasWithRefine")] MoveViasWithRefine, */
    MoveViasWithRefine,
    // двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников
    /* [XmlEnum("MoveCompsWithRefine")] MoveCompsWithRefine */
    MoveCompsWithRefine)

// Флаг, значение по умолчанию – off.
ENUM(Bool,
    /* [XmlEnum("off")] off, */
    off,
    /* [XmlEnum("on")] on */
    on)

// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.
ENUM(connectPad,
    // прямое подключение
    /* [XmlEnum("Direct")] Direct, */
    Direct,
    // подключение с помощью термобарьера
    /* [XmlEnum("Thermal")] Thermal */
    Thermal)

// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.
ENUM(connectVia,
    // прямое подключение
    /* [XmlEnum("Direct")] Direct, */
    Direct,
    // подключение с помощью термобарьера
    /* [XmlEnum("Thermal")] Thermal */
    Thermal)

// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
ENUM(dist,
    // миллиметр
    /* [XmlEnum("mm")] mm, */
    mm,
    // микрометр
    /* [XmlEnum("mkm")] mkm, */
    mkm,
    // сантиметр
    /* [XmlEnum("cm")] cm, */
    cm,
    // дециметр
    /* [XmlEnum("dm")] dm, */
    dm,
    // метр
    /* [XmlEnum("m")] m, */
    m,
    // мил(тысячная дюйма)
    /* [XmlEnum("mil")] mil, */
    mil,
    // дюйм
    /* [XmlEnum("inch")] inch */
    inch)

// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.
ENUM(fillType,
    // сплошная заливка
    /* [XmlEnum("Solid")] Solid, */
    Solid,
    // штриховка сеткой
    /* [XmlEnum("Hatched")] Hatched, */
    Hatched,
    // диагональная штриховка сеткой
    /* [XmlEnum("CRHatched")] CRHatched */
    CRHatched)

// Настройка отображения сетки: тип сетки.
ENUM(gridKind,
    /* [XmlEnum("Dots")] Dots, */
    Dots,
    /* [XmlEnum("Lines")] Lines */
    Lines)

// Тип слоя. Значение по умолчанию – Signal.
ENUM(layer_type,
    // сигнальный слой
    /* [XmlEnum("Signal")] Signal, */
    Signal,
    // сборочный слой (слой очертаний компонентов)
    /* [XmlEnum("Assy")] Assy, */
    Assy,
    // слой паяльной пасты
    /* [XmlEnum("Paste")] Paste, */
    Paste,
    // слой шелкографии
    /* [XmlEnum("Silk")] Silk, */
    Silk,
    // слой маски
    /* [XmlEnum("Mask")] Mask, */
    Mask,
    // опорный слой
    /* [XmlEnum("Plane")] Plane, */
    Plane,
    // механический слой
    /* [XmlEnum("Mechanical")] Mechanical, */
    Mechanical,
    // документирующий слой
    /* [XmlEnum("Doc")] Doc, */
    Doc,
    // диэлектрический слой
    /* [XmlEnum("Dielectric")] Dielectric */
    Dielectric)

// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.
ENUM(mode_Autoroute,
    // многослойная трассировка
    /* [XmlEnum("Multilayer")] Multilayer, */
    Multilayer,
    // однослойная трассировка на верхнем слое
    /* [XmlEnum("SinglelayerTop")] SinglelayerTop, */
    SinglelayerTop,
    // однослойная трассировка на нижнем слое
    /* [XmlEnum("SinglelayerBottom")] SinglelayerBottom */
    SinglelayerBottom)

// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
ENUM(mode_PadConnectSettings,
    // возможность подключения к углам КП определяется автоматически.
    /* [XmlEnum("AutoConnect")] AutoConnect, */
    AutoConnect,
    // разрешено подключаться к углам всех КП
    /* [XmlEnum("AllPads")] AllPads */
    AllPads)

// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.
ENUM(precision,
    // средняя точность
    /* [XmlEnum("Med")] Med, */
    Med,
    // низкая точность
    /* [XmlEnum("Low")] Low, */
    Low,
    // высокая точность
    /* [XmlEnum("High")] High */
    High)

// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.
ENUM(preference,
    // метрические (конкретные единицы выбираются в зависимости от параметра)
    /* [XmlEnum("Metric")] Metric, */
    Metric,
    // микрометр
    /* [XmlEnum("mkm")] mkm, */
    mkm,
    // миллиметр
    /* [XmlEnum("mm")] mm, */
    mm,
    // сантиметр
    /* [XmlEnum("cm")] cm, */
    cm,
    // дециметр
    /* [XmlEnum("dm")] dm, */
    dm,
    // метр
    /* [XmlEnum("m")] m, */
    m,
    // английские (конкретные единицы выбираются в зависимости от параметра)
    /* [XmlEnum("Imperial")] Imperial, */
    Imperial,
    // мил(тысячная дюйма)
    /* [XmlEnum("mil")] mil, */
    mil,
    // дюйм
    /* [XmlEnum("inch")] inch */
    inch)

// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.
ENUM(refine,
    // разрешён перенос проводников на другой слой.
    /* [XmlEnum("ChangeLayer")] ChangeLayer, */
    ChangeLayer,
    // без переноса проводников на другой слой.
    /* [XmlEnum("NoChangeLayer")] NoChangeLayer */
    NoChangeLayer)

// Тип запрета трассировки. Значение по умолчанию – Wires
ENUM(role,
    // запрет проводников
    /* [XmlEnum("Wires")] Wires, */
    Wires,
    // запрет переходных отверстий
    /* [XmlEnum("Vias")] Vias, */
    Vias,
    // запрет проводников и переходных отверстий
    /* [XmlEnum("Wires and Vias")] WiresАndVias */
    WiresАndVias)

// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.
ENUM(showWarnings,
    // показывать только отмеченные предупреждения
    /* [XmlEnum("ShowChecked")] ShowChecked, */
    ShowChecked,
    // показывать все предупреждения
    /* [XmlEnum("ShowAll")] ShowAll, */
    ShowAll,
    // ничего не показывать
    /* [XmlEnum("ShowNothing")] ShowNothing */
    ShowNothing)

// Сторона объекта.
// <remarks>! Значение Both возможно только при описании запретов размещения.</remarks>
ENUM(side,
    // верх
    /* [XmlEnum("Top")] Top, */
    Top,
    // низ
    /* [XmlEnum("Bottom")] Bottom, */
    Bottom,
    // обе стороны
    /* [XmlEnum("Both")] Both */
    Both)

// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.
ENUM(state,
    // незалитая
    /* [XmlEnum("Unpoured")] Unpoured, */
    Unpoured,
    // залитая
    /* [XmlEnum("Poured")] Poured, */
    Poured,
    // залитая и зафиксированная
    /* [XmlEnum("Locked")] Locked */
    Locked)

// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
ENUM(time,
    // пикосекунда
    /* [XmlEnum("ps")] ps, */
    ps,
    // фемтосекунда
    /* [XmlEnum("fs")] fs, */
    fs,
    // наносекунда
    /* [XmlEnum("ns")] ns, */
    ns,
    // микросекунда
    /* [XmlEnum("us")] us */
    us)

// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes
ENUM(type,
    // позиционное обозначение
    /* [XmlEnum("RefDes")] RefDes, */
    RefDes,
    // PartName
    /* [XmlEnum("PartName")] PartName */
    PartName)

// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.
ENUM(type_connectToCopper,
    // тип подключения не задан(используются настройки полигона)
    /* [XmlEnum("NoneConnect")] NoneConnect, */
    NoneConnect,
    // прямое подключение
    /* [XmlEnum("Direct")] Direct, */
    Direct,
    // подключение с помощью термобарьера
    /* [XmlEnum("Thermal")] Thermal */
    Thermal)

// Тип обработки углов прямоугольной контактной площадки.
ENUM(type_handling,
    // без обработки
    /* [XmlEnum("None")] None, */
    None,
    // скругление
    /* [XmlEnum("Rounding")] Rounding, */
    Rounding,
    // срез
    /* [XmlEnum("Chamfer")] Chamfer */
    Chamfer)

// Тип стека контактных площадок. Значение по умолчанию – Through.
ENUM(type_padstack,
    // сквозной
    /* [XmlEnum("Through")] Through, */
    Through,
    // планарный
    /* [XmlEnum("SMD")] SMD, */
    SMD,
    // монтажное отверстие
    /* [XmlEnum("MountHole")] MountHole */
    MountHole)

// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.
ENUM(units,
    // миллиметр
    /* [XmlEnum("mm")] mm, */
    mm,
    // мил (тысячная дюйма)
    /* [XmlEnum("mil")] mil */
    mil)

// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist
ENUM(valueType,
    // длина
    /* [XmlEnum("Dist")] Dist, */
    Dist,
    // время
    /* [XmlEnum("Time")] Time */
    Time)

// Параметр автоматической трассировки: форма проводников.
ENUM(wireShape,
    // Polyline
    /* [XmlEnum("Polyline")] Polyline, */
    Polyline,
    // Arcs
    /* [XmlEnum("Arcs")] Arcs */
    Arcs)

//	#endregion Enumerations

} // namespace TopoR_PCB_Classes
