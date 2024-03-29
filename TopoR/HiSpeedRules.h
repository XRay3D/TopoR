#pragma once
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
namespace TopoR {
// Раздел «Правила для высокоскоростных устройств».
struct HiSpeedRules {
    // Волновое сопротивление и правила разводки сигналов по слоям.
    struct Impedance {
        struct LayerRule {
            // Ширина проводника.
            // [XmlAttribute("width", DataType = "float")] public float width_;
            XmlAttr<float> width;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
        };
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
        // [XmlAttribute("Z0", DataType = "float")] public float z0_;
        XmlAttr<float> Z0;
        // Правило разводки сигнала для слоя.
        // [XmlElement("LayerRule")] public List<LayerRule_Impendance> LayerImpedanceRules_;
        XmlArray<LayerRule> LayerImpedanceRules;
    };
    // Волновое сопротивление и правила разводки сигналов по слоям для дифференциальных сигналов.
    struct ImpedanceDiff {
        struct LayerRule {
            // Ширина проводника.
            // [XmlAttribute("width", DataType = "float")] public float width_;
            XmlAttr<float> width;
            // Параметр правила разводки дифференциальных пар: зазор между проводниками пары.
            // [XmlAttribute("gap", DataType = "float")] public float gap_;
            XmlAttr<float> gap;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
        };
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
        // [XmlAttribute("Z0", DataType = "float")] public float z0_;
        XmlAttr<float> Z0;
        // Правило разводки дифференциальной пары для слоя.
        // [XmlElement("LayerRule")] public List<LayerRule_ImpendanceDiff> LayerImpedanceDiffRules_;
        XmlArray<LayerRule> LayerImpedanceDiffRules;
    };
    // Описание сигнального кластера цепей.
    struct SignalCluster {
        // Описание заданной связи.
        struct PinPair {
            // Ссылка на контакт источника сигнала.
            // [XmlElement("PinRef")] public List<PinRef> PinRefs_;
            XmlArrayElem<PinRef> PinRefs;
        };
        // Описание сигнала.
        struct Signal {
            // Имя объекта или ссылка на именованный объект.
            XmlAttr<QString> name;
            // Ссылка на контакт источника сигнала.
            // [XmlElement("ReceiverPinRef")] public ReceiverPinRef receiverPinRef;
            ReceiverPinRef receiverPinRef;
            // Пассивные компоненты на пути следования сигнала.
            // [XmlArray("Components")][XmlArrayItem("CompInstanceRef")] public List<CompInstanceRef> Components_;
            XmlArrayElem<CompInstanceRef> Components;
        };
        // Ссылка на волновое сопротивление.
        // [XmlElement("ImpedanceRef")] public ImpedanceRef impedanceRef;
        ImpedanceRef impedanceRef;
        // Ссылка на контакт источника сигнала.
        // [XmlElement("SourcePinRef")] public SourcePinRef sourcePinRef;
        SourcePinRef sourcePinRef;
        // Цепи сигнального кластера.
        // [XmlArray("Nets")][XmlArrayItem("NetRef")] public List<NetRef> Nets_;
        XmlArrayElem<NetRef> Nets;
        // Описание заданных связей сигнального кластера.
        // [XmlArray("PinPairs")][XmlArrayItem("PinPair")] public List<PinPair> PinPairs_;
        XmlArrayElem<PinPair> PinPairs;
        // Ссылки на сигналы.
        // [XmlElement("Signal")] public List<Signal> Signals_;
        XmlArrayElem<Signal> Signals;
    };
    // Описание дифференциального сигнала (дифференциальной пары).
    struct DiffSignal {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Параметр дифференциальной пары: допустимый разброс длины между проводниками пары.
        // [XmlAttribute("mismatch", DataType = "float")] public float mismatch_;
        XmlAttr<float> mismatch;
        // Ссылка на волновое сопротивление.
        // [XmlElement("ImpedanceRef")] public ImpedanceRef impedanceRef;
        ImpedanceRef impedanceRef;
        // Ссылки на сигналы.
        // [XmlElement("SignalRef")] public List<SignalRef> SignalRefs_;
        XmlArrayElem<SignalRef> SignalRefs;
    };
    // Описание группы сигналов.
    struct SignalGroup {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Ссылки на сигнал, диф.сигнал, или группу сигналов
        // <value>SignalRef, DiffSignalRef, SignalGroupRef</value>
        // [XmlElement(SignalRef),
        //  XmlElement(DiffSignalRef),
        //  XmlElement(SignalGroupRef)] public List<Object> References_;
        XmlArrayElem<XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef>> References;
    };
    // Описание правил выравнивания задержек.
    struct RulesDelay {
        // Описание правила выравнивания задержек для группы цепей или группы дифференциальных пар.
        struct DelayEqual {
            // Флаг применения правила.
            // [XmlAttribute("enabled")] public Bool enabled_;
            XmlAttr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [XmlAttribute("valueType")] public valueType valueType_;
            XmlAttr<valueType> valueType_;
            // Параметр правила выравнивания задержек внутри группы цепей: допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("tolerance", DataType = "float")] public float tolerance_;
            XmlAttr<float> tolerance;
            // Объекты воздействия правила.
            // [XmlArray("ObjectsAffected")][XmlArrayItem("SignalGroupRef")] public List<SignalGroupRef> ObjectsAffected_;
            XmlArrayElem<SignalGroupRef> ObjectsAffected;
        };
        // Описание правила задания абсолютного значения задержки.
        struct DelayConstant {
            // Флаг применения правила.
            // [XmlAttribute("enabled")] public Bool enabled_;
            XmlAttr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [XmlAttribute("valueType")] public valueType valueType_;
            XmlAttr<valueType> valueType_;
            // Значение константы в правилах выравнивания задержек.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("constant", DataType = "float")] public float constant_;
            XmlAttr<float> constant;
            // Параметр правила выравнивания задержек: нижний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("toleranceUnder", DataType = "float")] public float toleranceUnder_;
            XmlAttr<float> toleranceUnder;
            // Параметр правила выравнивания задержек: верхний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("toleranceOver", DataType = "float")] public float toleranceOver_;
            XmlAttr<float> toleranceOver;
            // Объекты воздействия правила.
            // [XmlArray("ObjectsAffected")][XmlArrayItem(SignalRef),
            //  XmlArrayItem(DiffSignalRef),
            //  XmlArrayItem(SignalGroupRef)] public List<Object> ObjectsAffected_;
            XmlArrayElem<XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
        };
        // Описание правила взаимного выравнивания задержек.
        /// \note !Правило несимметрично относительно ObjectLeft и ObjectRight
        struct DelayRelation {
            // Флаг применения правила.
            // [XmlAttribute("enabled")] public Bool enabled_;
            XmlAttr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [XmlAttribute("valueType")] public valueType valueType_;
            XmlAttr<valueType> valueType_;
            // Значение константы в правилах выравнивания задержек.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("constant", DataType = "float")] public float constant_;
            XmlAttr<float> constant;
            // Параметр правила выравнивания задержек: нижний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("toleranceUnder", DataType = "float")] public float toleranceUnder_;
            XmlAttr<float> toleranceUnder;
            // Параметр правила выравнивания задержек: верхний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [XmlAttribute("toleranceOver", DataType = "float")] public float toleranceOver_;
            XmlAttr<float> toleranceOver;
            // Первый объект воздействия правила взаимного выравнивания задержек.
            // [XmlElement("ObjectLeft")] public ObjectSignal ObjectLeft_;
            ObjectSignal ObjectLeft_; // FIXME ???
            // Второй объект воздействия правила взаимного выравнивания задержек.
            // [XmlElement("ObjectRight")] public ObjectSignal ObjectRight_;
            ObjectSignal ObjectRight_; // FIXME ???
        };
        // Правила выравнивания задержек для группы цепей или группы дифференциальных пар.
        // [XmlElement("DelayEqual")] public List<DelayEqual> DelayEquals_;
        XmlArrayElem<DelayEqual> DelayEquals;
        // Правила задания абсолютного значения задержки.
        // [XmlElement("DelayConstant")] public List<DelayConstant> DelayConstants_;
        XmlArrayElem<DelayConstant> DelayConstants;
        // Правила взаимного выравнивания задержек.
        /// \note !Правила несимметричны относительно ObjectLeft и ObjectRight
        // [XmlElement("DelayRelation")] public List<DelayRelation> DelayRelations_;
        XmlArrayElem<DelayRelation> DelayRelations;
    };
    // Настройки поиска сигналов.
    struct SignalSearchSettings {
        // Правило именования цепей дифференциальных сигналов.
        struct RuleDiffSignalNetsNames {
            // Флаг применения правила.
            XmlAttr<Bool> enabled;
            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь позитивного сигнала.
            XmlAttr<QString> posStr;
            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь негативного сигнала.
            XmlAttr<QString> negStr;
            operator bool() const { return +enabled; }
        };
        // Список цепей, исключённых из поиска сигналов.
        struct ExcludedNets {
            // Минимальное количество контактов в силовой цепи. Параметр используется для автоматического определения силовых цепей.
            // [XmlAttribute("minPinsNumber", DataType = "int")] public int minPinsNumber_;
            XmlAttr<int> minPinsNumber;
            // Cсылки на цепи.
            // [XmlElement("NetRef")] public List<NetRef> NetRefs_;
            XmlArray<NetRef> NetRefs;
        };
        // Максимальное число цепей в сигнальном кластере. Параметр используется при автоматическом определении цепей сигнального кластера.
        // [XmlAttribute("maxNetsInCluster", DataType = "int")] public int maxNetsInCluster_;
        XmlAttr<int> maxNetsInCluster;
        // Автоматически задавать связи.
        // [XmlAttribute("createPinPairs")] public Bool createPinPairs_;
        XmlAttr<Bool> createPinPairs;
        /* public bool createPinPairsSpecified_ */
        // Правила именования цепей дифференциальных сигналов.
        /// \note !Порядок следования правил в этой секции определяет приоритет правил. Правила следуют в порядке убывания приоритета.
        // [XmlArray("RulesDiffSignalNetsNames")][XmlArrayItem("RuleDiffSignalNetsNames")] public List<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames_;
        XmlArrayElem<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames;
        // Список цепей, исключённых из поиска сигналов.
        // [XmlElement("ExcludedNets")] public ExcludedNets excludedNets;
        ExcludedNets excludedNets;
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Волновые сопротивления и правила разводки сигналов.
    // [XmlArray("RulesImpedances")][XmlArrayItem(Impedance),
    // XmlArrayItem(ImpedanceDiff)] public List<Object> RulesImpedances_;
    XmlArrayElem<XmlVariant<Impedance, ImpedanceDiff>> RulesImpedances;
    // Сигнальные кластеры цепей.
    // [XmlArray("SignalClusters")][XmlArrayItem("SignalCluster")] public List<SignalCluster> SignalClusters_;
    XmlArrayElem<SignalCluster> SignalClusters;
    // Дифференциальные сигналы.
    // [XmlArray("DiffSignals")][XmlArrayItem("DiffSignal")] public List<DiffSignal> DiffSignals_;
    XmlArrayElem<DiffSignal> DiffSignals;
    // Группы сигналов.
    // [XmlArray("SignalGroups")][XmlArrayItem("SignalGroup")] public List<SignalGroup> SignalGroups_;
    XmlArrayElem<SignalGroup> SignalGroups;
    // Правила выравнивания задержек.
    // [XmlElement("RulesDelay")] public RulesDelay rulesDelay;
    RulesDelay rulesDelay;
    // Настройки автоматического поиска сигналов.
    // [XmlElement("SignalSearchSettings")] public SignalSearchSettings signalSearchSettings;
    SignalSearchSettings signalSearchSettings;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса HiSpeedRules. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    // Переименование ссылок на компонент, если его имя изменилось
    /// \param '1 \brief старое имя компонента
    /// \param '1 \brief новое имя компонента
    void Rename_compName(const QString& oldname, const QString& newname);
    /***********************************************************************/
};
} // namespace TopoR
