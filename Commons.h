#pragma once

#include "qserializer.h"
#include <any>
#include <vector>

// C# TO C++ CONVERTER NOTE: Forward class declarations:
// namespace TopoR_PCB_Classes {
class Shift;
// }

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

// namespace TopoR_PCB_Classes {

//	#region Enumerations //Все enum в алфавитном порядке

/// <summary>
/// Параметр надписей (ярлыков): способ выравнивания текста. Значение по умолчанию – CM.
/// </summary>
struct align {
    enum E {
        /// <summary>
        /// по центру
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("CM")] CM,
        CM,
        /// <summary>
        /// по левому верхнему углу
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("LT")] LT,
        LT,
        /// <summary>
        /// по верхнему краю
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("CT")] CT,
        CT,
        /// <summary>
        /// по правому верхнему углу
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("RT")] RT,
        RT,
        /// <summary>
        /// по левому краю
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("LM")] LM,
        LM,
        /// <summary>
        /// по правому краю
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("RM")] RM,
        RM,
        /// <summary>
        /// по левому нижнему углу
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("LB")] LB,
        LB,
        /// <summary>
        /// по нижнему краю
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("CB")] CB,
        CB,
        /// <summary>
        /// по правому нижнему углу
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("RB")] RB
        RB
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    align(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(align)

/// <summary>
/// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.
/// </summary>
struct autoEqu {
    enum E {
        /// <summary>
        /// не использовать функциональную эквивалентность
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("None")] None,
        None,
        /// <summary>
        /// переназначать выводы компонента
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Pins")] Pins,
        Pins,
        /// <summary>
        /// переназначать вентили компонентов (не поддерживается)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Gates")] Gates,
        Gates,
        /// <summary>
        /// разрешить все переназначения (не поддерживается)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Full")] Full
        Full
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    autoEqu(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(autoEqu)

/// <summary>
/// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.
/// </summary>
struct automove {
    enum E {
        /// <summary>
        /// двигаются только переходы
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("MoveVias")] MoveVias,
        MoveVias,
        /// <summary>
        /// двигаются только переходы; в процессе движения выполняется перекладка проводников
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("MoveViasWithRefine")] MoveViasWithRefine,
        MoveViasWithRefine,
        /// <summary>
        /// двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("MoveCompsWithRefine")] MoveCompsWithRefine
        MoveCompsWithRefine
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    automove(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(automove)

/// <summary>
/// Флаг, значение по умолчанию – off.
/// </summary>
struct Bool {
    enum E {
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("off")] off,
        off,
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("on")] on
        on
    } e;
    Q_ENUM(E)
    operator<=>() = default;
    operator int() { return e; }
    Bool(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(Bool)

/// <summary>
/// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.
/// </summary>
struct connectPad {
    enum E {
        /// <summary>
        /// прямое подключение
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Direct")] Direct,
        Direct,
        /// <summary>
        /// подключение с помощью термобарьера
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
        Thermal
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    connectPad(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(connectPad)

/// <summary>
/// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.
/// </summary>
struct connectVia {
    enum E {
        /// <summary>
        /// прямое подключение
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Direct")] Direct,
        Direct,
        /// <summary>
        /// подключение с помощью термобарьера
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
        Thermal
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    connectVia(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(connectVia)

/// <summary>
/// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
/// </summary>
struct dist_ {
    enum E {
        /// <summary>
        /// микрометр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mkm")] mkm,
        mkm,
        /// <summary>
        /// миллиметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mm")] mm,
        mm,

        /// <summary>
        /// сантиметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("cm")] cm,
        cm,
        /// <summary>
        /// дециметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("dm")] dm,
        dm,
        /// <summary>
        /// метр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("m")] m,
        m,
        /// <summary>
        /// мил(тысячная дюйма)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mil")] mil,
        mil,
        /// <summary>
        /// дюйм
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("inch")] inch
        inch
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    dist_(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(dist_)
/// <summary>
/// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.
/// </summary>
struct fillType {
    enum E {
        /// <summary>
        /// сплошная заливка
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Solid")] Solid,
        Solid,
        /// <summary>
        /// штриховка сеткой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Hatched")] Hatched,
        Hatched,
        /// <summary>
        /// диагональная штриховка сеткой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("CRHatched")] CRHatched
        CRHatched
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    fillType(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(fillType)

/// <summary>
/// Настройка отображения сетки: тип сетки.
/// </summary>
struct gridKind {
    enum E {
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Dots")] Dots,
        Dots,
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Lines")] Lines
        Lines
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    gridKind(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(gridKind)

/// <summary>
/// Тип слоя. Значение по умолчанию – Signal.
/// </summary>
struct layer_type {
    enum E {
        /// <summary>
        /// сигнальный слой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Signal")] Signal,
        Signal,
        /// <summary>
        /// сборочный слой (слой очертаний компонентов)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Assy")] Assy,
        Assy,
        /// <summary>
        /// слой паяльной пасты
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Paste")] Paste,
        Paste,
        /// <summary>
        /// слой шелкографии
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Silk")] Silk,
        Silk,
        /// <summary>
        /// слой маски
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Mask")] Mask,
        Mask,
        /// <summary>
        /// опорный слой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Plane")] Plane,
        Plane,
        /// <summary>
        /// механический слой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Mechanical")] Mechanical,
        Mechanical,
        /// <summary>
        /// документирующий слой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Doc")] Doc,
        Doc,
        /// <summary>
        /// диэлектрический слой
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Dielectric")] Dielectric
        Dielectric
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    layer_type(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(layer_type)
/// <summary>
/// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.
/// </summary>
struct mode_Autoroute {
    enum E {
        /// <summary>
        /// многослойная трассировка
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Multilayer")] Multilayer,
        Multilayer,
        /// <summary>
        /// однослойная трассировка на верхнем слое
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("SinglelayerTop")] SinglelayerTop,
        SinglelayerTop,
        /// <summary>
        /// однослойная трассировка на нижнем слое
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("SinglelayerBottom")] SinglelayerBottom
        SinglelayerBottom
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    mode_Autoroute(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(mode_Autoroute)

/// <summary>
/// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
/// </summary>
struct mode_PadConnectSettings {
    enum E {
        /// <summary>
        /// возможность подключения к углам КП определяется автоматически.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("AutoConnect")] AutoConnect,
        AutoConnect,
        /// <summary>
        /// разрешено подключаться к углам всех КП
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("AllPads")] AllPads
        AllPads
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    mode_PadConnectSettings(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(mode_PadConnectSettings)

/// <summary>
/// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.
/// </summary>
struct precision {
    enum E {
        /// <summary>
        /// средняя точность
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Med")] Med,
        Med,
        /// <summary>
        /// низкая точность
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Low")] Low,
        Low,
        /// <summary>
        /// высокая точность
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("High")] High
        High
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    precision(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(precision)

/// <summary>
/// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.
/// </summary>
struct preference {
    enum E {
        /// <summary>
        /// метрические (конкретные единицы выбираются в зависимости от параметра)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Metric")] Metric,
        Metric,
        /// <summary>
        /// микрометр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mkm")] mkm,
        mkm,
        /// <summary>
        /// миллиметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mm")] mm,
        mm,
        /// <summary>
        /// сантиметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("cm")] cm,
        cm,
        /// <summary>
        /// дециметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("dm")] dm,
        dm,
        /// <summary>
        /// метр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("m")] m,
        m,
        /// <summary>
        /// английские (конкретные единицы выбираются в зависимости от параметра)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Imperial")] Imperial,
        Imperial,
        /// <summary>
        /// мил(тысячная дюйма)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mil")] mil,
        mil,
        /// <summary>
        /// дюйм
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("inch")] inch
        inch
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    preference(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(preference)

/// <summary>
/// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.
/// </summary>
struct refine {
    enum E {
        /// <summary>
        /// разрешён перенос проводников на другой слой.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ChangeLayer")] ChangeLayer,
        ChangeLayer,
        /// <summary>
        /// без переноса проводников на другой слой.
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("NoChangeLayer")] NoChangeLayer
        NoChangeLayer
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    refine(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(refine)

/// <summary>
/// Тип запрета трассировки. Значение по умолчанию – Wires
/// </summary>
struct role {
    enum E {
        /// <summary>
        /// запрет проводников
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Wires")] Wires,
        //    FIXME    Wires,
        /// <summary>
        /// запрет переходных отверстий
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Vias")] Vias,
        Vias,
        /// <summary>
        /// запрет проводников и переходных отверстий
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Wires and Vias")] WiresАndVias
        //   FIXME     WiresАndVias
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    role(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(role)

/// <summary>
/// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.
/// </summary>
struct showWarnings {
    enum E {
        /// <summary>
        /// показывать только отмеченные предупреждения
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ShowChecked")] ShowChecked,
        ShowChecked,
        /// <summary>
        /// показывать все предупреждения
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ShowAll")] ShowAll,
        ShowAll,
        /// <summary>
        /// ничего не показывать
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ShowNothing")] ShowNothing
        ShowNothing
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    showWarnings(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(showWarnings)

/// <summary>
/// Сторона объекта.
/// </summary>
/// <remarks>! Значение Both возможно только при описании запретов размещения.</remarks>
struct side {
    enum E {
        /// <summary>
        /// верх
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Top")] Top,
        Top,
        /// <summary>
        /// низ
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Bottom")] Bottom,
        Bottom,
        /// <summary>
        /// обе стороны
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Both")] Both
        Both
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    side(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(side)

/// <summary>
/// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.
/// </summary>
struct state {
    enum E {
        /// <summary>
        /// незалитая
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Unpoured")] Unpoured,
        Unpoured,
        /// <summary>
        /// залитая
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Poured")] Poured,
        Poured,
        /// <summary>
        /// залитая и зафиксированная
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Locked")] Locked
        Locked
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    state(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(state)

/// <summary>
/// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
/// </summary>
struct time_ {
    enum E {
        /// <summary>
        /// пикосекунда
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ps")] ps,
        ps,
        /// <summary>
        /// фемтосекунда
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("fs")] fs,
        fs,
        /// <summary>
        /// наносекунда
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("ns")] ns,
        ns,
        /// <summary>
        /// микросекунда
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("us")] us
        us
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    time_(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(time_)

/// <summary>
/// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes
/// </summary>
struct type {
    enum E {
        /// <summary>
        /// позиционное обозначение
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("RefDes")] RefDes,
        RefDes,
        /// <summary>
        /// PartName
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("PartName")] PartName
        PartName
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    type(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(type)
/// <summary>
/// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.
/// </summary>
struct type_connectToCopper {
    enum E {
        /// <summary>
        /// тип подключения не задан(используются настройки полигона)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("NoneConnect")] NoneConnect,
        NoneConnect,
        /// <summary>
        /// прямое подключение
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Direct")] Direct,
        Direct,
        /// <summary>
        /// подключение с помощью термобарьера
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
        Thermal
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    type_connectToCopper(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(type_connectToCopper)

/// <summary>
/// Тип обработки углов прямоугольной контактной площадки.
/// </summary>
struct type_handling {
    enum E {
        /// <summary>
        /// без обработки
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("None")] None,
        None,
        /// <summary>
        /// скругление
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Rounding")] Rounding,
        Rounding,
        /// <summary>
        /// срез
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Chamfer")] Chamfer
        Chamfer
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    type_handling(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(type_handling)
/// <summary>
/// Тип стека контактных площадок. Значение по умолчанию – Through.
/// </summary>
struct type_padstack {
    enum E {
        /// <summary>
        /// сквозной
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Through")] Through,
        Through,
        /// <summary>
        /// планарный
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("SMD")] SMD,
        SMD,
        /// <summary>
        /// монтажное отверстие
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("MountHole")] MountHole
        MountHole
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    type_padstack(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(type_padstack)
/// <summary>
/// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.
/// </summary>
struct units {
    enum E {
        /// <summary>
        /// миллиметр
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mm")] mm,
        mm,
        /// <summary>
        /// мил (тысячная дюйма)
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("mil")] mil
        mil
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    units(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(units)
/// <summary>
/// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist
/// </summary>
struct valueType {
    enum E {
        /// <summary>
        /// длина
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Dist")] Dist,
        Dist,
        /// <summary>
        /// время
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Time")] Time
        Time
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    valueType(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(valueType)

/// <summary>
/// Параметр автоматической трассировки: форма проводников.
/// </summary>
struct wireShape {
    enum E {
        /// <summary>
        /// Polyline
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Polyline")] Polyline,
        Polyline,
        /// <summary>
        /// Arcs
        /// </summary>
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlEnum("Arcs")] Arcs
        Arcs
    } e;
    Q_ENUM(E)
    operator int() { return e; }
    wireShape(int v = {}) { e = static_cast<E>(v); }
    Q_GADGET
};
Q_DECLARE_METATYPE(wireShape)

//	#endregion Enumerations

//	#region Reference Types
/// <summary>
/// базовый класс ссылок.
/// </summary>
class BaseRef : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Имя объекта или ссылка на именованный объект.
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("name")] public string _ReferenceName;
        QString _ReferenceName;
};

/// <summary>
/// Ссылка на атрибут.
/// </summary>
class AttributeRef : public BaseRef {
};

/// <summary>
/// Ссылка на тип слоя.
/// </summary>
class LayerTypeRef : public QSerializer {
    Q_GADGET
    QS_META_OBJECT_METHOD
    /// <summary>
    /// Тип слоя.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("type")] public layer_type _type;
    layer_type _type
        = static_cast<layer_type>(0);
};

/// <summary>
/// Ссылка на группу слоёв.
/// </summary>
class LayerGroupRef : public BaseRef {
};

/// <summary>
/// Ссылка на слой.
/// </summary>
/// <remarks>! Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.</remarks>
class LayerRef : public BaseRef {
    /// <summary>
    /// Тип слоя или ссылка на именованный cлой
    /// </summary>
    /// <remarks>В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено</remarks>
    // TODO:
    //   XmlAttribute("type", typeof(type_layer)),
};

/// <summary>
/// Ссылка на тип переходного отверстия.
/// </summary>
class ViastackRef : public BaseRef {
};

/// <summary>
/// Ссылка на стек контактных площадок.
/// </summary>
class NetRef : public BaseRef {
};

/// <summary>
/// Ссылка на группу компонентов.
/// </summary>
class CompGroupRef : public BaseRef {
};

/// <summary>
/// Ссылка на компонент на плате.
/// </summary>
class CompInstanceRef : public BaseRef {
};

/// <summary>
/// Ссылка на группу цепей.
/// </summary>
class NetGroupRef : public BaseRef {
};

/// <summary>
/// Ссылка на волновое сопротивление.
/// </summary>
class ImpedanceRef : public BaseRef {
};

/// <summary>
/// Ссылка на сигнал.
/// </summary>
class SignalRef : public BaseRef {
};

/// <summary>
/// Ссылка на группу сигналов..
/// </summary>
class SignalGroupRef : public BaseRef {
};

/// <summary>
/// Ссылка на дифференциальный сигнал.
/// </summary>
class DiffSignalRef : public BaseRef {
};

/// <summary>
/// Ссылка на контакт.
/// </summary>
class PinRef : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Имя компонента, используется для ссылки на компонент.
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("compName")] public string _compName;
        QString _compName;

    /// <summary>
    /// Имя контакта компонента, используется для ссылки.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("pinName")] public string _pinName;
    QString _pinName;
};

/// <summary>
/// Ссылка на контакт источника сигнала.
/// </summary>
class SourcePinRef : public PinRef {
};

/// <summary>
/// Ссылка на контакт приёмника сигнала.
/// </summary>
class ReceiverPinRef : public PinRef {
};

/// <summary>
/// Ссылка на стек контактных площадок.
/// </summary>
class PadstackRef : public BaseRef {
};

/// <summary>
/// Ссылка на стиль надписей.
/// </summary>
class TextStyleRef : public BaseRef {
};

/// <summary>
/// Ссылка на схемный компонент.
/// </summary>
class ComponentRef : public BaseRef {
};

/// <summary>
/// Ссылка на посадочное место.
/// </summary>
class FootprintRef : public BaseRef {
};

/// <summary>
/// Ссылка на вывод посадочного места.
/// </summary>
class PadRef : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Ссылка на имя компонента
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("compName")] public string _compName;
        QString _compName;

    /// <summary>
    /// Номер контактной площадки (вывода) посадочного места.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("padNum", DataType = "int")] public int _padNum;
    std::int32_t _padNum = 0;
};
//	#endregion Reference Type

//	#region Coordinates

class base_coordinat : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("x", DataType = "float")] public float _x;
        float _x
        = 0.0F;
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("y", DataType = "float")] public float _y;
    float _y = 0.0F;

    void Shift(float x, float y);

    void UnitsConvert(dist_ in_units, dist_ out_units);
};

/// <summary>
/// координаты точки, вершины.
/// </summary>
class Dot : public base_coordinat {
};

/// <summary>
/// Центр круга (окружности), овала.
/// </summary>
class Center : public base_coordinat {
};

/// <summary>
/// Начальная точка линии, дуги.
/// </summary>
class Start : public base_coordinat {
};

/// <summary>
/// Средняя точка дуги.
/// </summary>
class Middle : public base_coordinat {
};

/// <summary>
/// Конечная точка линии, дуги.
/// </summary>
class End : public base_coordinat {
};

/// <summary>
/// Точка привязки объекта.
/// </summary>
class Org : public base_coordinat {
};

/// <summary>
/// Cмещение точки привязки или объекта по осям x и y.
/// </summary>
class Shift : public base_coordinat {
};

/// <summary>
/// Вытягивание по осям x и y.
/// </summary>
class Stretch : public base_coordinat {
};

//	#endregion Coordinates

//	#region Segments
class IBaseSegment : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public : virtual void Shift(float x, float y) = 0;
    virtual void UnitsConvert(dist_ in_units, dist_ out_units) = 0;
};

/// <summary>
/// Описание прямолинейного сегмента контура.
/// </summary>
class SegmentLine : public IBaseSegment {
    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    virtual ~SegmentLine()
    {
        // delete _End;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание дугообразного сегмента контура.
/// Дуга, задаётся центром. Обход против часовой стрелки.
/// </summary>
class SegmentArcCCW : public SegmentLine {
    /// <summary>
    /// Центр круга (окружности), овала.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
    Center _Center;

    virtual ~SegmentArcCCW()
    {
        // delete _Center;
    }

    void Shift(float x, float y);

    void UnitsConvert(dist_ in_units, dist_ out_units);
};

/// <summary>
/// Описание дугообразного сегмента контура.
/// Дуга, задаётся центром. Обход по часовой стрелки.
/// </summary>
class SegmentArcCW : public SegmentArcCCW {
};

/// <summary>
/// Описание дугообразного сегмента контура.
/// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.
/// </summary>
class SegmentArcByAngle : public SegmentLine {
    /// <summary>
    /// Задаёт угол в градусах c точностью до тысячных долей.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;
};

/// <summary>
/// Описание дугообразного сегмента контура.
/// Дуга, задаётся тремя точками: начало, середина и конец.
/// </summary>
class SegmentArcByMiddle : public SegmentLine {
    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Middle")] public Middle _Middle;
    Middle _Middle;

    virtual ~SegmentArcByMiddle()
    {
        // delete _Middle;
    }

    void Shift(float x, float y);

    void UnitsConvert(dist_ in_units, dist_ out_units);
};
//	#endregion Segments

//	#region Figures
/// <summary>
/// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов
/// </summary>
class IBaseFigure : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public : virtual void UnitsConvert(dist_ in_units, dist_ out_units) = 0;
    virtual void Shift(float x, float y) = 0;
};

/// <summary>
/// Дуга, заданная центром. Обход против часовой стрелки.
/// </summary>
class ArcCCW : public IBaseFigure {
    /// <summary>
    /// Центр круга (окружности), овала.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
    Center _Center;

    /// <summary>
    /// Начальная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
    Start _Start;

    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    virtual ~ArcCCW()
    {
        // delete _Center;
        // delete _Start;
        // delete _End;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Дуга, заданная центром. Обход по часовой стрелке.
/// </summary>
class ArcCW : public ArcCCW {
};

/// <summary>
/// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
/// </summary>
class ArcByAngle : public IBaseFigure {
    /// <summary>
    /// Задаёт угол в градусах c точностью до тысячных долей.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    /// <summary>
    /// Начальная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
    Start _Start;

    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    virtual ~ArcByAngle()
    {
        // delete _Start;
        // delete _End;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Дуга, заданная тремя точками: начало, середина и конец.
/// </summary>
class ArcByMiddle : public IBaseFigure {
    /// <summary>
    /// Начальная точка линии, дуги.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
    Start _Start;

    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Middle")] public Middle _Middle;
    Middle _Middle;

    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    virtual ~ArcByMiddle()
    {
        // delete _Start;
        // delete _Middle;
        // delete _End;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание окружности (незалитого круга).
/// </summary>
class Circle : public IBaseFigure {
    /// <summary>
    /// Диаметр окружности, круга, овала.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("diameter", DataType = "float")] public float _diameter;
    float _diameter = 0.0F;

    /// <summary>
    /// Центр круга (окружности), овала.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
    Center _Center;

    virtual ~Circle()
    {
        // delete _Center;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание линии.
/// </summary>
class Line : public IBaseFigure {
    /// <summary>
    /// Массив координат точек, вершин.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
    std::vector<Dot*> _Dots;
    bool ShouldSerialize_Dots();

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание полилинии.
/// </summary>
class Polyline : public IBaseFigure {
    /// <summary>
    /// Начальная точка линии, дуги.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
    Start _Start;

    /// <summary>
    /// Сегменты.
    /// </summary>
    // C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("SegmentLine", typeof(SegmentLine)), XmlElement("SegmentArcByAngle", typeof(SegmentArcByAngle)), XmlElement("SegmentArcCCW", typeof(SegmentArcCCW)), XmlElement("SegmentArcCW", typeof(SegmentArcCW)), XmlElement("SegmentArcByMiddle", typeof(SegmentArcByMiddle))] public List<Object> _Segments;
    std::vector<std::any> _Segments;
    virtual ~Polyline()
    {
        // delete _Start;
    }

    bool ShouldSerialize_Segments();
    void Shift(float x, float y) override;
    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание незалитого контура.
/// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
/// </summary>
class Contour : public Polyline {
};

/// <summary>
/// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
/// </summary>
class Rect : public Line {
};

/// <summary>
/// Описание залитого контура.
/// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
/// </summary>
class FilledContour : public Polyline {
}; /// TODO: требует уточнения

/// <summary>
/// Описание круга.
/// </summary>
class FilledCircle : public Circle {
};

/// <summary>
/// Описание залитого прямоугольника.
/// </summary>
class FilledRect : public Rect {
};

/// <summary>
/// Описание многоугольника.
/// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
/// </summary>
class Polygon : public Line {
};

/// <summary>
/// Описание дугообразного сегмента проводника (дуга по часовой стрелке).
/// </summary>
/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackArcCW : public IBaseFigure {
    /// <summary>
    /// Центр круга (окружности), овала.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
    Center _Center;

    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    /// <summary>
    /// Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("serpRef")] public string _serpRef;
    QString _serpRef;

    virtual ~TrackArcCW()
    {
        // delete _Center;
        // delete _End;
    }

    void Shift(float x, float y) override;
    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

/// <summary>
/// Описание дугообразного сегмента проводника (дуга против часовой стрелки).
/// </summary>
/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackArc : public TrackArcCW {
};

/// <summary>
/// Описание прямолинейного сегмента проводника.
/// </summary>
/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
class TrackLine : public IBaseFigure {
    /// <summary>
    /// Конечная точка линии, дуги.
    /// </summary>
public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("End")] public End _End;
    End _End;

    /// <summary>
    /// Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("serpRef")] public string _serpRef;
    QString _serpRef;

    virtual ~TrackLine()
    {
        // delete _End;
    }

    void Shift(float x, float y) override;

    void UnitsConvert(dist_ in_units, dist_ out_units) override;
};

//	#endregion Figures

//	#region Rules area
/// <summary>
/// Устанавливает область действия правила: все слои.
/// </summary>
class AllLayers : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllLayers")] public string _AllLayers;
        QString _AllLayers;
};

/// <summary>
/// Устанавливает область действия правила: все компоненты.
/// </summary>
class AllComps : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllComps")] public string _AllComps;
        QString _AllComps;
};

/// <summary>
/// Устанавливает область действия правила: все цепи.
/// </summary>
class AllNets : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllNets")] public string _AllNets;
        QString _AllNets;
};
/// <summary>
/// Устанавливает область действия правила: все внутренние слои.
/// </summary>
class AllLayersInner : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllLayersInner")] public string _AllLayersInner;
        QString _AllLayersInner;
};

/// <summary>
/// Устанавливает область действия правила: все внутренние сигнальные слои.
/// </summary>
class AllLayersInnerSignal : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllLayersInnerSignal")] public string _AllLayersInnerSignal;
        QString _AllLayersInnerSignal;
};

/// <summary>
/// Устанавливает область действия правила: все сигнальные слои.
/// </summary>
class AllLayersSignal : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllLayersSignal")] public string _AllLayersSignal;
        QString _AllLayersSignal;
};

/// <summary>
/// Устанавливает область действия правила: все внешние слои.
/// </summary>
class AllLayersOuter : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllLayersOuter")] public string _AllLayersOuter;
        QString _AllLayersOuter;
};

/// <summary>
/// Устанавливает доступные типы переходных отверстий для правила: все типы.
/// </summary>
class AllViastacks : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllViastacks")] public string _AllViastacks;
        QString _AllViastacks;
};

/// <summary>
/// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
/// </summary>
class AllViastacksThrough : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllViastacksThrough")] public string _AllViastacksThrough;
        QString _AllViastacksThrough;
};

/// <summary>
/// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
/// </summary>
class AllViastacksNotThrough : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("AllViastacksNotThrough")] public string _AllViastacksNotThrough;
        QString _AllViastacksNotThrough;
};
//	#endregion Rules area

//	#region Thermal Detail Text ObjectSignal

/// <summary>
/// Описание термобарьера.
/// </summary>
class Thermal : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Параметр термобарьера: число спиц.! В TopoR поддерживается только одно значение – 4.
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("spokeNum", DataType = "int")] public int _spokeNum;
        std::int32_t _spokeNum
        = 0;

    /// <summary>
    /// Параметр термобарьера: минимальное число спиц.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("minSpokeNum", DataType = "int")] public int _minSpokeNum;
    std::int32_t _minSpokeNum = 0;

    /// <summary>
    /// Задаёт угол в градусах c точностью до тысячных долей.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    /// <summary>
    /// Параметр термобарьера: ширина спицы.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("spokeWidth", DataType = "float")] public float _spokeWidth;
    float _spokeWidth = 0.0F;

    /// <summary>
    /// Параметр термобарьера: зазор между контактной площадкой и областью металлизации.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("backoff", DataType = "float")] public float _backoff;
    float _backoff = 0.0F;

    void UnitsConvert(dist_ in_units, dist_ out_units);
};

/// <summary>
/// Описание детали.
/// </summary>
class Detail : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Толщина линии.
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
        float _lineWidth
        = 0.0F;

    /// <summary>
    /// Ссылка на слой.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
    LayerRef _LayerRef;

    /// <summary>
    /// Описание фигуры.
    /// </summary>
    // C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Line", typeof(Line)), XmlElement("Circle", typeof(Circle)), XmlElement("Rect", typeof(Rect)), XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("Polyline", typeof(Polyline)), XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure;
    std::any _Figure;

    virtual ~Detail()
    {
        // delete _LayerRef;
    }

    void Shift(float x, float y);

    void UnitsConvert(dist_ in_units, dist_ out_units);
};

/// <summary>
/// Описание надписи.
/// </summary>
class Text : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Параметр надписи: текст надписи.
        /// </summary>
        public :
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlAttribute("text")] public string _text;
        QString _text;

    /// <summary>
    /// Параметр надписей (ярлыков): способ выравнивания текста.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("align")] public align _align;
    align _align = static_cast<align>(0);

    /// <summary>
    /// Задаёт угол в градусах c точностью до тысячных долей.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
    float _angle = 0.0F;

    /// <summary>
    /// Параметр надписей и ярлыков: зеркальность отображения.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("mirror")] public Bool _mirror;
    Bool _mirror = static_cast<Bool>(0);
    virtual ~Text()
    {
        // delete _LayerRef;
        // delete _TextStyleRef;
        // delete _Org;
    }

    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlIgnore] public bool _mirrorSpecified
    bool getMirrorSpecified() const;

    /// <summary>
    /// Ссылка на слой.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
    LayerRef _LayerRef;

    /// <summary>
    /// Ссылка на стиль надписей.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef;
    TextStyleRef _TextStyleRef;

    /// <summary>
    /// Точка привязки объекта.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
    Org _Org;

    void Shift(float x, float y);
    /// <summary>
    /// TODO: конвертировать текстовые стили по ссылке
    /// </summary>
    /// <param name="in_units"></param>
    /// <param name="out_units"></param>
    void UnitsConvert(dist_ in_units, dist_ out_units);
};

/// <summary>
/// Сигналы воздействия правила
/// </summary>
class ObjectSignal : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD public :
        // C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        // ORIGINAL LINE: [XmlElement("SignalRef", typeof(SignalRef)), XmlElement("DiffSignalRef", typeof(DiffSignalRef)), XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object _Refs;
        std::any _Refs;
};
//	#endregion

/// <summary>
/// Различные сервисные функции
/// </summary>
class Ut final : public QSerializer {

    Q_GADGET QS_META_OBJECT_METHOD
        /// <summary>
        /// Конвертация единиц измерения
        /// </summary>
        /// <param name="value">значение</param>
        /// <param name="in_units">текущие единицы измерения</param>
        /// <param name="out_units">выходные единицы измерения</param>
        /// <returns>Возвращает сконвертированное значение</returns>
        public : static float
                 UnitsConvert(double value, dist_ in_units, dist_ out_units);
};
// } // namespace TopoR_PCB_Classes
