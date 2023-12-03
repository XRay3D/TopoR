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

namespace TopoR_PCB_Classes {

// Раздел «Правила для высокоскоростных устройств».
struct HiSpeedRules {

    // Волновое сопротивление и правила разводки сигналов по слоям.
    struct Impedance {
        struct LayerRule_Impendance {

            // Ширина проводника.

            /* [XmlAttribute("width", DataType = "float")] public float width_; */
            XmlAttr<float> width;
            float width_ = 0.0F;

            // Ссылка на слой.

            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;
        };

        // Имя объекта или ссылка на именованный объект.

        /* [XmlAttribute("name")] public string name_; */
        QString name;

        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.

        /* [XmlAttribute("Z0", DataType = "float")] public float z0_; */
        XmlAttr<float> Z0;
        float z0_ = 0.0F;

        // Правило разводки сигнала для слоя.

        /* [XmlElement("LayerRule")] public List<LayerRule_Impendance> LayerImpedanceRules_; */
        std::vector<LayerRule_Impendance> LayerImpedanceRules;
    };

    // Волновое сопротивление и правила разводки сигналов по слоям для дифференциальных сигналов.
    struct ImpedanceDiff {
        struct LayerRule_ImpendanceDiff {

            // Ширина проводника.

            /* [XmlAttribute("width", DataType = "float")] public float width_; */
            XmlAttr<float> width;
            float width_ = 0.0F;

            // Параметр правила разводки дифференциальных пар: зазор между проводниками пары.

            /* [XmlAttribute("gap", DataType = "float")] public float gap_; */
            XmlAttr<float> gap;
            float gap_ = 0.0F;

            // Ссылка на слой.

            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;
        };

        // Имя объекта или ссылка на именованный объект.

        /* [XmlAttribute("name")] public string name_; */
        QString name;

        // Параметр правила разводки дифференциальной пары: значение волнового сопротивления в Омах.

        /* [XmlAttribute("Z0", DataType = "float")] public float z0_; */
        XmlAttr<float> Z0;
        float z0_ = 0.0F;

        // Правило разводки дифференциальной пары для слоя.

        /* [XmlElement("LayerRule")] public List<LayerRule_ImpendanceDiff> LayerImpedanceDiffRules_; */
        std::vector<LayerRule_ImpendanceDiff> LayerImpedanceDiffRules;
    };

    // Описание сигнального кластера цепей.
    struct SignalCluster {

        // Описание заданной связи.
        struct PinPair {

            // Ссылка на контакт источника сигнала.

            /* [XmlElement("PinRef")] public List<PinRef> PinRefs_; */
            std::vector<PinRef> PinRefs;
        };

        // Описание сигнала.
        struct Signal {

            // Имя объекта или ссылка на именованный объект.

            /* [XmlAttribute("name")] public string name_; */
            QString name;

            // Ссылка на контакт источника сигнала.

            /* [XmlElement("ReceiverPinRef")] public ReceiverPinRef ReceiverPinRef_; */
            ReceiverPinRef ReceiverPinRef_;

            // Пассивные компоненты на пути следования сигнала.

            /* [XmlArray("Components")][XmlArrayItem("CompInstanceRef")] public List<CompInstanceRef> Components_; */
            std::vector<CompInstanceRef> Components;
        };

        // Ссылка на волновое сопротивление.

        /* [XmlElement("ImpedanceRef")] public ImpedanceRef ImpedanceRef_; */
        ImpedanceRef ImpedanceRef_;

        // Ссылка на контакт источника сигнала.

        /* [XmlElement("SourcePinRef")] public SourcePinRef SourcePinRef_; */
        SourcePinRef SourcePinRef_;

        // Цепи сигнального кластера.

        /* [XmlArray("Nets")][XmlArrayItem("NetRef")] public List<NetRef> Nets_; */
        std::vector<NetRef> Nets;
        /*     public
             {
                 return Nets_?.Count > 0;
             }
        */

        // Описание заданных связей сигнального кластера.

        /* [XmlArray("PinPairs")][XmlArrayItem("PinPair")] public List<PinPair> PinPairs_; */
        std::vector<PinPair> PinPairs;
        /*   public
           {
               return PinPairs_?.Count > 0;
           }
        */

        // Ссылки на сигналы.

        /* [XmlElement("Signal")] public List<Signal> Signals_; */
        std::vector<Signal> Signals;
        /*    public
            {
                return Signals_?.Count > 0;
            }
        */
    };

    // Описание дифференциального сигнала (дифференциальной пары).
    struct DiffSignal {

        // Имя объекта или ссылка на именованный объект.

        /* [XmlAttribute("name")] public string name_; */
        QString name;

        // Параметр дифференциальной пары: допустимый разброс длины между проводниками пары.

        /* [XmlAttribute("mismatch", DataType = "float")] public float mismatch_; */
        XmlAttr<float> mismatch;
        float mismatch_ = 0.0F;

        // Ссылка на волновое сопротивление.

        /* [XmlElement("ImpedanceRef")] public ImpedanceRef ImpedanceRef_; */
        ImpedanceRef ImpedanceRef_;

        // Ссылки на сигналы.

        /* [XmlElement("SignalRef")] public List<SignalRef> SignalRefs_; */
        std::vector<SignalRef> SignalRefs;
    };

    // Описание группы сигналов.
    struct SignalGroup {
        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        QString name;

        // Ссылки на сигнал, диф.сигнал, или группу сигналов
        // <value>SignalRef, DiffSignalRef, SignalGroupRef</value>
        /* [XmlElement("SignalRef", typeof(SignalRef)),
            XmlElement("DiffSignalRef", typeof(DiffSignalRef)),
            XmlElement("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> References_; */
        std::vector<XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef>> References;
    };

    // Описание правил выравнивания задержек.
    struct RulesDelay {

        // Описание правила выравнивания задержек для группы цепей или группы дифференциальных пар.
        struct DelayEqual {

            // Флаг применения правила.

            /* [XmlAttribute("enabled")] public Bool enabled_; */
            Bool enabled_{};

            /* public bool enabledSpecified_ */

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            /* [XmlAttribute("valueType")] public valueType valueType_; */
            valueType valueType_{};

            // Параметр правила выравнивания задержек внутри группы цепей: допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("tolerance", DataType = "float")] public float tolerance_; */
            XmlAttr<float> tolerance;
            float tolerance_ = 0.0F;

            // Объекты воздействия правила.

            /* [XmlArray("ObjectsAffected")][XmlArrayItem("SignalGroupRef")] public List<SignalGroupRef> ObjectsAffected_; */
            std::vector<SignalGroupRef> ObjectsAffected;
        };

        // Описание правила задания абсолютного значения задержки.
        struct DelayConstant {

            // Флаг применения правила.

            /* [XmlAttribute("enabled")] public Bool enabled_; */
            Bool enabled_{};

            /* public bool enabledSpecified_ */

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            /* [XmlAttribute("valueType")] public valueType valueType_; */
            XmlAttr<valueType> valueType_{};

            // Значение константы в правилах выравнивания задержек.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("constant", DataType = "float")] public float constant_; */
            XmlAttr<float> constant;

            // Параметр правила выравнивания задержек: нижний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("toleranceUnder", DataType = "float")] public float toleranceUnder_; */
            XmlAttr<float> toleranceUnder;

            // Параметр правила выравнивания задержек: верхний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("toleranceOver", DataType = "float")] public float toleranceOver_; */
            XmlAttr<float> toleranceOver;

            // Объекты воздействия правила.

            /* [XmlArray("ObjectsAffected")][XmlArrayItem("SignalRef", typeof(SignalRef)),
                                             XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)),
                                             XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> ObjectsAffected_; */
            std::vector<XmlVariant<SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
        };

        // Описание правила взаимного выравнивания задержек.

        // <remarks>! Правило несимметрично относительно ObjectLeft и ObjectRight</remarks>
        struct DelayRelation {

            // Флаг применения правила.

            /* [XmlAttribute("enabled")] public Bool enabled_; */
            Bool enabled_{};

            /* public bool enabledSpecified_ */

            // Параметр правил выравнивания задержек: тип значений констант и допусков.

            /* [XmlAttribute("valueType")] public valueType valueType_; */
            valueType valueType_{};

            // Значение константы в правилах выравнивания задержек.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("constant", DataType = "float")] public float constant_; */
            XmlAttr<float> constant;
            float constant_ = 0.0F;

            // Параметр правила выравнивания задержек: нижний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("toleranceUnder", DataType = "float")] public float toleranceUnder_; */
            XmlAttr<float> toleranceUnder;
            float toleranceUnder_ = 0.0F;

            // Параметр правила выравнивания задержек: верхний допуск.

            // <remarks>! Единицы измерения значения зависят от параметра valueType и единиц заданных для всего файла(см.Units).</remarks>

            /* [XmlAttribute("toleranceOver", DataType = "float")] public float toleranceOver_; */
            XmlAttr<float> toleranceOver;
            float toleranceOver_ = 0.0F;

            // Первый объект воздействия правила взаимного выравнивания задержек.

            /* [XmlElement("ObjectLeft")] public ObjectSignal ObjectLeft_; */
            ObjectSignal ObjectLeft_;

            // Второй объект воздействия правила взаимного выравнивания задержек.

            /* [XmlElement("ObjectRight")] public ObjectSignal ObjectRight_; */
            ObjectSignal ObjectRight_;
        };

        // Правила выравнивания задержек для группы цепей или группы дифференциальных пар.

        /* [XmlElement("DelayEqual")] public List<DelayEqual> DelayEquals_; */
        std::vector<DelayEqual> DelayEquals;

        // Правила задания абсолютного значения задержки.

        /* [XmlElement("DelayConstant")] public List<DelayConstant> DelayConstants_; */
        std::vector<DelayConstant> DelayConstants;

        // Правила взаимного выравнивания задержек.

        // <remarks>! Правила несимметричны относительно ObjectLeft и ObjectRight</remarks>

        /* [XmlElement("DelayRelation")] public List<DelayRelation> DelayRelations_; */
        std::vector<DelayRelation> DelayRelations;
    };

    // Настройки поиска сигналов.
    struct SignalSearchSettings {

        // Правило именования цепей дифференциальных сигналов.
        struct RuleDiffSignalNetsNames {

            // Флаг применения правила.

            /* [XmlAttribute("enabled")] public Bool enabled_; */
            Bool enabled_{};

            /* public bool enabledSpecified_ */

            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь позитивного сигнала.

            /* [XmlAttribute("posStr")] public string posStr_; */
            QString posStr;

            // Параметр правила именования цепей дифференциальных сигналов: подстрока, определяющая цепь негативного сигнала.

            /* [XmlAttribute("negStr")] public string negStr_; */
            QString negStr;
        };

        // Список цепей, исключённых из поиска сигналов.
        struct ExcludedNets {

            // Минимальное количество контактов в силовой цепи. Параметр используется для автоматического определения силовых цепей.

            /* [XmlAttribute("minPinsNumber", DataType = "int")] public int minPinsNumber_; */
            XmlAttr<int> minPinsNumber;
            int minPinsNumber_ = 0;

            // Cсылки на цепи.

            /* [XmlElement("NetRef")] public List<NetRef> NetRefs_; */
            std::vector<NetRef> NetRefs;
        };

        // Максимальное число цепей в сигнальном кластере. Параметр используется при автоматическом определении цепей сигнального кластера.

        /* [XmlAttribute("maxNetsInCluster", DataType = "int")] public int maxNetsInCluster_; */
        XmlAttr<int> maxNetsInCluster;
        int maxNetsInCluster_ = 0;

        // Автоматически задавать связи.

        /* [XmlAttribute("createPinPairs")] public Bool createPinPairs_; */
        Bool createPinPairs_{};

        /* public bool createPinPairsSpecified_ */

        // Правила именования цепей дифференциальных сигналов.

        // <remarks>! Порядок следования правил в этой секции определяет приоритет правил. Правила следуют в порядке убывания приоритета.</remarks>

        /* [XmlArray("RulesDiffSignalNetsNames")][XmlArrayItem("RuleDiffSignalNetsNames")] public List<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames_; */
        std::vector<RuleDiffSignalNetsNames> RulesDiffSignalNetsNames;

        // Список цепей, исключённых из поиска сигналов.

        /* [XmlElement("ExcludedNets")] public ExcludedNets ExcludedNets_; */
        ExcludedNets ExcludedNets_;
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string version_; */
    QString version;

    // Волновые сопротивления и правила разводки сигналов.

    /* [XmlArray("RulesImpedances")][XmlArrayItem("Impedance", typeof(Impedance)),
XmlArrayItem("ImpedanceDiff", typeof(ImpedanceDiff))] public List<Object> RulesImpedances_; */
    std::vector<XmlVariant<Impedance, ImpedanceDiff>> RulesImpedances;

    // Сигнальные кластеры цепей.

    /* [XmlArray("SignalClusters")][XmlArrayItem("SignalCluster")] public List<SignalCluster> SignalClusters_; */
    std::vector<SignalCluster> SignalClusters;

    // Дифференциальные сигналы.

    /* [XmlArray("DiffSignals")][XmlArrayItem("DiffSignal")] public List<DiffSignal> DiffSignals_; */
    std::vector<DiffSignal> DiffSignals;

    // Группы сигналов.

    /* [XmlArray("SignalGroups")][XmlArrayItem("SignalGroup")] public List<SignalGroup> SignalGroups_; */
    std::vector<SignalGroup> SignalGroups;

    // Правила выравнивания задержек.

    /* [XmlElement("RulesDelay")] public RulesDelay RulesDelay_; */
    RulesDelay RulesDelay_;

    // Настройки автоматического поиска сигналов.

    /* [XmlElement("SignalSearchSettings")] public SignalSearchSettings SignalSearchSettings_; */
    SignalSearchSettings SignalSearchSettings_;

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

} // namespace TopoR_PCB_Classes
