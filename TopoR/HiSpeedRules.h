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
            // [Xml::Attribute("width", DataType = "double")] public double width_;
            Xml::Attr<double> width;
            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
        // [Xml::Attribute("Z0", DataType = "double")] public double z0_;
        Xml::Attr<double> Z0;
        // Правило разводки сигнала для слоя.
        // [Xml::Element("LayerRule")] public List<LayerRule_Impendance> LayerImpedanceRules_;
        Xml::Array<LayerRule> LayerImpedanceRules;
    };
    // Волновое сопротивление и правила разводки сигналов по слоям для дифференциальных сигналов.
    struct ImpedanceDiff {
        struct LayerRule {
            // Ширина проводника.
            // [Xml::Attribute("width", DataType = "double")] public double width_;
            Xml::Attr<double> width;
            // Параметр правила разводки дифференциальных пар: зазор между проводниками пары.
            // [Xml::Attribute("gap", DataType = "double")] public double gap_;
            Xml::Attr<double> gap;
            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.
        // [Xml::Attribute("Z0", DataType = "double")] public double z0_;
        Xml::Attr<double> Z0;
        // Правило разводки дифференциальной пары для слоя.
        // [Xml::Element("LayerRule")] public List<LayerRule_ImpendanceDiff> LayerImpedanceDiffRules_;
        Xml::Array<LayerRule> LayerImpedanceDiffRules;
    };
    // Описание сигнального кластера цепей.
    struct SignalCluster {
        // Описание заданной связи.
        struct PinPair {
            // Ссылка на контакт источника сигнала.
            // [Xml::Element("PinRef")] public List<PinRef> PinRefs_;
            Xml::Array<PinRef> PinRefs;
        };
        // Описание сигнала.
        struct Signal {
            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            // Ссылка на контакт источника сигнала.
            // [Xml::Element("ReceiverPinRef")] public ReceiverPinRef receiverPinRef;
            ReceiverPinRef receiverPinRef;
            // Пассивные компоненты на пути следования сигнала.
            // [Xml::Array("Components")][Xml::ArrayItem("CompInstanceRef")] public List<CompInstanceRef> Components_;
            Xml::ArrayElem<CompInstanceRef> Components;
        };
        // Ссылка на волновое сопротивление.
        // [Xml::Element("ImpedanceRef")] public ImpedanceRef impedanceRef;
        ImpedanceRef impedanceRef;
        // Ссылка на контакт источника сигнала.
        // [Xml::Element("SourcePinRef")] public SourcePinRef sourcePinRef;
        SourcePinRef sourcePinRef;
        // Цепи сигнального кластера.
        // [Xml::Array("Nets")][Xml::ArrayItem("NetRef")] public List<NetRef> Nets_;
        Xml::ArrayElem<NetRef> Nets;
        // Описание заданных связей сигнального кластера.
        // [Xml::Array("PinPairs")][Xml::ArrayItem("PinPair")] public List<PinPair> PinPairs_;
        Xml::ArrayElem<PinPair> PinPairs;
        // Ссылки на сигналы.
        // [Xml::Element("Signal")] public List<Signal> Signals_;
        Xml::Array<Signal> Signals;
    };
    // Описание дифференциального сигнала (дифференциальной пары).
    struct DiffSignal {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Параметр дифференциальной пары: допустимый разброс длины между проводниками пары.
        // [Xml::Attribute("mismatch", DataType = "double")] public double mismatch_;
        Xml::Attr<double> mismatch;
        // Ссылка на волновое сопротивление.
        // [Xml::Element("ImpedanceRef")] public ImpedanceRef impedanceRef;
        ImpedanceRef impedanceRef;
        // Ссылки на сигналы.
        // [Xml::Element("SignalRef")] public List<SignalRef> SignalRefs_;
        Xml::Array<SignalRef> SignalRefs;
    };
    // Описание группы сигналов.
    struct SignalGroup {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Ссылки на сигнал, диф.сигнал, или группу сигналов
        // <value>SignalRef, DiffSignalRef, SignalGroupRef</value>
        // [Xml::Element(SignalRef),
        //  Xml::Element(DiffSignalRef),
        //  Xml::Element(SignalGroupRef)] public List<Object> References_;
        Xml::Array<Xml::Variant<SignalRef, DiffSignalRef, SignalGroupRef>> References;
    };
    // Описание правил выравнивания задержек.
    struct RulesDelay {
        // Описание правила выравнивания задержек для группы цепей или группы дифференциальных пар.
        struct DelayEqual {
            // Флаг применения правила.
            // [Xml::Attribute("enabled")] public Bool enabled_;
            Xml::Attr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [Xml::Attribute("valueType")] public valueType valueType_;
            Xml::Attr<valueType> valueType_;
            // Параметр правила выравнивания задержек внутри группы цепей: допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("tolerance", DataType = "double")] public double tolerance_;
            Xml::Attr<double> tolerance;
            // Объекты воздействия правила.
            // [Xml::Array("ObjectsAffected")][Xml::ArrayItem("SignalGroupRef")] public List<SignalGroupRef> ObjectsAffected_;
            Xml::ArrayElem<SignalGroupRef> ObjectsAffected;
            bool isEmpty() const { return ObjectsAffected.empty(); } // FIXME  bugfix for generate empty DelayEqual
        };
        // Описание правила задания абсолютного значения задержки.
        struct DelayConstant {
            // Флаг применения правила.
            // [Xml::Attribute("enabled")] public Bool enabled_;
            Xml::Attr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [Xml::Attribute("valueType")] public valueType valueType_;
            Xml::Attr<valueType> valueType_;
            // Значение константы в правилах выравнивания задержек.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("constant", DataType = "double")] public double constant_;
            Xml::Attr<double> constant;
            // Параметр правила выравнивания задержек: нижний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("toleranceUnder", DataType = "double")] public double toleranceUnder_;
            Xml::Attr<double> toleranceUnder;
            // Параметр правила выравнивания задержек: верхний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("toleranceOver", DataType = "double")] public double toleranceOver_;
            Xml::Attr<double> toleranceOver;
            // Объекты воздействия правила.
            // [Xml::Array("ObjectsAffected")][Xml::ArrayItem(SignalRef),
            //  Xml::ArrayItem(DiffSignalRef),
            //  Xml::ArrayItem(SignalGroupRef)] public List<Object> ObjectsAffected_;
            Xml::ArrayElem<Xml::Variant<SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
        };
        // Описание правила взаимного выравнивания задержек.
        /// \note !Правило несимметрично относительно ObjectLeft и ObjectRight
        struct DelayRelation {
            // Флаг применения правила.
            // [Xml::Attribute("enabled")] public Bool enabled_;
            Xml::Attr<Bool> enabled;
            /* public bool enabledSpecified_ */
            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            // [Xml::Attribute("valueType")] public valueType valueType_;
            Xml::Attr<valueType> valueType_;
            // Значение константы в правилах выравнивания задержек.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("constant", DataType = "double")] public double constant_;
            Xml::Attr<double> constant;
            // Параметр правила выравнивания задержек: нижний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("toleranceUnder", DataType = "double")] public double toleranceUnder_;
            Xml::Attr<double> toleranceUnder;
            // Параметр правила выравнивания задержек: верхний допуск.
            /// \note !Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).
            // [Xml::Attribute("toleranceOver", DataType = "double")] public double toleranceOver_;
            Xml::Attr<double> toleranceOver;
            // Первый объект воздействия правила взаимного выравнивания задержек.
            // [Xml::Element("ObjectLeft")] public ObjectSignal ObjectLeft_;
            // using ObjectLeft = ObjectSignal;
            Xml::Named<ObjectSignal, "ObjectLeft"> objectLeft;   // FIXME ???
                                                                 // Второй объект воздействия правила взаимного выравнивания задержек.
                                                                 // [Xml::Element("ObjectRight")] public ObjectSignal ObjectRight_;
                                                                 // using ObjectRight = ObjectSignal;
            Xml::Named<ObjectSignal, "ObjectRight"> objectRight; // FIXME ???
        };
        // Правила выравнивания задержек для группы цепей или группы дифференциальных пар.
        // [Xml::Element("DelayEqual")] public List<DelayEqual> DelayEquals_;
        Xml::Array<DelayEqual> delayEquals;
        // Правила задания абсолютного значения задержки.
        // [Xml::Element("DelayConstant")] public List<DelayConstant> delayConstants_;
        Xml::Array<DelayConstant> delayConstants;
        // Правила взаимного выравнивания задержек.
        /// \note !Правила несимметричны относительно ObjectLeft и ObjectRight
        // [Xml::Element("DelayRelation")] public List<DelayRelation> delayRelations_;
        Xml::Array<DelayRelation> delayRelations;

        bool isEmpty() const { return delayEquals.empty() && delayConstants.empty() && delayRelations.empty(); }
    };
    // Настройки поиска сигналов.
    struct SignalSearchSettings {
        // Правило именования цепей дифференциальных сигналов.
        struct RuleDiffSignalNetsNames {
            // Флаг применения правила.
            Xml::Attr<Bool> enabled;
            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь позитивного сигнала.
            Xml::Attr<QString> posStr;
            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь негативного сигнала.
            Xml::Attr<QString> negStr;
            operator bool() const { return +enabled; }
        };
        // Список цепей, исключённых из поиска сигналов.
        struct ExcludedNets {
            // Минимальное количество контактов в силовой цепи. Параметр используется для автоматического определения силовых цепей.
            // [Xml::Attribute("minPinsNumber", DataType = "int")] public int minPinsNumber_;
            Xml::Attr<int> minPinsNumber;
            // Cсылки на цепи.
            // [Xml::Element("NetRef")] public List<NetRef> NetRefs_;
            Xml::Array<NetRef> NetRefs;
        };
        // Максимальное число цепей в сигнальном кластере. Параметр используется при автоматическом определении цепей сигнального кластера.
        // [Xml::Attribute("maxNetsInCluster", DataType = "int")] public int maxNetsInCluster_;
        Xml::Attr<int> maxNetsInCluster;
        // Автоматически задавать связи.
        // [Xml::Attribute("createPinPairs")] public Bool createPinPairs_;
        Xml::Attr<Bool> createPinPairs;
        /* public bool createPinPairsSpecified_ */
        // Правила именования цепей дифференциальных сигналов.
        /// \note !Порядок следования правил в этой секции определяет приоритет правил. Правила следуют в порядке убывания приоритета.
        // [Xml::Array("RulesDiffSignalNetsNames")][Xml::ArrayItem("RuleDiffSignalNetsNames")] public List<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames_;
        Xml::ArrayElem<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames;
        // Список цепей, исключённых из поиска сигналов.
        // [Xml::Element("ExcludedNets")] public ExcludedNets excludedNets;
        ExcludedNets excludedNets;
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Волновые сопротивления и правила разводки сигналов.
    // [Xml::Array("RulesImpedances")][Xml::ArrayItem(Impedance),
    // Xml::ArrayItem(ImpedanceDiff)] public List<Object> RulesImpedances_;
    Xml::ArrayElem<Xml::Variant<Impedance, ImpedanceDiff>> RulesImpedances;
    // Сигнальные кластеры цепей.
    // [Xml::Array("SignalClusters")][Xml::ArrayItem("SignalCluster")] public List<SignalCluster> SignalClusters_;
    Xml::ArrayElem<SignalCluster> SignalClusters;
    // Дифференциальные сигналы.
    // [Xml::Array("DiffSignals")][Xml::ArrayItem("DiffSignal")] public List<DiffSignal> DiffSignals_;
    Xml::ArrayElem<DiffSignal> DiffSignals;
    // Группы сигналов.
    // [Xml::Array("SignalGroups")][Xml::ArrayItem("SignalGroup")] public List<SignalGroup> SignalGroups_;
    Xml::ArrayElem<SignalGroup> SignalGroups;
    // Правила выравнивания задержек.
    // [Xml::Element("RulesDelay")] public RulesDelay rulesDelay;
    RulesDelay rulesDelay;
    // Настройки автоматического поиска сигналов.
    // [Xml::Element("SignalSearchSettings")] public SignalSearchSettings signalSearchSettings;
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
