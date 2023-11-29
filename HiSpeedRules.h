﻿#pragma once

#include "Commons.h"
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Правила для высокоскоростных устройств».

class HiSpeedRules {

    // Волновое сопротивление и правила разводки сигналов по слоям.

public:
    class Impedance {
    public:
        class LayerRule_Impendance {

            // Ширина проводника.

        public:
            //[XmlAttribute("width", DataType = "float")] public float _width;
            float _width = 0.0F;

            // Ссылка на слой.

            //[XmlElement("LayerRef")] public LayerRef _LayerRef;
            std::optional<LayerRef> _LayerRef;
        };

        // Имя объекта или ссылка на именованный объект.

    public:
        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.

        //[XmlAttribute("Z0", DataType = "float")] public float _z0;
        float _z0 = 0.0F;

        // Правило разводки сигнала для слоя.

        //[XmlElement("LayerRule")] public List<LayerRule_Impendance> _LayerImpedanceRules;
        std::vector<std::optional<LayerRule_Impendance>> _LayerImpedanceRules;
        bool ShouldSerialize_LayerImpedanceRules();
    };

    // Волновое сопротивление и правила разводки сигналов по слоям для дифференциальных сигналов.

public:
    class ImpedanceDiff {
    public:
        class LayerRule_ImpendanceDiff {

            // Ширина проводника.

        public:
            //[XmlAttribute("width", DataType = "float")] public float _width;
            float _width = 0.0F;

            // Параметр правила разводки дифференциальных пар: зазор между проводниками пары.

            //[XmlAttribute("gap", DataType = "float")] public float _gap;
            float _gap = 0.0F;

            // Ссылка на слой.

            //[XmlElement("LayerRef")] public LayerRef _LayerRef;
            std::optional<LayerRef> _LayerRef;
        };

        // Имя объекта или ссылка на именованный объект.

    public:
        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.

        //[XmlAttribute("Z0", DataType = "float")] public float _z0;
        float _z0 = 0.0F;

        // Правило разводки дифференциальной пары для слоя.

        //[XmlElement("LayerRule")] public List<LayerRule_ImpendanceDiff> _LayerImpedanceDiffRules;
        std::vector<std::optional<LayerRule_ImpendanceDiff>> _LayerImpedanceDiffRules;
        bool ShouldSerialize_LayerImpedanceDiffRules();
    };

    // Описание сигнального кластера цепей.

public:
    class SignalCluster {

        // Описание заданной связи.

    public:
        class PinPair {

            // Ссылка на контакт источника сигнала.

        public:
            //[XmlElement("PinRef")] public List<PinRef> _PinRefs;
            std::vector<std::optional<PinRef>> _PinRefs;
            bool ShouldSerialize_PinRefs();
        };

        // Описание сигнала.

    public:
        class Signal {

            // Имя объекта или ссылка на именованный объект.

        public:
            //[XmlAttribute("name")] public string _name;
            std::string _name;

            // Ссылка на контакт источника сигнала.

            //[XmlElement("ReceiverPinRef")] public ReceiverPinRef _ReceiverPinRef;
            std::optional<ReceiverPinRef> _ReceiverPinRef;

            // Пассивные компоненты на пути следования сигнала.

            //[XmlArray("Components")][XmlArrayItem("CompInstanceRef")] public List<CompInstanceRef> _Components;
            std::vector<std::optional<CompInstanceRef>> _Components;
            /*   public bool ShouldSerialize_Components()
               {
                   return _Components?.Count > 0;
               }*/
        };

        // Ссылка на волновое сопротивление.

    public:
        //[XmlElement("ImpedanceRef")] public ImpedanceRef _ImpedanceRef;
        std::optional<ImpedanceRef> _ImpedanceRef;

        // Ссылка на контакт источника сигнала.

        //[XmlElement("SourcePinRef")] public SourcePinRef _SourcePinRef;
        std::optional<SourcePinRef> _SourcePinRef;

        // Цепи сигнального кластера.

        //[XmlArray("Nets")][XmlArrayItem("NetRef")] public List<NetRef> _Nets;
        std::vector<std::optional<NetRef>> _Nets;
        /*     public bool ShouldSerialize_Nets()
             {
                 return _Nets?.Count > 0;
             }
        */

        // Описание заданных связей сигнального кластера.

        //[XmlArray("PinPairs")][XmlArrayItem("PinPair")] public List<PinPair> _PinPairs;
        std::vector<std::optional<PinPair>> _PinPairs;
        /*   public bool ShouldSerialize_PinPairs()
           {
               return _PinPairs?.Count > 0;
           }
        */

        // Ссылки на сигналы.

        //[XmlElement("Signal")] public List<Signal> _Signals;
        std::vector<std::optional<Signal>> _Signals;
        /*    public bool ShouldSerialize_Signals()
            {
                return _Signals?.Count > 0;
            }
        */
    };

    // Описание дифференциального сигнала (дифференциальной пары).

public:
    class DiffSignal {

        // Имя объекта или ссылка на именованный объект.

    public:
        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Параметр дифференциальной пары: допустимый разброс длины между проводниками пары.

        //[XmlAttribute("mismatch", DataType = "float")] public float _mismatch;
        float _mismatch = 0.0F;

        // Ссылка на волновое сопротивление.

        //[XmlElement("ImpedanceRef")] public ImpedanceRef _ImpedanceRef;
        std::optional<ImpedanceRef> _ImpedanceRef;

        // Ссылки на сигналы.

        //[XmlElement("SignalRef")] public List<SignalRef> _SignalRefs;
        std::vector<std::optional<SignalRef>> _SignalRefs;
        bool ShouldSerialize_SignalRefs();
    };

    // Описание группы сигналов.

public:
    class SignalGroup {

        // Имя объекта или ссылка на именованный объект.

    public:
        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Ссылки на сигнал, диф.сигнал, или группу сигналов

        // <value>SignalRef, DiffSignalRef, SignalGroupRef</value>

        //[XmlElement("SignalRef", typeof(SignalRef)), XmlElement("DiffSignalRef", typeof(DiffSignalRef)), XmlElement("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _References;
        std::vector<std::any> _References;
        bool ShouldSerialize_References();
    };

    // Описание правил выравнивания задержек.

public:
    class RulesDelay {

        // Описание правила выравнивания задержек для группы цепей или группы дифференциальных пар.

    public:
        class DelayEqual {

            // Флаг применения правила.

        public:
            //[XmlAttribute("enabled")] public Bool _enabled;
            Bool _enabled{};

            //[XmlIgnore] public bool _enabledSpecified
            bool getEnabledSpecified() const;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            //[XmlAttribute("valueType")] public valueType _valueType;
            valueType _valueType{};

            // Параметр правила выравнивания задержек внутри группы цепей: допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("tolerance", DataType = "float")] public float _tolerance;
            float _tolerance = 0.0F;

            // Объекты воздействия правила.

            //[XmlArray("ObjectsAffected")][XmlArrayItem("SignalGroupRef")] public List<SignalGroupRef> _ObjectsAffected;
            std::vector<std::optional<SignalGroupRef>> _ObjectsAffected;
            bool ShouldSerialize_ObjectsAffected();
        };

        // Описание правила задания абсолютного значения задержки.

    public:
        class DelayConstant {

            // Флаг применения правила.

        public:
            //[XmlAttribute("enabled")] public Bool _enabled;
            Bool _enabled{};

            //[XmlIgnore] public bool _enabledSpecified
            bool getEnabledSpecified() const;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            //[XmlAttribute("valueType")] public valueType _valueType;
            valueType _valueType{};

            // Значение константы в правилах выравнивания задержек.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("constant", DataType = "float")] public float _constant;
            float _constant = 0.0F;

            // Параметр правила выравнивания задержек: нижний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("toleranceUnder", DataType = "float")] public float _toleranceUnder;
            float _toleranceUnder = 0.0F;

            // Параметр правила выравнивания задержек: верхний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("toleranceOver", DataType = "float")] public float _toleranceOver;
            float _toleranceOver = 0.0F;

            // Объекты воздействия правила.

            //[XmlArray("ObjectsAffected")][XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
            std::vector<std::any> _ObjectsAffected;
            bool ShouldSerialize_ObjectsAffected();
        };

        // Описание правила взаимного выравнивания задержек.

        // <remarks>! Правило несимметрично относительно ObjectLeft и ObjectRight</remarks>
    public:
        class DelayRelation {

            // Флаг применения правила.

        public:
            //[XmlAttribute("enabled")] public Bool _enabled;
            Bool _enabled{};

            //[XmlIgnore] public bool _enabledSpecified
            bool getEnabledSpecified() const;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            //[XmlAttribute("valueType")] public valueType _valueType;
            valueType _valueType{};

            // Значение константы в правилах выравнивания задержек.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("constant", DataType = "float")] public float _constant;
            float _constant = 0.0F;

            // Параметр правила выравнивания задержек: нижний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("toleranceUnder", DataType = "float")] public float _toleranceUnder;
            float _toleranceUnder = 0.0F;

            // Параметр правила выравнивания задержек: верхний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            //[XmlAttribute("toleranceOver", DataType = "float")] public float _toleranceOver;
            float _toleranceOver = 0.0F;

            // Первый объект воздействия правила взаимного выравнивания задержек.

            //[XmlElement("ObjectLeft")] public ObjectSignal _ObjectLeft;
            std::optional<ObjectSignal> _ObjectLeft;

            // Второй объект воздействия правила взаимного выравнивания задержек.

            //[XmlElement("ObjectRight")] public ObjectSignal _ObjectRight;
            std::optional<ObjectSignal> _ObjectRight;
        };

        // Правила выравнивания задержек для группы цепей или группы дифференциальных пар.

    public:
        //[XmlElement("DelayEqual")] public List<DelayEqual> _DelayEquals;
        std::vector<std::optional<DelayEqual>> _DelayEquals;
        bool ShouldSerialize_DelayEquals();

        // Правила задания абсолютного значения задержки.

        //[XmlElement("DelayConstant")] public List<DelayConstant> _DelayConstants;
        std::vector<std::optional<DelayConstant>> _DelayConstants;
        bool ShouldSerialize_DelayConstants();

        // Правила взаимного выравнивания задержек.

        // <remarks>! Правила несимметричны относительно ObjectLeft и ObjectRight</remarks>

        //[XmlElement("DelayRelation")] public List<DelayRelation> _DelayRelations;
        std::vector<std::optional<DelayRelation>> _DelayRelations;
        bool ShouldSerialize_DelayRelations();
    };

    // Настройки поиска сигналов.

public:
    class SignalSearchSettings {

        // Правило именования цепей дифференциальных сигналов.

    public:
        class RuleDiffSignalNetsNames {

            // Флаг применения правила.

        public:
            //[XmlAttribute("enabled")] public Bool _enabled;
            Bool _enabled{};

            //[XmlIgnore] public bool _enabledSpecified
            bool getEnabledSpecified() const;

            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь позитивного сигнала.

            //[XmlAttribute("posStr")] public string _posStr;
            std::string _posStr;

            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь негативного сигнала.

            //[XmlAttribute("negStr")] public string _negStr;
            std::string _negStr;
        };

        // Список цепей, исключённых из поиска сигналов.

    public:
        class ExcludedNets {

            // Минимальное количество контактов в силовой цепи. Параметр используется для автоматического определения силовых цепей.

        public:
            //[XmlAttribute("minPinsNumber", DataType = "int")] public int _minPinsNumber;
            int _minPinsNumber = 0;

            // Cсылки на цепи.

            //[XmlElement("NetRef")] public List<NetRef> _NetRefs;
            std::vector<std::optional<NetRef>> _NetRefs;
            bool ShouldSerialize_NetRefs();
        };

        // Максимальное число цепей в сигнальном кластере. Параметр используется при автоматическом определении цепей сигнального кластера.

    public:
        //[XmlAttribute("maxNetsInCluster", DataType = "int")] public int _maxNetsInCluster;
        int _maxNetsInCluster = 0;

        // Автоматически задавать связи.

        //[XmlAttribute("createPinPairs")] public Bool _createPinPairs;
        Bool _createPinPairs{};

        //[XmlIgnore] public bool _createPinPairsSpecified
        bool getCreatePinPairsSpecified() const;

        // Правила именования цепей дифференциальных сигналов.

        // <remarks>! Порядок следования правил в этой секции определяет приоритет правил. Правила следуют в порядке убывания приоритета.</remarks>

        //[XmlArray("RulesDiffSignalNetsNames")][XmlArrayItem("RuleDiffSignalNetsNames")] public List<RuleDiffSignalNetsNames> _RulesDiffSignalNetsNames;
        std::vector<std::optional<RuleDiffSignalNetsNames>> _RulesDiffSignalNetsNames;
        bool ShouldSerialize_RulesDiffSignalNetsNames();

        // Список цепей, исключённых из поиска сигналов.

        //[XmlElement("ExcludedNets")] public ExcludedNets _ExcludedNets;
        std::optional<ExcludedNets> _ExcludedNets;
    };

    // Версия раздела.

public:
    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Волновые сопротивления и правила разводки сигналов.

    //[XmlArray("RulesImpedances")][XmlArrayItem("Impedance", typeof(Impedance)), XmlArrayItem("ImpedanceDiff", typeof(ImpedanceDiff))] public List<Object> _RulesImpedances;
    std::vector<std::any> _RulesImpedances;
    bool ShouldSerialize_RulesImpedances();

    // Сигнальные кластеры цепей.

    //[XmlArray("SignalClusters")][XmlArrayItem("SignalCluster")] public List<SignalCluster> _SignalClusters;
    std::vector<std::optional<SignalCluster>> _SignalClusters;
    bool ShouldSerialize_SignalClusters();

    // Дифференциальные сигналы.

    //[XmlArray("DiffSignals")][XmlArrayItem("DiffSignal")] public List<DiffSignal> _DiffSignals;
    std::vector<std::optional<DiffSignal>> _DiffSignals;
    bool ShouldSerialize_DiffSignals();

    // Группы сигналов.

    //[XmlArray("SignalGroups")][XmlArrayItem("SignalGroup")] public List<SignalGroup> _SignalGroups;
    std::vector<std::optional<SignalGroup>> _SignalGroups;
    bool ShouldSerialize_SignalGroups();

    // Правила выравнивания задержек.

    //[XmlElement("RulesDelay")] public RulesDelay _RulesDelay;
    std::optional<RulesDelay> _RulesDelay;

    // Настройки автоматического поиска сигналов.

    //[XmlElement("SignalSearchSettings")] public SignalSearchSettings _SignalSearchSettings;
    std::optional<SignalSearchSettings> _SignalSearchSettings;

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса HiSpeedRules. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    // Переименование ссылок на компонент, если его имя изменилось

    // <param name="oldname">старое имя компонента</param>
    // <param name="newname">новое имя компонента</param>
    void Rename_compName(const std::string& oldname, const std::string& newname);
    /***********************************************************************/
};
} // namespace TopoR_PCB_Classes
