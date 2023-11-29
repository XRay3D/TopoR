#pragma once

#include <string>
#include <vector>
#include <any>
#include <memory>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace TopoR_PCB_Classes { class Shift; }

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */


namespace TopoR_PCB_Classes
{

//	#region Enumerations //Все enum в алфавитном порядке

	/// <summary>
	/// Параметр надписей (ярлыков): способ выравнивания текста. Значение по умолчанию – CM.
	/// </summary>
	enum class align
	{
		/// <summary>
		/// по центру
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("CM")] CM,
		CM,
		/// <summary>
		/// по левому верхнему углу
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("LT")] LT,
		LT,
		/// <summary>
		/// по верхнему краю
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("CT")] CT,
		CT,
		/// <summary>
		/// по правому верхнему углу
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("RT")] RT,
		RT,
		/// <summary>
		/// по левому краю
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("LM")] LM,
		LM,
		/// <summary>
		/// по правому краю
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("RM")] RM,
		RM,
		/// <summary>
		/// по левому нижнему углу
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("LB")] LB,
		LB,
		/// <summary>
		/// по нижнему краю
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("CB")] CB,
		CB,
		/// <summary>
		/// по правому нижнему углу
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("RB")] RB
		RB
	};

	/// <summary>
	/// Параметр автоматической трассировки: использование функциональной эквивалентности. Значение по умолчанию – None.
	/// </summary>
	enum class autoEqu
	{
		/// <summary>
		/// не использовать функциональную эквивалентность
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("None")] None,
		None,
		/// <summary>
		/// переназначать выводы компонента
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Pins")] Pins,
		Pins,
		/// <summary>
		/// переназначать вентили компонентов (не поддерживается)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Gates")] Gates,
		Gates,
		/// <summary>
		/// разрешить все переназначения (не поддерживается)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Full")] Full
		Full
	};

	/// <summary>
	/// Настройка автоматической подвижки. Значение по умолчанию – MoveVias.
	/// </summary>
	enum class automove
	{
		/// <summary>
		/// двигаются только переходы
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("MoveVias")] MoveVias,
		MoveVias,
		/// <summary>
		/// двигаются только переходы; в процессе движения выполняется перекладка проводников
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("MoveViasWithRefine")] MoveViasWithRefine,
		MoveViasWithRefine,
		/// <summary>
		/// двигаются компоненты и переходы; в процессе движения выполняется перекладка проводников
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("MoveCompsWithRefine")] MoveCompsWithRefine
		MoveCompsWithRefine
	};

	/// <summary>
	/// Флаг, значение по умолчанию – off.
	/// </summary>
	enum class Bool
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("off")] off,
		off,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("on")] on
		on
	};

	/// <summary>
	/// Параметр области металлизации (полигона) стека: подключение контактных площадок. Значение по умолчанию – Direct.
	/// </summary>
	enum class connectPad
	{
		/// <summary>
		/// прямое подключение
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Direct")] Direct,
		Direct,
		/// <summary>
		/// подключение с помощью термобарьера
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
		Thermal
	};

	/// <summary>
	/// Параметр области металлизации (полигона): подключение площадок переходных отверстий. Значение по умолчанию – Direct.
	/// </summary>
	enum class connectVia
	{
		/// <summary>
		/// прямое подключение
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Direct")] Direct,
		Direct,
		/// <summary>
		/// подключение с помощью термобарьера
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
		Thermal
	};

	/// <summary>
	/// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
	/// </summary>
	enum class dist
	{
		/// <summary>
		/// миллиметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mm")] mm,
		mm,
		/// <summary>
		/// микрометр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mkm")] mkm,
		mkm,
		/// <summary>
		/// сантиметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("cm")] cm,
		cm,
		/// <summary>
		/// дециметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("dm")] dm,
		dm,
		/// <summary>
		/// метр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("m")] m,
		m,
		/// <summary>
		/// мил(тысячная дюйма)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mil")] mil,
		mil,
		/// <summary>
		/// дюйм
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("inch")] inch
		inch
	};

	/// <summary>
	/// Параметр области металлизации (полигона): тип заливки. Значение по умолчанию – Solid.
	/// </summary>
	enum class fillType
	{
		/// <summary>
		/// сплошная заливка
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Solid")] Solid,
		Solid,
		/// <summary>
		/// штриховка сеткой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Hatched")] Hatched,
		Hatched,
		/// <summary>
		/// диагональная штриховка сеткой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("CRHatched")] CRHatched
		CRHatched
	};

	/// <summary>
	/// Настройка отображения сетки: тип сетки.
	/// </summary>
	enum class gridKind
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Dots")] Dots,
		Dots,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Lines")] Lines
		Lines
	};

	/// <summary>
	/// Тип слоя. Значение по умолчанию – Signal.
	/// </summary>
	enum class layer_type
	{
		/// <summary>
		/// сигнальный слой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Signal")] Signal,
		Signal,
		/// <summary>
		/// сборочный слой (слой очертаний компонентов)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Assy")] Assy,
		Assy,
		/// <summary>
		/// слой паяльной пасты 
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Paste")] Paste,
		Paste,
		/// <summary>
		/// слой шелкографии
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Silk")] Silk,
		Silk,
		/// <summary>
		/// слой маски
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Mask")] Mask,
		Mask,
		/// <summary>
		/// опорный слой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Plane")] Plane,
		Plane,
		/// <summary>
		/// механический слой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Mechanical")] Mechanical,
		Mechanical,
		/// <summary>
		/// документирующий слой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Doc")] Doc,
		Doc,
		/// <summary>
		/// диэлектрический слой
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Dielectric")] Dielectric
		Dielectric
	};

	/// <summary>
	/// Настройка автоматической трассировки: режим трассировки. Значение по умолчанию – Multilayer.
	/// </summary>
	enum class mode_Autoroute
	{
		/// <summary>
		/// многослойная трассировка
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Multilayer")] Multilayer,
		Multilayer,
		/// <summary>
		/// однослойная трассировка на верхнем слое
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("SinglelayerTop")] SinglelayerTop,
		SinglelayerTop,
		/// <summary>
		/// однослойная трассировка на нижнем слое
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("SinglelayerBottom")] SinglelayerBottom
		SinglelayerBottom
	};

	/// <summary>
	/// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
	/// </summary>
	enum class mode_PadConnectSettings
	{
		/// <summary>
		/// возможность подключения к углам КП определяется автоматически.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("AutoConnect")] AutoConnect,
		AutoConnect,
		/// <summary>
		/// разрешено подключаться к углам всех КП
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("AllPads")] AllPads
		AllPads
	};

	/// <summary>
	/// Параметр области металлизации (полигона): точность аппроксимации контура. Значение по умолчанию – Med.
	/// </summary>
	enum class precision
	{
		/// <summary>
		/// средняя точность
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Med")] Med,
		Med,
		/// <summary>
		/// низкая точность
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Low")] Low,
		Low,
		/// <summary>
		/// высокая точность
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("High")] High
		High
	};

	/// <summary>
	/// Настройка отображения: единицы измерения. Значение по умолчанию – Metric.
	/// </summary>
	enum class preference
	{
		/// <summary>
		/// метрические (конкретные единицы выбираются в зависимости от параметра)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Metric")] Metric,
		Metric,
		/// <summary>
		/// микрометр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mkm")] mkm,
		mkm,
		/// <summary>
		/// миллиметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mm")] mm,
		mm,
		/// <summary>
		/// сантиметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("cm")] cm,
		cm,
		/// <summary>
		/// дециметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("dm")] dm,
		dm,
		/// <summary>
		/// метр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("m")] m,
		m,
		/// <summary>
		/// английские (конкретные единицы выбираются в зависимости от параметра)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Imperial")] Imperial,
		Imperial,
		/// <summary>
		/// мил(тысячная дюйма)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mil")] mil,
		mil,
		/// <summary>
		/// дюйм
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("inch")] inch
		inch
	};

	/// <summary>
	/// Настройка автоматической перекладки проводников. Значение по умолчанию – ChangeLayer.
	/// </summary>
	enum class refine
	{
		/// <summary>
		/// разрешён перенос проводников на другой слой.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ChangeLayer")] ChangeLayer,
		ChangeLayer,
		/// <summary>
		/// без переноса проводников на другой слой.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("NoChangeLayer")] NoChangeLayer
		NoChangeLayer
	};

	/// <summary>
	/// Тип запрета трассировки. Значение по умолчанию – Wires
	/// </summary>
	enum class role
	{
		/// <summary>
		/// запрет проводников
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Wires")] Wires,
		Wires,
		/// <summary>
		/// запрет переходных отверстий
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Vias")] Vias,
		Vias,
		/// <summary>
		/// запрет проводников и переходных отверстий
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Wires and Vias")] WiresАndVias
		WiresАndVias
	};

	/// <summary>
	/// Настройка фильтра сообщений: режим показа предупреждений. Значение по умолчанию – ShowChecked.
	/// </summary>
	enum class showWarnings
	{
		/// <summary>
		/// показывать только отмеченные предупреждения
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ShowChecked")] ShowChecked,
		ShowChecked,
		/// <summary>
		/// показывать все предупреждения
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ShowAll")] ShowAll,
		ShowAll,
		/// <summary>
		/// ничего не показывать
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ShowNothing")] ShowNothing
		ShowNothing
	};

	/// <summary>
	/// Сторона объекта.
	/// </summary>
	/// <remarks>! Значение Both возможно только при описании запретов размещения.</remarks>
	enum class side
	{
		/// <summary>
		/// верх
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Top")] Top,
		Top,
		/// <summary>
		/// низ
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Bottom")] Bottom,
		Bottom,
		/// <summary>
		/// обе стороны
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Both")] Both
		Both
	};

	/// <summary>
	/// Параметр области металлизации (полигона): состояние. Значение по умолчанию – Unpoured.
	/// </summary>
	enum class state
	{
		/// <summary>
		/// незалитая
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Unpoured")] Unpoured,
		Unpoured,
		/// <summary>
		/// залитая
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Poured")] Poured,
		Poured,
		/// <summary>
		/// залитая и зафиксированная
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Locked")] Locked
		Locked
	};

	/// <summary>
	/// Единица измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
	/// </summary>
	enum class time
	{
		/// <summary>
		/// пикосекунда
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ps")] ps,
		ps,
		/// <summary>
		/// фемтосекунда
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("fs")] fs,
		fs,
		/// <summary>
		/// наносекунда
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("ns")] ns,
		ns,
		/// <summary>
		/// микросекунда
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("us")] us
		us
	};

	/// <summary>
	/// Тип предопределённого атрибута компонента. Значение по умолчанию - RefDes
	/// </summary>
	enum class type
	{
		/// <summary>
		/// позиционное обозначение
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("RefDes")] RefDes,
		RefDes,
		/// <summary>
		/// PartName
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("PartName")] PartName
		PartName
	};

	/// <summary>
	/// Параметр стека контактной площадки: подключение к области металлизации (полигону). Значение по умолчанию – NoneConnect.
	/// </summary>
	enum class type_connectToCopper
	{
		/// <summary>
		/// тип подключения не задан(используются настройки полигона)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("NoneConnect")] NoneConnect,
		NoneConnect,
		/// <summary>
		/// прямое подключение 
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Direct")] Direct,
		Direct,
		/// <summary>
		/// подключение с помощью термобарьера
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Thermal")] Thermal
		Thermal
	};

	/// <summary>
	/// Тип обработки углов прямоугольной контактной площадки.
	/// </summary>
	enum class type_handling
	{
		/// <summary>
		/// без обработки
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("None")] None,
		None,
		/// <summary>
		/// скругление
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Rounding")] Rounding,
		Rounding,
		/// <summary>
		/// срез
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Chamfer")] Chamfer
		Chamfer
	};

	/// <summary>
	/// Тип стека контактных площадок. Значение по умолчанию – Through.
	/// </summary>
	enum class type_padstack
	{
		/// <summary>
		/// сквозной
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Through")] Through,
		Through,
		/// <summary>
		/// планарный
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("SMD")] SMD,
		SMD,
		/// <summary>
		/// монтажное отверстие
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("MountHole")] MountHole
		MountHole
	};

	/// <summary>
	/// Настройка вывода файлов Gerber, DXF, Drill: единицы измерения. Значение по умолчанию – mm.
	/// </summary>
	enum class units
	{
		/// <summary>
		/// миллиметр
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mm")] mm,
		mm,
		/// <summary>
		/// мил (тысячная дюйма)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("mil")] mil
		mil
	};

	/// <summary>
	/// Параметр правил выравнивания задержек: тип значений констант и допусков. Значение по умолчанию: Dist
	/// </summary>
	enum class valueType
	{
		/// <summary>
		/// длина
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Dist")] Dist,
		Dist,
		/// <summary>
		/// время
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Time")] Time
		Time
	};

	/// <summary>
	/// Параметр автоматической трассировки: форма проводников. 
	/// </summary>
	enum class wireShape
	{
		/// <summary>
		/// Polyline
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Polyline")] Polyline,
		Polyline,
		/// <summary>
		/// Arcs
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlEnum("Arcs")] Arcs
		Arcs
	};

//	#endregion Enumerations

//	#region Reference Types 
	/// <summary>
	/// базовый класс ссылок.
	/// </summary>
	class BaseRef : public std::enable_shared_from_this<BaseRef>
	{
		/// <summary>
		/// Имя объекта или ссылка на именованный объект.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _ReferenceName;
		std::wstring _ReferenceName;
	};

	/// <summary>
	/// Ссылка на атрибут.
	/// </summary>
	class AttributeRef : public BaseRef
	{

	protected:
		std::shared_ptr<AttributeRef> shared_from_this()
		{
			return std::static_pointer_cast<AttributeRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на тип слоя.
	/// </summary>
	class LayerTypeRef : public std::enable_shared_from_this<LayerTypeRef>
	{
		/// <summary>
		/// Тип слоя.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("type")] public layer_type _type;
		layer_type _type = static_cast<layer_type>(0);
	};

	/// <summary>
	/// Ссылка на группу слоёв.
	/// </summary>
	class LayerGroupRef : public BaseRef
	{

	protected:
		std::shared_ptr<LayerGroupRef> shared_from_this()
		{
			return std::static_pointer_cast<LayerGroupRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на слой.
	/// </summary>
	/// <remarks>! Если в дизайне определён только один слой с заданным именем, то тип слоя не указывается.</remarks>
	class LayerRef : public BaseRef
	{
		/// <summary>
		/// Тип слоя или ссылка на именованный cлой
		/// </summary>
		/// <remarks>В документации сказано ещё и про возможность установки типа, если имя слоя неуникально, в данный момент это отключено</remarks>
		// TODO:
		//   XmlAttribute("type", typeof(type_layer)),

	protected:
		std::shared_ptr<LayerRef> shared_from_this()
		{
			return std::static_pointer_cast<LayerRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на тип переходного отверстия.
	/// </summary>
	class ViastackRef : public BaseRef
	{

	protected:
		std::shared_ptr<ViastackRef> shared_from_this()
		{
			return std::static_pointer_cast<ViastackRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на стек контактных площадок.
	/// </summary>
	class NetRef : public BaseRef
	{

	protected:
		std::shared_ptr<NetRef> shared_from_this()
		{
			return std::static_pointer_cast<NetRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на группу компонентов.
	/// </summary>
	class CompGroupRef : public BaseRef
	{

	protected:
		std::shared_ptr<CompGroupRef> shared_from_this()
		{
			return std::static_pointer_cast<CompGroupRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на компонент на плате.
	/// </summary>
	class CompInstanceRef : public BaseRef
	{

	protected:
		std::shared_ptr<CompInstanceRef> shared_from_this()
		{
			return std::static_pointer_cast<CompInstanceRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на группу цепей.
	/// </summary>
	class NetGroupRef : public BaseRef
	{

	protected:
		std::shared_ptr<NetGroupRef> shared_from_this()
		{
			return std::static_pointer_cast<NetGroupRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на волновое сопротивление.
	/// </summary>
	class ImpedanceRef : public BaseRef
	{

	protected:
		std::shared_ptr<ImpedanceRef> shared_from_this()
		{
			return std::static_pointer_cast<ImpedanceRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на сигнал.
	/// </summary>
	class SignalRef : public BaseRef
	{

	protected:
		std::shared_ptr<SignalRef> shared_from_this()
		{
			return std::static_pointer_cast<SignalRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на группу сигналов..
	/// </summary>
	class SignalGroupRef : public BaseRef
	{

	protected:
		std::shared_ptr<SignalGroupRef> shared_from_this()
		{
			return std::static_pointer_cast<SignalGroupRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на дифференциальный сигнал.
	/// </summary>
	class DiffSignalRef : public BaseRef
	{

	protected:
		std::shared_ptr<DiffSignalRef> shared_from_this()
		{
			return std::static_pointer_cast<DiffSignalRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на контакт.
	/// </summary>
	class PinRef : public std::enable_shared_from_this<PinRef>
	{
		/// <summary>
		/// Имя компонента, используется для ссылки на компонент.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("compName")] public string _compName;
		std::wstring _compName;

		/// <summary>
		/// Имя контакта компонента, используется для ссылки.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("pinName")] public string _pinName;
		std::wstring _pinName;
	};

	/// <summary>
	/// Ссылка на контакт источника сигнала.
	/// </summary>
	class SourcePinRef : public PinRef
	{

	protected:
		std::shared_ptr<SourcePinRef> shared_from_this()
		{
			return std::static_pointer_cast<SourcePinRef>(PinRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на контакт приёмника сигнала.
	/// </summary>
	class ReceiverPinRef : public PinRef
	{

	protected:
		std::shared_ptr<ReceiverPinRef> shared_from_this()
		{
			return std::static_pointer_cast<ReceiverPinRef>(PinRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на стек контактных площадок.
	/// </summary>
	class PadstackRef : public BaseRef
	{

	protected:
		std::shared_ptr<PadstackRef> shared_from_this()
		{
			return std::static_pointer_cast<PadstackRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на стиль надписей.
	/// </summary>
	class TextStyleRef : public BaseRef
	{

	protected:
		std::shared_ptr<TextStyleRef> shared_from_this()
		{
			return std::static_pointer_cast<TextStyleRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на схемный компонент.
	/// </summary>
	class ComponentRef : public BaseRef
	{

	protected:
		std::shared_ptr<ComponentRef> shared_from_this()
		{
			return std::static_pointer_cast<ComponentRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на посадочное место.
	/// </summary>
	class FootprintRef : public BaseRef
	{

	protected:
		std::shared_ptr<FootprintRef> shared_from_this()
		{
			return std::static_pointer_cast<FootprintRef>(BaseRef::shared_from_this());
		}
	};

	/// <summary>
	/// Ссылка на вывод посадочного места.
	/// </summary>
	class PadRef : public std::enable_shared_from_this<PadRef>
	{
		/// <summary>
		/// Ссылка на имя компонента
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("compName")] public string _compName;
		std::wstring _compName;

		/// <summary>
		/// Номер контактной площадки (вывода) посадочного места.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("padNum", DataType = "int")] public int _padNum;
		int _padNum = 0;
	};
//	#endregion Reference Type

//	#region Coordinates

	class base_coordinat : public std::enable_shared_from_this<base_coordinat>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("x", DataType = "float")] public float _x;
		float _x = 0.0F;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("y", DataType = "float")] public float _y;
		float _y = 0.0F;

		void Shift(float x, float y);

		void UnitsConvert(dist in_units, dist out_units);
	};

	/// <summary>
	/// координаты точки, вершины.
	/// </summary>
	class Dot : public base_coordinat
	{

	protected:
		std::shared_ptr<Dot> shared_from_this()
		{
			return std::static_pointer_cast<Dot>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Центр круга (окружности), овала.
	/// </summary>
	class Center : public base_coordinat
	{

	protected:
		std::shared_ptr<Center> shared_from_this()
		{
			return std::static_pointer_cast<Center>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Начальная точка линии, дуги.
	/// </summary>
	class Start : public base_coordinat
	{

	protected:
		std::shared_ptr<Start> shared_from_this()
		{
			return std::static_pointer_cast<Start>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Средняя точка дуги.
	/// </summary>
	class Middle : public base_coordinat
	{

	protected:
		std::shared_ptr<Middle> shared_from_this()
		{
			return std::static_pointer_cast<Middle>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Конечная точка линии, дуги.
	/// </summary>
	class End : public base_coordinat
	{

	protected:
		std::shared_ptr<End> shared_from_this()
		{
			return std::static_pointer_cast<End>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Точка привязки объекта.
	/// </summary>
	class Org : public base_coordinat
	{

	protected:
		std::shared_ptr<Org> shared_from_this()
		{
			return std::static_pointer_cast<Org>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Cмещение точки привязки или объекта по осям x и y.
	/// </summary>
	class Shift : public base_coordinat
	{

	protected:
		std::shared_ptr<Shift> shared_from_this()
		{
			return std::static_pointer_cast<Shift>(base_coordinat::shared_from_this());
		}
	};

	/// <summary>
	/// Вытягивание по осям x и y.
	/// </summary>
	class Stretch : public base_coordinat
	{

	protected:
		std::shared_ptr<Stretch> shared_from_this()
		{
			return std::static_pointer_cast<Stretch>(base_coordinat::shared_from_this());
		}
	};

//	#endregion Coordinates

//	#region Segments
	class IBaseSegment
	{
	public:
		virtual void Shift(float x, float y) = 0;
		virtual void UnitsConvert(dist in_units, dist out_units) = 0;
	};

	/// <summary>
	/// Описание прямолинейного сегмента контура.
	/// </summary>
	class SegmentLine : public IBaseSegment
	{
		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание дугообразного сегмента контура.
	/// Дуга, задаётся центром. Обход против часовой стрелки.
	/// </summary>
	class SegmentArcCCW : public SegmentLine
	{
		/// <summary>
		/// Центр круга (окружности), овала.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
		std::shared_ptr<Center> _Center;

		void Shift(float x, float y);

		void UnitsConvert(dist in_units, dist out_units);

	protected:
		std::shared_ptr<SegmentArcCCW> shared_from_this()
		{
			return std::static_pointer_cast<SegmentArcCCW>(SegmentLine::shared_from_this());
		}
	};

	/// <summary>
	/// Описание дугообразного сегмента контура.
	/// Дуга, задаётся центром. Обход по часовой стрелки.
	/// </summary>
	class SegmentArcCW : public SegmentArcCCW
	{

	protected:
		std::shared_ptr<SegmentArcCW> shared_from_this()
		{
			return std::static_pointer_cast<SegmentArcCW>(SegmentArcCCW::shared_from_this());
		}
	};

	/// <summary>
	/// Описание дугообразного сегмента контура. 
	/// Дуга, задаётся углом. Отрицательный угол означает обход по часовой стрелке.
	/// </summary>
	class SegmentArcByAngle : public SegmentLine
	{
		/// <summary>
		/// Задаёт угол в градусах c точностью до тысячных долей.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
		float _angle = 0.0F;

	protected:
		std::shared_ptr<SegmentArcByAngle> shared_from_this()
		{
			return std::static_pointer_cast<SegmentArcByAngle>(SegmentLine::shared_from_this());
		}
	};

	/// <summary>
	/// Описание дугообразного сегмента контура.
	/// Дуга, задаётся тремя точками: начало, середина и конец.
	/// </summary>
	class SegmentArcByMiddle : public SegmentLine
	{
		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Middle")] public Middle _Middle;
		std::shared_ptr<Middle> _Middle;

		void Shift(float x, float y);

		void UnitsConvert(dist in_units, dist out_units);

	protected:
		std::shared_ptr<SegmentArcByMiddle> shared_from_this()
		{
			return std::static_pointer_cast<SegmentArcByMiddle>(SegmentLine::shared_from_this());
		}
	};
//	#endregion Segments

//	#region Figures
	/// <summary>
	/// Интерфейс BaseFigure создан для реализации удобного доступа к одинаковым методам разных объектов
	/// </summary>
	class IBaseFigure
	{
	public:
		virtual void UnitsConvert(dist in_units, dist out_units) = 0;
		virtual void Shift(float x, float y) = 0;
	};

		/// <summary>
		/// Дуга, заданная центром. Обход против часовой стрелки.
		/// </summary>
		class ArcCCW : public IBaseFigure
		{
		/// <summary>
		/// Центр круга (окружности), овала.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
		std::shared_ptr<Center> _Center;

		/// <summary>
		/// Начальная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
		std::shared_ptr<Start> _Start;

		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
		};

	/// <summary>
	/// Дуга, заданная центром. Обход по часовой стрелке.
	/// </summary>
	class ArcCW : public ArcCCW
	{

	protected:
		std::shared_ptr<ArcCW> shared_from_this()
		{
			return std::static_pointer_cast<ArcCW>(ArcCCW::shared_from_this());
		}
	};

	/// <summary>
	/// Дуга, заданная углом. Отрицательный угол означает обход по часовой стрелке.
	/// </summary>
	class ArcByAngle : public IBaseFigure
	{
		/// <summary>
		/// Задаёт угол в градусах c точностью до тысячных долей.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
		float _angle = 0.0F;

		/// <summary>
		/// Начальная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
		std::shared_ptr<Start> _Start;

		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Дуга, заданная тремя точками: начало, середина и конец.
	/// </summary>
	class ArcByMiddle : public IBaseFigure
	{
		/// <summary>
		/// Начальная точка линии, дуги.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
		std::shared_ptr<Start> _Start;

		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Middle")] public Middle _Middle;
		std::shared_ptr<Middle> _Middle;

		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание окружности (незалитого круга).
	/// </summary>
	class Circle : public IBaseFigure
	{
		/// <summary>
		/// Диаметр окружности, круга, овала.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("diameter", DataType = "float")] public float _diameter;
		float _diameter = 0.0F;

		/// <summary>
		/// Центр круга (окружности), овала.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
		std::shared_ptr<Center> _Center;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание линии.
	/// </summary>
	class Line : public IBaseFigure
	{
		/// <summary>
		/// Массив координат точек, вершин.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
		std::vector<std::shared_ptr<Dot>> _Dots;
		bool ShouldSerialize_Dots();

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание полилинии.
	/// </summary>
	class Polyline : public IBaseFigure
	{
		/// <summary>
		/// Начальная точка линии, дуги.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
		std::shared_ptr<Start> _Start;

		/// <summary>
		/// Сегменты.
		/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SegmentLine", typeof(SegmentLine)), XmlElement("SegmentArcByAngle", typeof(SegmentArcByAngle)), XmlElement("SegmentArcCCW", typeof(SegmentArcCCW)), XmlElement("SegmentArcCW", typeof(SegmentArcCW)), XmlElement("SegmentArcByMiddle", typeof(SegmentArcByMiddle))] public List<Object> _Segments;
		std::vector<std::any> _Segments;
		bool ShouldSerialize_Segments();
		void Shift(float x, float y) override;
		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание незалитого контура.
	/// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
	/// </summary>
	class Contour : public Polyline
	{

	protected:
		std::shared_ptr<Contour> shared_from_this()
		{
			return std::static_pointer_cast<Contour>(Polyline::shared_from_this());
		}
	};

	/// <summary>
	/// Описание незалитого прямоугольника. Указываются верхняя левая и правая нижняя вершины
	/// </summary>
	class Rect : public Line
	{

	protected:
		std::shared_ptr<Rect> shared_from_this()
		{
			return std::static_pointer_cast<Rect>(Line::shared_from_this());
		}
	};

	/// <summary>
	/// Описание залитого контура.
	/// Если конечная точка последнего сегмента не совпадает с начальной точкой контура, контур замыкается линейным сегментом.
	/// </summary>
	class FilledContour : public Polyline
	{

	protected:
		std::shared_ptr<FilledContour> shared_from_this()
		{
			return std::static_pointer_cast<FilledContour>(Polyline::shared_from_this());
		}
	}; ///TODO: требует уточнения

	/// <summary>
	/// Описание круга.
	/// </summary>
	class FilledCircle : public Circle
	{

	protected:
		std::shared_ptr<FilledCircle> shared_from_this()
		{
			return std::static_pointer_cast<FilledCircle>(Circle::shared_from_this());
		}
	};

	/// <summary>
	/// Описание залитого прямоугольника.
	/// </summary>
	class FilledRect : public Rect
	{

	protected:
		std::shared_ptr<FilledRect> shared_from_this()
		{
			return std::static_pointer_cast<FilledRect>(Rect::shared_from_this());
		}
	};

	/// <summary>
	/// Описание многоугольника.
	/// Тег поддерживается, но является устаревшим.Следует использовать тег FilledContour.
	/// </summary>
	class Polygon : public Line
	{

	protected:
		std::shared_ptr<Polygon> shared_from_this()
		{
			return std::static_pointer_cast<Polygon>(Line::shared_from_this());
		}
	};

	/// <summary>
	/// Описание дугообразного сегмента проводника (дуга по часовой стрелке).
	/// </summary>
	/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
	class TrackArcCW : public IBaseFigure
	{
		/// <summary>
		/// Центр круга (окружности), овала.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Center")] public Center _Center;
		std::shared_ptr<Center> _Center;

		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		/// <summary>
		/// Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("serpRef")] public string _serpRef;
		std::wstring _serpRef;

		void Shift(float x, float y) override;
		void UnitsConvert(dist in_units, dist out_units) override;
	};

	/// <summary>
	/// Описание дугообразного сегмента проводника (дуга против часовой стрелки).
	/// </summary>
	/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
	class TrackArc : public TrackArcCW
	{

	protected:
		std::shared_ptr<TrackArc> shared_from_this()
		{
			return std::static_pointer_cast<TrackArc>(TrackArcCW::shared_from_this());
		}
	};

	/// <summary>
	/// Описание прямолинейного сегмента проводника.
	/// </summary>
	/// <remarks>Начальная точка сегмента определяется по предыдущему сегменту или по тегу Start, заданному в SubWire. ! Если сегмент принадлежит змейке, указывается ссылка на змейку serpRef.</remarks>
	class TrackLine : public IBaseFigure
	{
		/// <summary>
		/// Конечная точка линии, дуги.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("End")] public End _End;
		std::shared_ptr<End> _End;

		/// <summary>
		/// Ссылка на змейку. Строка должна содержать идентификатор описанной змейки Serpent.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("serpRef")] public string _serpRef;
		std::wstring _serpRef;

		void Shift(float x, float y) override;

		void UnitsConvert(dist in_units, dist out_units) override;
	};

//	#endregion Figures 

//	#region Rules area
	/// <summary>
	/// Устанавливает область действия правила: все слои.
	/// </summary>
	class AllLayers : public std::enable_shared_from_this<AllLayers>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayers")] public string _AllLayers;
		std::wstring _AllLayers;
	};

	/// <summary>
	/// Устанавливает область действия правила: все компоненты.
	/// </summary>
	class AllComps : public std::enable_shared_from_this<AllComps>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllComps")] public string _AllComps;
		std::wstring _AllComps;
	};

	/// <summary>
	/// Устанавливает область действия правила: все цепи.
	/// </summary>
	class AllNets : public std::enable_shared_from_this<AllNets>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllNets")] public string _AllNets;
		std::wstring _AllNets;
	};
	/// <summary>
	/// Устанавливает область действия правила: все внутренние слои.
	/// </summary>
	class AllLayersInner : public std::enable_shared_from_this<AllLayersInner>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayersInner")] public string _AllLayersInner;
		std::wstring _AllLayersInner;
	};

	/// <summary>
	/// Устанавливает область действия правила: все внутренние сигнальные слои.
	/// </summary>
	class AllLayersInnerSignal : public std::enable_shared_from_this<AllLayersInnerSignal>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayersInnerSignal")] public string _AllLayersInnerSignal;
		std::wstring _AllLayersInnerSignal;
	};

	/// <summary>
	/// Устанавливает область действия правила: все сигнальные слои.
	/// </summary>
	class AllLayersSignal : public std::enable_shared_from_this<AllLayersSignal>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayersSignal")] public string _AllLayersSignal;
		std::wstring _AllLayersSignal;
	};

	/// <summary>
	/// Устанавливает область действия правила: все внешние слои.
	/// </summary>
	class AllLayersOuter : public std::enable_shared_from_this<AllLayersOuter>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayersOuter")] public string _AllLayersOuter;
		std::wstring _AllLayersOuter;
	};

	/// <summary>
	/// Устанавливает доступные типы переходных отверстий для правила: все типы.
	/// </summary>
	class AllViastacks : public std::enable_shared_from_this<AllViastacks>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllViastacks")] public string _AllViastacks;
		std::wstring _AllViastacks;
	};

	/// <summary>
	/// Устанавливает доступные типы переходных отверстий для правила: все сквозные типы.
	/// </summary>
	class AllViastacksThrough : public std::enable_shared_from_this<AllViastacksThrough>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllViastacksThrough")] public string _AllViastacksThrough;
		std::wstring _AllViastacksThrough;
	};

	/// <summary>
	/// Устанавливает доступные типы переходных отверстий для правила: все несквозные типы.
	/// </summary>
	class AllViastacksNotThrough : public std::enable_shared_from_this<AllViastacksNotThrough>
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllViastacksNotThrough")] public string _AllViastacksNotThrough;
		std::wstring _AllViastacksNotThrough;
	};
//	#endregion Rules area

//	#region Thermal Detail Text ObjectSignal

	/// <summary>
	/// Описание термобарьера.
	/// </summary>
	class Thermal : public std::enable_shared_from_this<Thermal>
	{
		/// <summary>
		/// Параметр термобарьера: число спиц.! В TopoR поддерживается только одно значение – 4.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("spokeNum", DataType = "int")] public int _spokeNum;
		int _spokeNum = 0;

		/// <summary>
		/// Параметр термобарьера: минимальное число спиц.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("minSpokeNum", DataType = "int")] public int _minSpokeNum;
		int _minSpokeNum = 0;

		/// <summary>
		/// Задаёт угол в градусах c точностью до тысячных долей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
		float _angle = 0.0F;

		/// <summary>
		/// Параметр термобарьера: ширина спицы.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("spokeWidth", DataType = "float")] public float _spokeWidth;
		float _spokeWidth = 0.0F;

		/// <summary>
		/// Параметр термобарьера: зазор между контактной площадкой и областью металлизации.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("backoff", DataType = "float")] public float _backoff;
		float _backoff = 0.0F;

		void UnitsConvert(dist in_units, dist out_units);
	};

	/// <summary>
	/// Описание детали.
	/// </summary>
	class Detail : public std::enable_shared_from_this<Detail>
	{
		/// <summary>
		/// Толщина линии.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
		float _lineWidth = 0.0F;

		/// <summary>
		/// Ссылка на слой.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
		std::shared_ptr<LayerRef> _LayerRef;

		/// <summary>
		/// Описание фигуры.
		/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Line", typeof(Line)), XmlElement("Circle", typeof(Circle)), XmlElement("Rect", typeof(Rect)), XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("Polyline", typeof(Polyline)), XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure;
		std::any _Figure;

		void Shift(float x, float y);

		void UnitsConvert(dist in_units, dist out_units);
	};

	/// <summary>
	/// Описание надписи.
	/// </summary>
	class Text : public std::enable_shared_from_this<Text>
	{
		/// <summary>
		/// Параметр надписи: текст надписи.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("text")] public string _text;
		std::wstring _text;

		/// <summary>
		/// Параметр надписей (ярлыков): способ выравнивания текста.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("align")] public align _align;
		align _align = static_cast<align>(0);

		/// <summary>
		/// Задаёт угол в градусах c точностью до тысячных долей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
		float _angle = 0.0F;

		/// <summary>
		/// Параметр надписей и ярлыков: зеркальность отображения.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("mirror")] public Bool _mirror;
		Bool _mirror = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _mirrorSpecified
		bool getMirrorSpecified() const;

		/// <summary>
		/// Ссылка на слой.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
		std::shared_ptr<LayerRef> _LayerRef;

		/// <summary>
		/// Ссылка на стиль надписей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef;
		std::shared_ptr<TextStyleRef> _TextStyleRef;

		/// <summary>
		/// Точка привязки объекта.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
		std::shared_ptr<Org> _Org;

		void Shift(float x, float y);
		/// <summary>
		/// TODO: конвертировать текстовые стили по ссылке
		/// </summary>
		/// <param name="in_units"></param>
		/// <param name="out_units"></param>
		void UnitsConvert(dist in_units, dist out_units);
	};

	/// <summary>
	/// Сигналы воздействия правила
	/// </summary>
	class ObjectSignal : public std::enable_shared_from_this<ObjectSignal>
	{
	public:
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SignalRef", typeof(SignalRef)), XmlElement("DiffSignalRef", typeof(DiffSignalRef)), XmlElement("SignalGroupRef", typeof(SignalGroupRef)),] public Object _Refs;
		std::any _Refs;
	};
//	#endregion

	/// <summary>
	/// Различные сервисные функции
	/// </summary>
	class Ut final
	{
		/// <summary>
		/// Конвертация единиц измерения
		/// </summary>
		/// <param name="value">значение</param>
		/// <param name="in_units">текущие единицы измерения</param>
		/// <param name="out_units">выходные единицы измерения</param>
		/// <returns>Возвращает сконвертированное значение</returns>
	public:
		static float UnitsConvert(float value, dist in_units, dist out_units);
	};
}
