#pragma once

#include "ctre.hpp"
#include <QString>
#include <algorithm>
#include <array>
#include <limits>
#include <ranges>
#include <string_view>

using namespace std::literals;

namespace TopoR {

enum ArcDir {
    CW,
    CCW
};

namespace Enumerations { // Все enum в алфавитном порядке

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
    for(auto it = tokens.begin();
        auto&& [whole, name, value]:
        ctre::range<R"((\w+)(?: = (\w+))?,?)">(base)) {
        if(value)
            val = value.to_number();
        if(it != tokens.end())
            *it++ = {name.to_view(), static_cast<Enum>(val++)};
    }
    return tokens;
}

} // namespace Impl

#define XML_ENUM(Enum, ...)                                                                          \
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
XML_ENUM(align,
    CM, // по центру
    LT, // по левому верхнему углу
    CT, // по верхнему краю
    RT, // по правому верхнему углу
    LM, // по левому краю
    RM, // по правому краю
    LB, // по левому нижнему углу
    CB, // по нижнему краю
    RB  // по правому нижнему углу
)

// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.
XML_ENUM(autoEqu,
    None,  // не использовать функциональную эквивалентность
    Pins,  // переназначать выводы компонента
    Gates, // переназначать вентили компонентов (не поддерживается)
    Full   // разрешить все переназначения (не поддерживается)
)

// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.
XML_ENUM(automove,
    MoveVias,           // двигаются только переходы
    MoveViasWithRefine, // двигаются только переходы; в процессе движения выполняется перекладка проводников
    MoveCompsWithRefine // двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников
)

// Флаг, значение по умолчанию – off.
XML_ENUM(Bool,
    off, // off,
    on   // on
)

// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.
XML_ENUM(connectPad,
    Direct, // прямое подключение
    Thermal // подключение с помощью термобарьера
)

// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.
XML_ENUM(connectVia,
    Direct, // прямое подключение
    Thermal // подключение с помощью термобарьера
)

// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
XML_ENUM(dist,
    mm,  // миллиметр
    mkm, // микрометр
    cm,  // сантиметр
    dm,  // дециметр
    m,   // метр
    mil, // мил(тысячная дюйма)
    inch // дюйм
)

// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.
XML_ENUM(fillType,
    Solid,    // сплошная заливка
    Hatched,  // штриховка сеткой
    CRHatched // диагональная штриховка сеткой
)
// Настройка отображения сетки: тип сетки.

XML_ENUM(gridKind,
    Dots, // Dots,
    Lines // Lines
)

// Тип слоя. Значение по умолчанию – Signal.
XML_ENUM(LayerType,
    Signal,     // сигнальный слой
    Assy,       // сборочный слой (слой очертаний компонентов)
    Paste,      // слой паяльной пасты
    Silk,       // слой шелкографии
    Mask,       // слой маски
    Plane,      // опорный слой
    Mechanical, // механический слой
    Doc,        // документирующий слой
    Dielectric  // диэлектрический слой
)

// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.
XML_ENUM(mode_Autoroute,
    Multilayer,       // многослойная трассировка
    SinglelayerTop,   // однослойная трассировка на верхнем слое
    SinglelayerBottom // однослойная трассировка на нижнем слое
)

// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
XML_ENUM(mode_PadConnectSettings,
    AutoConnect, // возможность подключения к углам КП определяется автоматически.
    AllPads      // разрешено подключаться к углам всех КП
)

// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.
XML_ENUM(precision,
    Med, // средняя точность
    Low, // низкая точность
    High // высокая точность
)

// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.
XML_ENUM(preference,
    Metric,   // метрические (конкретные единицы выбираются в зависимости от параметра)
    mkm,      // микрометр
    mm,       // миллиметр
    cm,       // сантиметр
    dm,       // дециметр
    m,        // метр
    Imperial, // английские (конкретные единицы выбираются в зависимости от параметра)
    mil,      // мил(тысячная дюйма)
    inch      // дюйм
)

// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.
XML_ENUM(refine,
    ChangeLayer,  // разрешён перенос проводников на другой слой.
    NoChangeLayer // без переноса проводников на другой слой.
)

// Тип запрета трассировки. Значение по умолчанию – Wires
XML_ENUM(role,
    Wires,       // запрет проводников
    Vias,        // запрет переходных отверстий
    WiresАndVias // запрет проводников и переходных отверстий
)

// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.
XML_ENUM(showWarnings,
    ShowChecked, // показывать только отмеченные предупреждения
    ShowAll,     // показывать все предупреждения
    ShowNothing  // ничего не показывать
)
// Сторона объекта.

/// \note !Значение Both возможно только при описании запретов размещения.
XML_ENUM(side,
    Top,    // верх
    Bottom, // низ
    Both    // обе стороны
)

// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.
XML_ENUM(state,
    Unpoured, // незалитая
    Poured,   // залитая
    Locked    // залитая и зафиксированная
)

// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
XML_ENUM(time,
    ps, // пикосекунда
    fs, // фемтосекунда
    ns, // наносекунда
    us  // микросекунда
)

// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes
XML_ENUM(type,
    RefDes,  // позиционное обозначение
    PartName // PartName
)

// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.
XML_ENUM(ConnectToCopper,
    NoneConnect, // тип подключения не задан(используются настройки полигона)
    Direct,      // прямое подключение
    Thermal      // подключение с помощью термобарьера
)

// Тип обработки углов прямоугольной контактной площадки.
XML_ENUM(Handling,
    None,     // без обработки
    Rounding, // скругление
    Chamfer   // срез
)

// Тип стека контактных площадок. Значение по умолчанию – Through.
XML_ENUM(type_padstack,
    Through,  // сквозной
    SMD,      // планарный
    MountHole // монтажное отверстие
)

// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.
XML_ENUM(units,
    mm, // миллиметр
    mil // мил (тысячная дюйма)
)

// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist
XML_ENUM(valueType,
    Dist, // длина
    Time  // время
)

// Параметр автоматической трассировки: форма проводников.
XML_ENUM(wireShape,
    Polyline, // Polyline
    Arcs      // Arcs
)

} // namespace Enumerations
using namespace Enumerations;

} // namespace TopoR
