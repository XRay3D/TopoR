#pragma once

#include "Commons.h"
#include <string>
#include <vector>
#include <any>
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */


namespace TopoR_PCB_Classes
{
	/// <summary>
	/// Раздел «Соединения на плате».
	/// </summary>
	/// <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
	class Connectivity : public std::enable_shared_from_this<Connectivity>
	{
		/// <summary>
		/// Переходное отверстие на плате.
		/// </summary>
	public:
		class Via : public std::enable_shared_from_this<Via>
		{
			/// <summary>
			/// Признак фиксации.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fixed")] public Bool _fixed;
			Bool _fixed = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _fixedSpecified
			bool getFixedSpecified() const;

			/// <summary>
			/// Ссылка на тип переходного отверстия.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ViastackRef")] public ViastackRef _ViastackRef;
			std::shared_ptr<ViastackRef> _ViastackRef;

			/// <summary>
			/// Ссылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
			std::shared_ptr<NetRef> _NetRef;

			/// <summary>
			/// Точка привязки объекта.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
			std::shared_ptr<Org> _Org;
		};

		/// <summary>
		/// Описание змейки.
		/// </summary>
		/// <remarks>! Проводники, реализующие змейку, описываются в секции Wires (см. описание раздела Connectivity)</remarks>
	public:
		class Serpent : public std::enable_shared_from_this<Serpent>
		{
			/// <summary>
			/// Идентификатор неименованных объектов.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("id")] public string _id;
			std::wstring _id;

			/// <summary>
			/// Параметр змейки: требуемая длина.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("Count", DataType ="float")] public float _Count;
			float _Count = 0.0F;

			/// <summary>
			/// Параметр змейки: зазор между соседними изломами.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("gap", DataType = "float")] public float _gap;
			float _gap = 0.0F;

			/// <summary>
			/// Параметр змейки: высота h1 (см. описание змейки Serpent).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("h1", DataType = "float")] public float _h1;
			float _h1 = 0.0F;

			/// <summary>
			/// Параметр змейки: высота h2 (см. описание змейки Serpent).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("h2", DataType = "float")] public float _h2;
			float _h2 = 0.0F;

			/// <summary>
			/// Параметр змейки: высота h3 (см. описание змейки Serpent).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("h3", DataType = "float")] public float _h3;
			float _h3 = 0.0F;

			/// <summary>
			/// Параметр змейки: высота h4 (см. описание змейки Serpent).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("h4", DataType = "float")] public float _h4;
			float _h4 = 0.0F;
		};

		/// <summary>
		/// Описание застёгнутой пары проводников.
		/// </summary>
		/// <remarks>! Сегменты(Track) описывают осевую линию пары.Форма проводников пары рассчитывается автоматически.</remarks> 
	public:
		class ZippedWire : public std::enable_shared_from_this<ZippedWire>
		{
			/// <summary>
			/// Идентификатор неименованных объектов.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("id")] public string _id;
			std::wstring _id;

			/// <summary>
			/// Признак фиксации.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fixed")] public Bool _fixed;
			Bool _fixed = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _fixedSpecified
			bool getFixedSpecified() const;

			/// <summary>
			/// Ссылка на слой.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
			std::shared_ptr<LayerRef> _LayerRef;

			/// <summary>
			/// Ссылка на дифференциальный сигнал.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DiffSignalRef")] public DiffSignalRef _DiffSignalRef;
			std::shared_ptr<DiffSignalRef> _DiffSignalRef;

			/// <summary>
			/// Начальная точка линии, дуги.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
			std::shared_ptr<Start> _Start;

			/// <summary>
			/// Описание(я) сегмента проводника.
			/// </summary>
			/// <remarks>! В случае отсутствия - предупреждение. Весь ZippedWire будет проигнорирован.</remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TrackLine", typeof(TrackLine)), XmlElement("TrackArc", typeof(TrackArc)), XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks;
			std::vector<std::any> _Tracks;
			bool ShouldSerialize_Tracks();
		};

		/// <summary>
		/// Описание проводника.
		/// </summary>
	public:
		class Wire : public std::enable_shared_from_this<Wire>
		{
			/// <summary>
			/// Описание части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
			/// </summary>
			/// <remarks>! Атрибут zipwireRef (ссылка на застёгнутую пару проводников) используется, если описываемая часть проводника входит в застёгнутую пару проводников ZippedWire (см. пример описания проводника дифференциальной пары).</remarks>
		public:
			class Subwire : public std::enable_shared_from_this<Subwire>
			{
				/// <summary>
				/// Описание «капельки» четырёхугольником. Первая вершина соответствует точке привязки контакта (переходного отверстия). Остальные вершины описывают контур четырёхугольника против часовой стрелки.
				/// </summary>
				/// <remarks> ! TopoR при импорте игнорирует информацию о капельках.</remarks>
			public:
				class Teardrop : public std::enable_shared_from_this<Teardrop>
				{
					/// <summary>
					/// координаты точки, вершины.
					/// </summary>
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
					std::vector<std::shared_ptr<Dot>> _Dots;
					bool ShouldSerialize_Dots();
				};

				/// <summary>
				/// Признак фиксации.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fixed")] public Bool _fixed;
				Bool _fixed = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _fixedSpecified
				bool getFixedSpecified() const;

				/// <summary>
				/// Ширина проводника.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("width", DataType = "float")] public float _width;
				float _width = 0.0F;

				/// <summary>
				/// Ссылка на застёгнутую пару проводников. Строка должна содержать идентификатор описанной застёгнутой пары проводников ZippedWire.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("zipwireRef")] public string _zipwireRef;
				std::wstring _zipwireRef;

				/// <summary>
				/// Описание «капелек» для Subwire.
				/// </summary>
				/// <remarks>От KilkennyCat: сделал как массив, в спецификации не так, но так удобней</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Teardrops")][XmlArrayItem("Teardrop")] public List<Teardrop> _Teardrops;
				std::vector<std::shared_ptr<Teardrop>> _Teardrops;
				bool ShouldSerialize_Teardrops();
				/// <summary>
				/// Начальная точка линии, дуги.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Start")] public Start _Start;
				std::shared_ptr<Start> _Start;

				/// <summary>
				/// Описание(я) сегмента проводника.
				/// </summary>
				/// <remarks>! В случае отсутствия - предупреждение. Весь проводник будет проигнорирован.</remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TrackLine", typeof(TrackLine)), XmlElement("TrackArc", typeof(TrackArc)), XmlElement("TrackArcCW", typeof(TrackArcCW))] public List<Object> _Tracks;
				std::vector<std::any> _Tracks;
				bool ShouldSerialize_Tracks();
			};

			/// <summary>
			/// Ссылка на слой.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
			std::shared_ptr<LayerRef> _LayerRef;

			/// <summary>
			/// Ссылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
			std::shared_ptr<NetRef> _NetRef;

			/// <summary>
			/// Части проводника (последовательность сегментов с одной шириной и одинаковым признаком фиксации).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Subwire")] public List<Subwire> _Subwires;
			std::vector<std::shared_ptr<Subwire>> _Subwires;
			bool ShouldSerialize_Subwires();
		};

		/// <summary>
		/// Описание заливаемой области металлизации (полигона).
		/// </summary>
		/// <remarks>! Заливка полигона линиями (Fill) записывается только для других САПР. TopoR при импорте её игнорирует. Сплошная заливка (fillType = Solid) не записывается.</remarks>
	public:
		class Copper_Connectivity : public std::enable_shared_from_this<Copper_Connectivity>
		{
			/// <summary>
			/// Описание термобарьера для подключения контактных площадок к области металлизации.
			/// </summary>
		public:
			class ThermalPad : public std::enable_shared_from_this<ThermalPad>
			{
				/// <summary>
				/// Описание термобарьера.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Thermal")] public Thermal _Thermal;
				std::shared_ptr<Thermal> _Thermal;
			};

			/// <summary>
			/// Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
			/// </summary>
		public:
			class ThermalVia : public std::enable_shared_from_this<ThermalVia>
			{
				/// <summary>
				/// Описание термобарьера.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Thermal")] public Thermal _Thermal;
				std::shared_ptr<Thermal> _Thermal;
			};

			/// <summary>
			/// Описание контура заливаемой области металлизации.
			/// </summary>
		public:
			class Shape_Copper : public std::enable_shared_from_this<Shape_Copper>
			{
				/// <summary>
				/// Описание залитой фигуры.
				/// </summary>
			public:
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("FilledContour", typeof(FilledContour))] public Object _FilledFigure;
				std::any _FilledFigure;
			};

			/// <summary>
			/// Описание островка области металлизации.
			/// </summary>
		public:
			class Island : public std::enable_shared_from_this<Island>
			{
				/// <summary>
				/// Описание спицы термобарьера, присутствующего на плате
				/// </summary>
			public:
				class ThermalSpoke : public std::enable_shared_from_this<ThermalSpoke>
				{
					/// <summary>
					/// Толщина линии.
					/// </summary>
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
					float _lineWidth = 0.0F;

					/// <summary>
					/// Описания координат точек, вершин.
					/// </summary>
					/// <remarks>! В случае отсутствия - весь ThermalSpoke будет проигнорирован.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Dot")] public List<Dot> _Dots;
					std::vector<std::shared_ptr<Dot>> _Dots;
					bool ShouldSerialize_Dots();
				};

				/// <summary>
				/// Описание многоугольника.
				/// </summary>
			public:
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Polygon", typeof(Polygon)), XmlElement("FilledContour", typeof(FilledContour))] public Object _Polygon;
				std::any _Polygon;

				/// <summary>
				/// Вырезы в островке области металлизации.
				/// </summary>
				/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Voids")][XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids;
				std::vector<std::any> _Voids;

				/// <summary>
				/// Описание спиц термобарьеров, присутствующих на плате
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ThermalSpoke")] public List<ThermalSpoke> _ThermalSpokes;
				std::vector<std::shared_ptr<ThermalSpoke>> _ThermalSpokes;
				bool ShouldSerialize_ThermalSpokes();
			};

			/// <summary>
			/// Параметр области металлизации (полигона): приоритет заливки.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("priority", DataType ="int")] public int _priority;
			int _priority = 0;

			/// <summary>
			/// Параметр области металлизации (полигона): использовать указанный зазор.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("useBackoff")] public Bool _useBackoff;
			Bool _useBackoff = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _useBackoffSpecified
			bool getUseBackoffSpecified() const;

			/// <summary>
			/// Параметр области металлизации (полигона): зазор до области металлизации.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("backoff", DataType ="float")] public float _backoff;
			float _backoff = 0.0F;

			/// <summary>
			/// Параметр области металлизации (полигона) стека: подключение контактных площадок.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("connectPad")] public connectPad _connectPad;
			connectPad _connectPad = static_cast<connectPad>(0);

			/// <summary>
			/// Параметр области металлизации (полигона): подключение площадок переходных отверстий.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("connectVia")] public connectVia _connectVia;
			connectVia _connectVia = static_cast<connectVia>(0);

			/// <summary>
			/// Толщина линии.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
			float _lineWidth = 0.0F;

			/// <summary>
			/// Параметр области металлизации (полигона): зазор между линиями штриховки.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("lineClr", DataType = "float")] public float _lineClr;
			float _lineClr = 0.0F;

			/// <summary>
			/// Параметр области металлизации (полигона): минимальная площадь островка.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("minSquare", DataType = "float")] public float _minSquare;
			float _minSquare = 0.0F;

			/// <summary>
			/// Параметр области металлизации (полигона): точность аппроксимации контура.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("precision")] public precision _precision;
			precision _precision = static_cast<precision>(0);

			/// <summary>
			/// Параметр области металлизации (полигона): удалять неподключенные островки.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("deleteUnconnected")] public Bool _deleteUnconnected;
			Bool _deleteUnconnected = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _deleteUnconnectedSpecified
			bool getDeleteUnconnectedSpecified() const;

			/// <summary>
			/// Параметр области металлизации (полигона): состояние.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("state")] public state _state;
			state _state = static_cast<state>(0);

			/// <summary>
			/// Параметр области металлизации (полигона): тип заливки.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fillType")] public fillType _fillType;
			fillType _fillType = static_cast<fillType>(0);

			/// <summary>
			/// Ссылка на слой.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
			std::shared_ptr<LayerRef> _LayerRef;

			/// <summary>
			/// Ссылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
			std::shared_ptr<NetRef> _NetRef;

			/// <summary>
			/// Описание термобарьера для подключения контактных площадок к области металлизации.
			/// </summary>
			/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ThermalPad")] public ThermalPad _ThermalPad;
			std::shared_ptr<ThermalPad> _ThermalPad;

			/// <summary>
			/// Описание термобарьера для подключения площадок переходных отверстий к области металлизации.
			/// </summary>
			/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ThermalVia")] public ThermalVia _ThermalVia;
			std::shared_ptr<ThermalVia> _ThermalVia;

			/// <summary>
			/// Описание контура заливаемой области металлизации..
			/// </summary>
			/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Shape")] public Shape_Copper _Shape;
			std::shared_ptr<Shape_Copper> _Shape;

			/// <summary>
			/// Вырезы в областях металлизации (полигонах) заданные пользователем.
			/// </summary>
			/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Voids")][XmlArrayItem("FilledCircle", typeof(FilledCircle)), XmlArrayItem("FilledRect", typeof(FilledRect)), XmlArrayItem("Polygon", typeof(Polygon)), XmlArrayItem("FilledContour", typeof(FilledContour))] public List<Object> _Voids;
			std::vector<std::any> _Voids;

			/// <summary>
			/// Островки области металлизации.
			/// </summary>
			/// <remarks>! В случае отсутствия - критическая ошибка. Обязан быть пустой тэг.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Islands")][XmlArrayItem("Island")] public List<Island> _Islands;
			std::vector<std::shared_ptr<Island>> _Islands;

			/// <summary>
			/// Заливка областей металлизации (полигонов) линиями.
			/// </summary>
			/// <remarks>! TopoR при импорте игнорирует эту информацию и строит заливку заново.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Fill")][XmlArrayItem("Line")] public List<Line> _Fill_lines;
			std::vector<std::shared_ptr<Line>> _Fill_lines;
			bool ShouldSerialize_Fill_lines();
		};

		/// <summary>
		/// Описание незаливаемой области металлизации.
		/// </summary>
	public:
		class NonfilledCopper : public std::enable_shared_from_this<NonfilledCopper>
		{
			/// <summary>
			/// Описание контура незаливаемой области металлизации.
			/// </summary>
		public:
			class Shape_NonfilledCopper : public std::enable_shared_from_this<Shape_NonfilledCopper>
			{
				/// <summary>
				/// Описание фигуры.
				/// </summary>
			public:
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Circle", typeof(Circle)), XmlElement("Line", typeof(Line)), XmlElement("Polyline", typeof(Polyline)), XmlElement("Rect", typeof(Rect)), XmlElement("Contour", typeof(Contour))] public Object _FigureContPoliline;
				std::any _FigureContPoliline;
			};

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
			/// Ссылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
			std::shared_ptr<NetRef> _NetRef;

			/// <summary>
			/// Описание контура незаливаемой области металлизации.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Shape")] public Shape_NonfilledCopper _Shape;
			std::shared_ptr<Shape_NonfilledCopper> _Shape;
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::wstring _version;

		/// <summary>
		/// Переходные отверстия на плате.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Vias")][XmlArrayItem("Via")] public List<Via> _Vias;
		std::vector<std::shared_ptr<Via>> _Vias;
		bool ShouldSerialize_Vias();
		/// <summary>
		/// Змейки
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Serpents")][XmlArrayItem("Serpent")] public List<Serpent> _Serpents;
		std::vector<std::shared_ptr<Serpent>> _Serpents;
		bool ShouldSerialize_Serpents();
		/// <summary>
		/// Застёгнутые пары проводников.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ZippedWires")][XmlArrayItem("ZippedWire")] public List<ZippedWire> _ZippedWires;
		std::vector<std::shared_ptr<ZippedWire>> _ZippedWires;
		bool ShouldSerialize_ZippedWires();
		/// <summary>
		/// Проводники.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Wires")][XmlArrayItem("Wire")] public List<Wire> _Wires;
		std::vector<std::shared_ptr<Wire>> _Wires;
		bool ShouldSerialize_Wires();
		/// <summary>
		/// Oбласти металлизации (полигонов).
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Connectivity> _Coppers;
		std::vector<std::shared_ptr<Copper_Connectivity>> _Coppers;
		bool ShouldSerialize_Coppers();
		/// <summary>
		/// Незаливаемые области металлизации.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("NonfilledCoppers")][XmlArrayItem("NonfilledCopper")] public List<NonfilledCopper> _NonfilledCoppers;
		std::vector<std::shared_ptr<NonfilledCopper>> _NonfilledCoppers;
		bool ShouldSerialize_NonfilledCoppers();


		/************************************************************************
		 * Здесь находятся функции для работы с элементами класса Connectivity. *
		 * Они не являются частью формата TopoR PCB.                            *
		 * **********************************************************************/


		/************************************************************************/
	};
}
