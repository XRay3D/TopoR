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
	/// Раздел «Правила».
	/// </summary>
	/// <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
	class Rules : public std::enable_shared_from_this<Rules>
	{
		/// <summary>
		/// Описание правила ширины проводников.
		/// </summary>
	public:
		class WidthOfWires : public std::enable_shared_from_this<WidthOfWires>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Параметр правила ширины проводников: минимальная ширина проводника.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("widthMin", DataType = "float")] public float _widthMin;
			float _widthMin = 0.0F;

			/// <summary>
			/// Параметр правила ширины проводников: номинальная ширина проводника.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("widthNom", DataType = "float")] public float _widthNom;
			float _widthNom = 0.0F;

			/// <summary>
			/// Ссылка на слои. См. также _LayersRefs
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
			std::any _LayersRef;
			/// <summary>
			/// Ссылка на слои. См. также _LayersRef
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
			std::vector<std::shared_ptr<LayerRef>> _LayersRefs;
			bool ShouldSerialize_LayersRefs();
			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets))] public List<Object> _ObjectsAffected;
			std::vector<std::any> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
		};

		/// <summary>
		/// Описание правила зазоров между цепями.
		/// </summary>
	public:
		class ClearanceNetToNet : public std::enable_shared_from_this<ClearanceNetToNet>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Параметр правила зазоров между цепями: минимальный зазор.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("clrnMin", DataType = "float")] public float _clrnMin;
			float _clrnMin = 0.0F;

			/// <summary>
			/// Параметр правила зазоров между цепями: номинальный зазор.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("clrnNom", DataType = "float")] public float _clrnNom;
			float _clrnNom = 0.0F;

			/// <summary>
			/// Ссылка на слои. См. также _LayersRefs
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
			std::any _LayersRef;
			/// <summary>
			/// Ссылка на слои. См. также _LayersRef
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
			std::vector<std::shared_ptr<LayerRef>> _LayersRefs;
			bool ShouldSerialize_LayersRefs();
			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets)), XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
			std::vector<std::any> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
		};

		/// <summary>
		/// Описание правила зазоров между компонентами.
		/// </summary>
	public:
		class ClearanceCompToComp : public std::enable_shared_from_this<ClearanceCompToComp>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Параметр правила зазоров между цепями: минимальный зазор.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("clrn", DataType = "float")] public float _clrn;
			float _clrn = 0.0F;

			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("ComponentRef", typeof(ComponentRef)), XmlArrayItem("CompGroupRef", typeof(CompGroupRef)), XmlArrayItem("AllComps", typeof(AllComps))] public List<Object> _ObjectsAffected;
			std::vector<std::any> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
		};

		/// <summary>
		/// Описание зазоров до края платы.
		/// </summary>
	public:
		class RulesClearancesToBoard : public std::enable_shared_from_this<RulesClearancesToBoard>
		{
			/// <summary>
			/// Устанавливает зазор от проводников до края платы.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("wires", DataType = "float")] public float _clrn;
			float _clrn = 0.0F;

			/// <summary>
			/// Устанавливает зазор от компонентов до края платы.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("comps", DataType = "float")] public float _comps;
			float _comps = 0.0F;
		};

		/// <summary>
		/// Описание правила назначения цепям стеков переходных отверстий.
		/// </summary>
	public:
		class ViastacksOfNets : public std::enable_shared_from_this<ViastacksOfNets>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets)), XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
			std::vector<std::any> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
			/// <summary>
			/// Назначенные типы переходных отверстий.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Viastacks")][XmlArrayItem("AllViastacks", typeof(AllViastacks)), XmlArrayItem("AllViastacksThrough", typeof(AllViastacksThrough)), XmlArrayItem("AllViastacksNotThrough", typeof(AllViastacksNotThrough)), XmlArrayItem("ViastackRef", typeof(ViastackRef))] public List<Object> _Viastacks;
			std::vector<std::any> _Viastacks;
			bool ShouldSerialize_Viastacks();
		};

		/// <summary>
		/// Описание правила назначения цепям опорных слоёв.
		/// </summary>
	public:
		class PlaneLayerNets : public std::enable_shared_from_this<PlaneLayerNets>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Ссылка на слои. См. также _LayersRefs
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
			std::any _LayersRef;
			/// <summary>
			/// Ссылка на слои. См. также _LayersRef
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
			std::vector<std::shared_ptr<LayerRef>> _LayersRefs;
			bool ShouldSerialize_LayersRefs();
			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef")] public List<NetRef> _ObjectsAffected;
			std::vector<std::shared_ptr<NetRef>> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
		};

		/// <summary>
		/// Описание правила назначения цепям сигнальных слоёв.
		/// </summary>
	public:
		class SignalLayerNets : public std::enable_shared_from_this<SignalLayerNets>
		{
			/// <summary>
			/// Флаг применения правила.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("enabled")] public Bool _enabled;
			Bool _enabled = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _enabledSpecified
			bool getEnabledSpecified() const;

			/// <summary>
			/// Ссылка на слои. См. также _LayersRefs
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
			std::any _LayersRef;
			/// <summary>
			/// Ссылка на слои. См. также _LayersRef
			/// </summary>
			/// <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
			std::vector<std::shared_ptr<LayerRef>> _LayersRefs;
			bool ShouldSerialize_LayersRefs();
			/// <summary>
			/// Объекты воздействия правила.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef))] public List<Object> _ObjectsAffected;
			std::vector<std::any> _ObjectsAffected;
			bool ShouldSerialize_ObjectsAffected();
		};

		/// <summary>
		/// Свойства цепи.
		/// </summary>
	public:
		class NetProperty : public std::enable_shared_from_this<NetProperty>
		{
			/// <summary>
			/// Свойство цепи: гибкая фиксация.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("flexfix")] public Bool _flexfix;
			Bool _flexfix = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _flexfixSpecified
			bool getFlexfixSpecified() const;

			/// <summary>
			/// Свойство цепи: флаг трассировки для автоматического трассировщика.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("route")] public Bool _route;
			Bool _route = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _routeSpecified
			bool getRouteSpecified() const;

			/// <summary>
			/// Ссылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public List<NetRef> _NetRefs;
			std::vector<std::shared_ptr<NetRef>> _NetRefs;
			bool ShouldSerialize_NetRefs();
		};

		/// <summary>
		/// Настройки подключения к углам прямоугольных контактных площадок.
		/// </summary>
	public:
		class PadConnectSettings : public std::enable_shared_from_this<PadConnectSettings>
		{
			/// <summary>
			/// Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("mode")] public mode_PadConnectSettings _mode;
			mode_PadConnectSettings _mode = static_cast<mode_PadConnectSettings>(0);

			/// <summary>
			/// Ссылки на стеки контактных площадок.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadstackRef")] public List<PadstackRef> _PadstackRefs;
			std::vector<std::shared_ptr<PadstackRef>> _PadstackRefs;
			bool ShouldSerialize_PadstackRefs();
			/// <summary>
			/// Ссылки на контакты.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PinRef")] public List<PinRef> _PinRefs;
			std::vector<std::shared_ptr<PinRef>> _PinRefs;
			bool ShouldSerialize_PinRefs();
			/// <summary>
			/// Ссылки на выводы посадочных мест.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadRef")] public List<PadRef> _PadRefs;
			std::vector<std::shared_ptr<PadRef>> _PadRefs;
			bool ShouldSerialize_PadRefs();
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::wstring _version;

		/// <summary>
		/// Правила ширин проводников.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesWidthOfWires")][XmlArrayItem("WidthOfWires")] public List<WidthOfWires> _RulesWidthOfWires;
		std::vector<std::shared_ptr<WidthOfWires>> _RulesWidthOfWires;
		bool ShouldSerialize_RulesWidthOfWires();
		/// <summary>
		/// Правила зазоров между цепями.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesClearancesNetToNet")][XmlArrayItem("ClearanceNetToNet")] public List<ClearanceNetToNet> _RulesClearancesNetToNet;
		std::vector<std::shared_ptr<ClearanceNetToNet>> _RulesClearancesNetToNet;
		bool ShouldSerialize_RulesClearancesNetToNet();
		/// <summary>
		/// Правила зазоров между компонентами.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesClearancesCompToComp")][XmlArrayItem("ClearanceCompToComp")] public List<ClearanceCompToComp> _RulesClearancesCompToComp;
		std::vector<std::shared_ptr<ClearanceCompToComp>> _RulesClearancesCompToComp;
		bool ShouldSerialize_RulesClearancesCompToComp();
		/// <summary>
		/// Правило зазоров до края платы.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("RulesClearancesToBoard")] public RulesClearancesToBoard _RulesClearancesToBoard;
		std::shared_ptr<RulesClearancesToBoard> _RulesClearancesToBoard;

		/// <summary>
		/// Правила назначения цепям стеков переходных отверстий.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesViastacksOfNets")][XmlArrayItem("ViastacksOfNets")] public List<ViastacksOfNets> _RulesViastacksOfNets;
		std::vector<std::shared_ptr<ViastacksOfNets>> _RulesViastacksOfNets;
		bool ShouldSerialize_RulesViastacksOfNets();
		/// <summary>
		/// Правила назначения цепям опорных слоёв.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesPlaneLayersNets")][XmlArrayItem("PlaneLayerNets")] public List<PlaneLayerNets> _RulesPlaneLayersNets;
		std::vector<std::shared_ptr<PlaneLayerNets>> _RulesPlaneLayersNets;
		bool ShouldSerialize_RulesPlaneLayersNets();
		/// <summary>
		/// Правила назначения цепям сигнальных слоёв.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesSignalLayersNets")][XmlArrayItem("SignalLayerNets")] public List<SignalLayerNets> _RulesSignalLayersNets;
		std::vector<std::shared_ptr<SignalLayerNets>> _RulesSignalLayersNets;
		bool ShouldSerialize_RulesSignalLayersNets();
		/// <summary>
		/// Свойства цепей
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("NetProperties")][XmlArrayItem("NetProperty")] public List<NetProperty> _NetProperties;
		std::vector<std::shared_ptr<NetProperty>> _NetProperties;
		bool ShouldSerialize_NetProperties();
		/// <summary>
		/// Настройки подключения к углам прямоугольных контактных площадок.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadConnectSettings")] public PadConnectSettings _PadConnectSettings;
		std::shared_ptr<PadConnectSettings> _PadConnectSettings;


		/*****************************************************************
		 * Здесь находятся функции для работы с элементами класса Rules. *
		 * Они не являются частью формата TopoR PCB.                     *
		 * ***************************************************************/

		/// <summary>
		/// Переименование ссылок на компонент, если его имя изменилось
		/// </summary>
		/// <param name="oldname">старое имя компонента</param>
		/// <param name="newname">новое имя компонента</param>
		void Rename_compName(const std::wstring &oldname, const std::wstring &newname);
	};
}
