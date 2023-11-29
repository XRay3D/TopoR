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
	/// Раздел «Правила для высокоскоростных устройств».
	/// </summary>
	class HiSpeedRules : public std::enable_shared_from_this<HiSpeedRules>
	{
		/// <summary>
		/// Волновое сопротивление и правила разводки сигналов по слоям.
		/// </summary>
	public:
		class Impedance : public std::enable_shared_from_this<Impedance>
		{
		public:
			class LayerRule_Impendance : public std::enable_shared_from_this<LayerRule_Impendance>
			{
				/// <summary>
				/// Ширина проводника.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("width", DataType = "float")] public float _width;
				float _width = 0.0F;

				/// <summary>
				/// Ссылка на слой.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
				std::shared_ptr<LayerRef> _LayerRef;
			};

			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("Z0", DataType = "float")] public float _z0;
			float _z0 = 0.0F;

			/// <summary>
			/// Правило разводки сигнала для слоя.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRule")] public List<LayerRule_Impendance> _LayerImpedanceRules;
			std::vector<std::shared_ptr<LayerRule_Impendance>> _LayerImpedanceRules;
			bool ShouldSerialize_LayerImpedanceRules();
		};

		/// <summary>
		/// Волновое сопротивление и правила разводки сигналов по слоям для дифференциальных сигналов.
		/// </summary>
	public:
		class ImpedanceDiff : public std::enable_shared_from_this<ImpedanceDiff>
		{
		public:
			class LayerRule_ImpendanceDiff : public std::enable_shared_from_this<LayerRule_ImpendanceDiff>
			{
				/// <summary>
				/// Ширина проводника.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("width", DataType = "float")] public float _width;
				float _width = 0.0F;

				/// <summary>
				/// Параметр правила разводки дифференциальных пар: зазор между проводниками пары.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("gap", DataType = "float")] public float _gap;
				float _gap = 0.0F;

				/// <summary>
				/// Ссылка на слой.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
				std::shared_ptr<LayerRef> _LayerRef;
			};

			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("Z0", DataType = "float")] public float _z0;
			float _z0 = 0.0F;

			/// <summary>
			/// Правило разводки дифференциальной пары для слоя.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRule")] public List<LayerRule_ImpendanceDiff> _LayerImpedanceDiffRules;
			std::vector<std::shared_ptr<LayerRule_ImpendanceDiff>> _LayerImpedanceDiffRules;
			bool ShouldSerialize_LayerImpedanceDiffRules();
		};

		/// <summary>
		/// Описание сигнального кластера цепей.
		/// </summary>
	public:
		class SignalCluster : public std::enable_shared_from_this<SignalCluster>
		{
			/// <summary>
			/// Описание заданной связи.
			/// </summary>
		public:
			class PinPair : public std::enable_shared_from_this<PinPair>
			{
				/// <summary>
				/// Ссылка на контакт источника сигнала.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PinRef")] public List<PinRef> _PinRefs;
				std::vector<std::shared_ptr<PinRef>> _PinRefs;
				bool ShouldSerialize_PinRefs();
			};

			/// <summary>
			/// Описание сигнала.
			/// </summary>
		public:
			class Signal : public std::enable_shared_from_this<Signal>
			{
				/// <summary>
				/// Имя объекта или ссылка на именованный объект.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
				std::wstring _name;

				/// <summary>
				/// Ссылка на контакт источника сигнала.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ReceiverPinRef")] public ReceiverPinRef _ReceiverPinRef;
				std::shared_ptr<ReceiverPinRef> _ReceiverPinRef;

				/// <summary>
				/// Пассивные компоненты на пути следования сигнала.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Components")][XmlArrayItem("CompInstanceRef")] public List<CompInstanceRef> _Components;
				std::vector<std::shared_ptr<CompInstanceRef>> _Components;
			 /*   public bool ShouldSerialize_Components()
			    {
			        return _Components?.Count > 0;
			    }*/
			};

			/// <summary>
			/// Ссылка на волновое сопротивление.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ImpedanceRef")] public ImpedanceRef _ImpedanceRef;
			std::shared_ptr<ImpedanceRef> _ImpedanceRef;

			/// <summary>
			/// Ссылка на контакт источника сигнала.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SourcePinRef")] public SourcePinRef _SourcePinRef;
			std::shared_ptr<SourcePinRef> _SourcePinRef;

			/// <summary>
			/// Цепи сигнального кластера.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Nets")][XmlArrayItem("NetRef")] public List<NetRef> _Nets;
			std::vector<std::shared_ptr<NetRef>> _Nets;
	   /*     public bool ShouldSerialize_Nets()
	        {
	            return _Nets?.Count > 0;
	        }
	   */
			/// <summary>
			/// Описание заданных связей сигнального кластера.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("PinPairs")][XmlArrayItem("PinPair")] public List<PinPair> _PinPairs;
			std::vector<std::shared_ptr<PinPair>> _PinPairs;
		 /*   public bool ShouldSerialize_PinPairs()
		    {
		        return _PinPairs?.Count > 0;
		    }
		 */
			/// <summary>
			/// Ссылки на сигналы.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Signal")] public List<Signal> _Signals;
			std::vector<std::shared_ptr<Signal>> _Signals;
		/*    public bool ShouldSerialize_Signals()
		    {
		        return _Signals?.Count > 0;
		    }
		*/
		};

		/// <summary>
		/// Описание дифференциального сигнала (дифференциальной пары).
		/// </summary>
	public:
		class DiffSignal : public std::enable_shared_from_this<DiffSignal>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Параметр дифференциальной пары: допустимый разброс длины между проводниками пары.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("mismatch", DataType = "float")] public float _mismatch;
			float _mismatch = 0.0F;

			/// <summary>
			/// Ссылка на волновое сопротивление.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ImpedanceRef")] public ImpedanceRef _ImpedanceRef;
			std::shared_ptr<ImpedanceRef> _ImpedanceRef;

			/// <summary>
			/// Ссылки на сигналы.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SignalRef")] public List<SignalRef> _SignalRefs;
			std::vector<std::shared_ptr<SignalRef>> _SignalRefs;
			bool ShouldSerialize_SignalRefs();
		};

		/// <summary>
		/// Описание группы сигналов.
		/// </summary>
	public:
		class SignalGroup : public std::enable_shared_from_this<SignalGroup>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Ссылки на сигнал, диф.сигнал, или группу сигналов
			/// </summary>
			/// <value>SignalRef, DiffSignalRef, SignalGroupRef</value>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SignalRef", typeof(SignalRef)), XmlElement("DiffSignalRef", typeof(DiffSignalRef)), XmlElement("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _References;
			std::vector<std::any> _References;
			bool ShouldSerialize_References();
		};

		/// <summary>
		/// Описание правил выравнивания задержек.
		/// </summary>
	public:
		class RulesDelay : public std::enable_shared_from_this<RulesDelay>
		{
			/// <summary>
			/// Описание правила выравнивания задержек для группы цепей или группы дифференциальных пар.
			/// </summary>
		public:
			class DelayEqual : public std::enable_shared_from_this<DelayEqual>
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
				/// Параметр правил выравнивания задержек: тип значений констант и допусков.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("valueType")] public valueType _valueType;
				valueType _valueType = static_cast<valueType>(0);

				/// <summary>
				/// Параметр правила выравнивания задержек внутри группы цепей: допуск.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("tolerance", DataType = "float")] public float _tolerance;
				float _tolerance = 0.0F;

				/// <summary>
				/// Объекты воздействия правила.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("SignalGroupRef")] public List<SignalGroupRef> _ObjectsAffected;
				std::vector<std::shared_ptr<SignalGroupRef>> _ObjectsAffected;
				bool ShouldSerialize_ObjectsAffected();
			};

			/// <summary>
			/// Описание правила задания абсолютного значения задержки.
			/// </summary>
		public:
			class DelayConstant : public std::enable_shared_from_this<DelayConstant>
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
				/// Параметр правил выравнивания задержек: тип значений констант и допусков.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("valueType")] public valueType _valueType;
				valueType _valueType = static_cast<valueType>(0);

				/// <summary>
				/// Значение константы в правилах выравнивания задержек.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("constant", DataType = "float")] public float _constant;
				float _constant = 0.0F;

				/// <summary>
				/// Параметр правила выравнивания задержек: нижний допуск.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("toleranceUnder", DataType = "float")] public float _toleranceUnder;
				float _toleranceUnder = 0.0F;

				/// <summary>
				/// Параметр правила выравнивания задержек: верхний допуск.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("toleranceOver", DataType = "float")] public float _toleranceOver;
				float _toleranceOver = 0.0F;

				/// <summary>
				/// Объекты воздействия правила.
				/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("ObjectsAffected")][XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
				std::vector<std::any> _ObjectsAffected;
				bool ShouldSerialize_ObjectsAffected();
			};

			/// <summary>
			/// Описание правила взаимного выравнивания задержек.
			/// </summary>
			/// <remarks>! Правило несимметрично относительно ObjectLeft и ObjectRight</remarks>
		public:
			class DelayRelation : public std::enable_shared_from_this<DelayRelation>
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
				/// Параметр правил выравнивания задержек: тип значений констант и допусков.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("valueType")] public valueType _valueType;
				valueType _valueType = static_cast<valueType>(0);

				/// <summary>
				/// Значение константы в правилах выравнивания задержек.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("constant", DataType = "float")] public float _constant;
				float _constant = 0.0F;

				/// <summary>
				/// Параметр правила выравнивания задержек: нижний допуск.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("toleranceUnder", DataType = "float")] public float _toleranceUnder;
				float _toleranceUnder = 0.0F;

				/// <summary>
				/// Параметр правила выравнивания задержек: верхний допуск.
				/// </summary>
				/// <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("toleranceOver", DataType = "float")] public float _toleranceOver;
				float _toleranceOver = 0.0F;

				/// <summary>
				/// Первый объект воздействия правила взаимного выравнивания задержек.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ObjectLeft")] public ObjectSignal _ObjectLeft;
				std::shared_ptr<ObjectSignal> _ObjectLeft;

				/// <summary>
				/// Второй объект воздействия правила взаимного выравнивания задержек.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ObjectRight")] public ObjectSignal _ObjectRight;
				std::shared_ptr<ObjectSignal> _ObjectRight;
			};

			/// <summary>
			/// Правила выравнивания задержек для группы цепей или группы дифференциальных пар.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DelayEqual")] public List<DelayEqual> _DelayEquals;
			std::vector<std::shared_ptr<DelayEqual>> _DelayEquals;
			bool ShouldSerialize_DelayEquals();
			/// <summary>
			/// Правила задания абсолютного значения задержки.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DelayConstant")] public List<DelayConstant> _DelayConstants;
			std::vector<std::shared_ptr<DelayConstant>> _DelayConstants;
			bool ShouldSerialize_DelayConstants();
			/// <summary>
			/// Правила взаимного выравнивания задержек. 
			/// </summary>
			/// <remarks>! Правила несимметричны относительно ObjectLeft и ObjectRight</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DelayRelation")] public List<DelayRelation> _DelayRelations;
			std::vector<std::shared_ptr<DelayRelation>> _DelayRelations;
			bool ShouldSerialize_DelayRelations();
		};

		/// <summary>
		/// Настройки поиска сигналов.
		/// </summary>
	public:
		class SignalSearchSettings : public std::enable_shared_from_this<SignalSearchSettings>
		{
			/// <summary>
			/// Правило именования цепей дифференциальных сигналов.
			/// </summary>
		public:
			class RuleDiffSignalNetsNames : public std::enable_shared_from_this<RuleDiffSignalNetsNames>
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
				/// Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь позитивного сигнала.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("posStr")] public string _posStr;
				std::wstring _posStr;

				/// <summary>
				/// Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь негативного сигнала.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("negStr")] public string _negStr;
				std::wstring _negStr;
			};

			/// <summary>
			/// Список цепей, исключённых из поиска сигналов.
			/// </summary>
		public:
			class ExcludedNets : public std::enable_shared_from_this<ExcludedNets>
			{
				/// <summary>
				/// Минимальное количество контактов в силовой цепи. Параметр используется для автоматического определения силовых цепей.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("minPinsNumber", DataType = "int")] public int _minPinsNumber;
				int _minPinsNumber = 0;

				/// <summary>
				/// Cсылки на цепи.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public List<NetRef> _NetRefs;
				std::vector<std::shared_ptr<NetRef>> _NetRefs;
				bool ShouldSerialize_NetRefs();
			};

			/// <summary>
			/// Максимальное число цепей в сигнальном кластере. Параметр используется при автоматическом определении цепей сигнального кластера.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("maxNetsInCluster", DataType = "int")] public int _maxNetsInCluster;
			int _maxNetsInCluster = 0;

			/// <summary>
			/// Автоматически задавать связи.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("createPinPairs")] public Bool _createPinPairs;
			Bool _createPinPairs = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _createPinPairsSpecified
			bool getCreatePinPairsSpecified() const;

			/// <summary>
			/// Правила именования цепей дифференциальных сигналов.
			/// </summary>
			/// <remarks>! Порядок следования правил в этой секции определяет приоритет правил. Правила следуют в порядке убывания приоритета.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesDiffSignalNetsNames")][XmlArrayItem("RuleDiffSignalNetsNames")] public List<RuleDiffSignalNetsNames> _RulesDiffSignalNetsNames;
			std::vector<std::shared_ptr<RuleDiffSignalNetsNames>> _RulesDiffSignalNetsNames;
			bool ShouldSerialize_RulesDiffSignalNetsNames();
			/// <summary>
			/// Список цепей, исключённых из поиска сигналов.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ExcludedNets")] public ExcludedNets _ExcludedNets;
			std::shared_ptr<ExcludedNets> _ExcludedNets;
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::wstring _version;

		/// <summary>
		/// Волновые сопротивления и правила разводки сигналов.
		/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("RulesImpedances")][XmlArrayItem("Impedance", typeof(Impedance)), XmlArrayItem("ImpedanceDiff", typeof(ImpedanceDiff))] public List<Object> _RulesImpedances;
		std::vector<std::any> _RulesImpedances;
		bool ShouldSerialize_RulesImpedances();
		/// <summary>
		/// Сигнальные кластеры цепей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("SignalClusters")][XmlArrayItem("SignalCluster")] public List<SignalCluster> _SignalClusters;
		std::vector<std::shared_ptr<SignalCluster>> _SignalClusters;
		bool ShouldSerialize_SignalClusters();
		/// <summary>
		/// Дифференциальные сигналы.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("DiffSignals")][XmlArrayItem("DiffSignal")] public List<DiffSignal> _DiffSignals;
		std::vector<std::shared_ptr<DiffSignal>> _DiffSignals;
		bool ShouldSerialize_DiffSignals();
		/// <summary>
		/// Группы сигналов.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("SignalGroups")][XmlArrayItem("SignalGroup")] public List<SignalGroup> _SignalGroups;
		std::vector<std::shared_ptr<SignalGroup>> _SignalGroups;
		bool ShouldSerialize_SignalGroups();
		/// <summary>
		/// Правила выравнивания задержек.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("RulesDelay")] public RulesDelay _RulesDelay;
		std::shared_ptr<RulesDelay> _RulesDelay;

		/// <summary>
		/// Настройки автоматического поиска сигналов.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("SignalSearchSettings")] public SignalSearchSettings _SignalSearchSettings;
		std::shared_ptr<SignalSearchSettings> _SignalSearchSettings;


		/************************************************************************
		 * Здесь находятся функции для работы с элементами класса HiSpeedRules. *
		 * Они не являются частью формата TopoR PCB.                            *
		 * **********************************************************************/

		/// <summary>
		/// Переименование ссылок на компонент, если его имя изменилось
		/// </summary>
		/// <param name="oldname">старое имя компонента</param>
		/// <param name="newname">новое имя компонента</param>
		void Rename_compName(const std::wstring &oldname, const std::wstring &newname);
		/***********************************************************************/
	};
}
