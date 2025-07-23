#pragma once

#include "ctre.hpp"
#include "qdebug.h"
#include <QString>
#include <algorithm>
#include <array>
#include <limits>
#include <meta>
#include <ranges>
#include <string_view>

using namespace std::literals;
namespace meta = std::meta;

template <typename E> concept Enum = std::is_enum_v<E>;

template <Enum E>
inline constexpr auto operator+(E e) noexcept { return std::to_underlying(e); }

template <Enum E>
inline constexpr std::string_view enumToString(E value) {
    template for(constexpr auto e: std::define_static_array(meta::enumerators_of(^^E))) {
        if(value == [:e:]) return meta::identifier_of(e);
    }
    return "";
}

template <Enum E>
inline constexpr E stringToEnum(std::string_view value) {
    template for(constexpr auto e: std::define_static_array(meta::enumerators_of(^^E))) {
        if(value == meta::identifier_of(e)) return [:e:];
    }
    return E(-1);
}

namespace TopoR {

enum ArcDir {
    CW,
    CCW
};

// 23:10:03: Прошло времени: 00:40.
namespace Enumerations { // Все enum в алфавитном порядке

// Параметр надписей (ярлыков): способ выравнивания текста. Значение по умолчанию – CM.
enum class align : int {
    CM, // по центру
    LT, // по левому верхнему углу
    CT, // по верхнему краю
    RT, // по правому верхнему углу
    LM, // по левому краю
    RM, // по правому краю
    LB, // по левому нижнему углу
    CB, // по нижнему краю
    RB  // по правому нижнему углу
};

// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.
enum class autoEqu : int {
    None,  // не использовать функциональную эквивалентность
    Pins,  // переназначать выводы компонента
    Gates, // переназначать вентили компонентов (не поддерживается)
    Full   // разрешить все переназначения (не поддерживается)
};

// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.
enum class automove : int {
    MoveVias,           // двигаются только переходы
    MoveViasWithRefine, // двигаются только переходы; в процессе движения выполняется перекладка проводников
    MoveCompsWithRefine // двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников
};

// Флаг, значение по умолчанию – off.
enum class Bool : int {
    off, // off,
    on   // on
};

// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.
enum class connectPad : int {
    Direct, // прямое подключение
    Thermal // подключение с помощью термобарьера
};

// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.
enum class connectVia : int {
    Direct, // прямое подключение
    Thermal // подключение с помощью термобарьера
};

// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
enum class dist : int {
    mm,  // миллиметр
    mkm, // микрометр
    cm,  // сантиметр
    dm,  // дециметр
    m,   // метр
    mil, // мил(тысячная дюйма)
    inch // дюйм
};

// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.
enum class fillType : int {
    Solid,    // сплошная заливка
    Hatched,  // штриховка сеткой
    CRHatched // диагональная штриховка сеткой
};
// Настройка отображения сетки: тип сетки.

enum class gridKind : int {
    Dots, // Dots,
    Lines // Lines
};

// Тип слоя. Значение по умолчанию – Signal.
enum class LayerType : int {
    Signal,     // сигнальный слой
    Assy,       // сборочный слой (слой очертаний компонентов)
    Paste,      // слой паяльной пасты
    Silk,       // слой шелкографии
    Mask,       // слой маски
    Plane,      // опорный слой
    Mechanical, // механический слой
    Doc,        // документирующий слой
    Dielectric  // диэлектрический слой
};

// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.
enum class mode_Autoroute : int {
    MultiLayer,       // многослойная трассировка
    SingleLayerTop,   // однослойная трассировка на верхнем слое
    SingleLayerBottom // однослойная трассировка на нижнем слое
};

// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
enum class mode_PadConnectSettings : int {
    AutoConnect, // возможность подключения к углам КП определяется автоматически.
    AllPads      // разрешено подключаться к углам всех КП
};

// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.
enum class precision : int {
    Med, // средняя точность
    Low, // низкая точность
    High // высокая точность
};

// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.
enum class preference : int {
    Metric,   // метрические (конкретные единицы выбираются в зависимости от параметра)
    mkm,      // микрометр
    mm,       // миллиметр
    cm,       // сантиметр
    dm,       // дециметр
    m,        // метр
    Imperial, // английские (конкретные единицы выбираются в зависимости от параметра)
    mil,      // мил(тысячная дюйма)
    inch      // дюйм
};

// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.
enum class refine : int {
    ChangeLayer,  // разрешён перенос проводников на другой слой.
    NoChangeLayer // без переноса проводников на другой слой.
};

// Тип запрета трассировки. Значение по умолчанию – Wires
enum class role : int {
    Wires,         // запрет проводников
    Vias,          // запрет переходных отверстий
    Wires_and_Vias // запрет проводников и переходных отверстий
};

// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.
enum class showWarnings : int {
    ShowChecked, // показывать только отмеченные предупреждения
    ShowAll,     // показывать все предупреждения
    ShowNothing  // ничего не показывать
};
// Сторона объекта.

// NOTE !Значение Both возможно только при описании запретов размещения.
enum class side : int {
    Top,    // верх
    Bottom, // низ
    Both    // обе стороны
};

// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.
enum class state : int {
    Unpoured, // незалитая
    Poured,   // залитая
    Locked    // залитая и зафиксированная
};

// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
enum class time : int {
    ps, // пикосекунда
    fs, // фемтосекунда
    ns, // наносекунда
    us  // микросекунда
};

// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes
enum class type : int {
    RefDes,  // позиционное обозначение
    PartName // PartName
};

// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.
enum class ConnectToCopper : int {
    NoneConnect, // тип подключения не задан(используются настройки полигона)
    Direct,      // прямое подключение
    Thermal      // подключение с помощью термобарьера
};

// Тип обработки углов прямоугольной контактной площадки.
enum class Handling : int {
    None,     // без обработки
    Rounding, // скругление
    Chamfer   // срез
};

// Тип стека контактных площадок. Значение по умолчанию – Through.
enum class type_padstack : int {
    Through,     // сквозной
    SMD,         // планарный
    MountingHole // монтажное отверстие
};

// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.
enum class units : int {
    mm, // миллиметр
    mil // мил (тысячная дюйма)
};

// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist
enum class valueType : int {
    Dist, // длина
    Time  // время
};

// Параметр автоматической трассировки: форма проводников.
enum class wireShape : int {
    Polyline, // Polyline
    Arcs      // Arcs
};

} // namespace Enumerations
using namespace Enumerations;

} // namespace TopoR
