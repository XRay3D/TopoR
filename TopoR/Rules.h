#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Правила».
// <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
struct Rules {
    // Описание правила ширины проводников.
    struct WidthOfWires {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Параметр правила ширины проводников: минимальная ширина проводника.
        /* [XmlAttribute("widthMin", DataType = "float")] public float widthMin_; */
        XmlAttr<float> widthMin;
        float widthMin_ = 0.0F;
        // Параметр правила ширины проводников: номинальная ширина проводника.
        /* [XmlAttribute("widthNom", DataType = "float")] public float widthNom_; */
        XmlAttr<float> widthNom;
        float widthNom_ = 0.0F;
        // Ссылка на слои. См. также LayersRefs_
        // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
        /* [XmlElement("AllLayers", typeof(AllLayers)),
            XmlElement("AllLayersInner", typeof(AllLayersInner)),
            XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
            XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
            XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
            XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
        XmlVariant<
            AllLayers,
            AllLayersInner,
            AllLayersInnerSignal,
            AllLayersSignal,
            AllLayersOuter,
            LayerGroupRef>
            LayersRef_;
        // Ссылка на слои. См. также LayersRef_
        // <remarks>! При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов. </remarks>
        /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
        XmlArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)),
            XmlArrayItem("NetGroupRef", typeof(NetGroupRef)),
            XmlArrayItem("AllNets", typeof(AllNets))] public List<Object> ObjectsAffected_; */
        XmlArrayElem<XmlVariant<NetRef, NetGroupRef, AllNets>> ObjectsAffected;
    };
    // Описание правила зазоров между цепями.
    struct ClearanceNetToNet {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Параметр правила зазоров между цепями: минимальный зазор.
        /* [XmlAttribute("clrnMin", DataType = "float")] public float clrnMin_; */
        XmlAttr<float> clrnMin;
        float clrnMin_ = 0.0F;
        // Параметр правила зазоров между цепями: номинальный зазор.
        /* [XmlAttribute("clrnNom", DataType = "float")] public float clrnNom_; */
        XmlAttr<float> clrnNom;
        float clrnNom_ = 0.0F;
        // Ссылка на слои. См. также LayersRefs_
        // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
        /* [XmlElement("AllLayers", typeof(AllLayers)),
            XmlElement("AllLayersInner", typeof(AllLayersInner)),
            XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
            XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
            XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
            XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
        XmlVariant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef_;
        // Ссылка на слои. См. также LayersRef_
        // <remarks>! При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов. </remarks>
        /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
        XmlArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)),
            XmlArrayItem("NetGroupRef", typeof(NetGroupRef)),
            XmlArrayItem("AllNets", typeof(AllNets)),
            XmlArrayItem("SignalRef", typeof(SignalRef)),
            XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)),
            XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> ObjectsAffected_; */
        XmlArrayElem<XmlVariant<NetRef, NetGroupRef, AllNets, SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
    };
    // Описание правила зазоров между компонентами.
    struct ClearanceCompToComp {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Параметр правила зазоров между цепями: минимальный зазор.
        /* [XmlAttribute("clrn", DataType = "float")] public float clrn_; */
        XmlAttr<float> clrn;
        float clrn_ = 0.0F;
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][XmlArrayItem("ComponentRef", typeof(ComponentRef)),
            XmlArrayItem("CompGroupRef", typeof(CompGroupRef)),
            XmlArrayItem("AllComps", typeof(AllComps))] public List<Object> ObjectsAffected_; */
        XmlArrayElem<XmlVariant<ComponentRef, CompGroupRef, AllComps>> ObjectsAffected;
    };
    // Описание зазоров до края платы.
    struct RulesClearancesToBoard {
        // Устанавливает зазор от проводников до края платы.
        /* [XmlAttribute("wires", DataType = "float")] public float clrn_; */
        XmlAttr<float> wires;
        float clrn_ = 0.0F;
        // Устанавливает зазор от компонентов до края платы.
        /* [XmlAttribute("comps", DataType = "float")] public float comps_; */
        XmlAttr<float> comps;
        float comps_ = 0.0F;
    };
    // Описание правила назначения цепям стеков переходных отверстий.
    struct ViastacksOfNets {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)),
            XmlArrayItem("NetGroupRef", typeof(NetGroupRef)),
            XmlArrayItem("AllNets", typeof(AllNets)),
            XmlArrayItem("SignalRef", typeof(SignalRef)),
            XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)),
            XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> ObjectsAffected_; */
        XmlArrayElem<XmlVariant<NetRef, NetGroupRef, AllNets, SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
        // Назначенные типы переходных отверстий.
        /* [XmlArray("Viastacks")][XmlArrayItem("AllViastacks", typeof(AllViastacks)),
            XmlArrayItem("AllViastacksThrough", typeof(AllViastacksThrough)),
            XmlArrayItem("AllViastacksNotThrough", typeof(AllViastacksNotThrough)),
            XmlArrayItem("ViastackRef", typeof(ViastackRef))] public List<Object> Viastacks_; */
        XmlArrayElem<XmlVariant<AllViastacks, AllViastacksThrough, AllViastacksNotThrough, ViastackRef>> Viastacks;
    };
    // Описание правила назначения цепям опорных слоёв.
    struct PlaneLayerNets {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Ссылка на слои. См. также LayersRefs_
        // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
        /* [XmlElement("AllLayers", typeof(AllLayers)),
        XmlElement("AllLayersInner", typeof(AllLayersInner)),
        XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
        XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
        XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
        XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
        XmlVariant<AllLayers,
            AllLayersInner,
            AllLayersInnerSignal,
            AllLayersSignal,
            AllLayersOuter,
            LayerGroupRef>
            LayersRef_;
        // Ссылка на слои. См. также LayersRef_
        // <remarks>! При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов. </remarks>
        /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
        XmlArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][XmlArrayItem("NetRef")] public List<NetRef> ObjectsAffected_; */
        XmlArrayElem<NetRef> ObjectsAffected;
    };
    // Описание правила назначения цепям сигнальных слоёв.
    struct SignalLayerNets {
        // Флаг применения правила.
        /* [XmlAttribute("enabled")] public Bool enabled_; */
        Bool enabled_{};
        /* public bool enabledSpecified_ */
        // Ссылка на слои. См. также LayersRefs_
        // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
        /* [XmlElement("AllLayers", typeof(AllLayers)),
            XmlElement("AllLayersInner", typeof(AllLayersInner)),
            XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
            XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
            XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
            XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
        XmlVariant<AllLayers,
            AllLayersInner,
            AllLayersInnerSignal,
            AllLayersSignal,
            AllLayersOuter,
            LayerGroupRef>
            LayersRef_;
        // Ссылка на слои. См. также LayersRef_
        // <remarks>! При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов. </remarks>
        /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
        XmlArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        /* [XmlArray("ObjectsAffected")][
            XmlArrayItem("NetRef", typeof(NetRef)),
            XmlArrayItem("NetGroupRef", typeof(NetGroupRef))] public List<Object> ObjectsAffected_; */
        XmlArrayElem<XmlVariant<NetRef, NetGroupRef>> ObjectsAffected;
    };
    // Свойства цепи.
    struct NetProperty {
        // Свойство цепи: гибкая фиксация.
        /* [XmlAttribute("flexfix")] public Bool flexfix_; */
        Bool flexfix_{};
        /* public bool flexfixSpecified_ */
        // Свойство цепи: флаг трассировки для автоматического трассировщика.
        /* [XmlAttribute("route")] public Bool route_; */
        Bool route_{};
        /* public bool routeSpecified_ */
        // Ссылка на цепь.
        /* [XmlElement("NetRef")] public List<NetRef> NetRefs_; */
        XmlArrayElem<NetRef> NetRefs;
    };
    // Настройки подключения к углам прямоугольных контактных площадок.
    struct PadConnectSettings {
        // Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
        /* [XmlAttribute("mode")] public mode_PadConnectSettings mode_; */
        mode_PadConnectSettings mode_{};
        // Ссылки на стеки контактных площадок.
        /* [XmlElement("PadstackRef")] public List<PadstackRef> PadstackRefs_; */
        XmlArrayElem<PadstackRef> PadstackRefs;
        // Ссылки на контакты.
        /* [XmlElement("PinRef")] public List<PinRef> PinRefs_; */
        XmlArrayElem<PinRef> PinRefs;
        // Ссылки на выводы посадочных мест.
        /* [XmlElement("PadRef")] public List<PadRef> PadRefs_; */
        XmlArrayElem<PadRef> PadRefs;
    };
    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;
    // Правила ширин проводников.
    /* [XmlArray("RulesWidthOfWires")][XmlArrayItem("WidthOfWires")] public List<WidthOfWires> RulesWidthOfWires_; */
    XmlArrayElem<WidthOfWires> RulesWidthOfWires;
    // Правила зазоров между цепями.
    /* [XmlArray("RulesClearancesNetToNet")][XmlArrayItem("ClearanceNetToNet")] public List<ClearanceNetToNet> RulesClearancesNetToNet_; */
    XmlArrayElem<ClearanceNetToNet> RulesClearancesNetToNet;
    // Правила зазоров между компонентами.
    /* [XmlArray("RulesClearancesCompToComp")][XmlArrayItem("ClearanceCompToComp")] public List<ClearanceCompToComp> RulesClearancesCompToComp_; */
    XmlArrayElem<ClearanceCompToComp> RulesClearancesCompToComp;
    // Правило зазоров до края платы.
    /* [XmlElement("RulesClearancesToBoard")] public RulesClearancesToBoard rulesClearancesToBoard; */
    RulesClearancesToBoard rulesClearancesToBoard;
    // Правила назначения цепям стеков переходных отверстий.
    /* [XmlArray("RulesViastacksOfNets")][XmlArrayItem("ViastacksOfNets")] public List<ViastacksOfNets> RulesViastacksOfNets_; */
    XmlArrayElem<ViastacksOfNets> RulesViastacksOfNets;
    // Правила назначения цепям опорных слоёв.
    /* [XmlArray("RulesPlaneLayersNets")][XmlArrayItem("PlaneLayerNets")] public List<PlaneLayerNets> RulesPlaneLayersNets_; */
    XmlArrayElem<PlaneLayerNets> RulesPlaneLayersNets;
    // Правила назначения цепям сигнальных слоёв.
    /* [XmlArray("RulesSignalLayersNets")][XmlArrayItem("SignalLayerNets")] public List<SignalLayerNets> RulesSignalLayersNets_; */
    XmlArrayElem<SignalLayerNets> RulesSignalLayersNets;
    // Свойства цепей
    /* [XmlArray("NetProperties")][XmlArrayItem("NetProperty")] public List<NetProperty> NetProperties_; */
    XmlArrayElem<NetProperty> NetProperties;
    // Настройки подключения к углам прямоугольных контактных площадок.
    /* [XmlElement("PadConnectSettings")] public PadConnectSettings padConnectSettings; */
    PadConnectSettings padConnectSettings;
    /*****************************************************************
     * Здесь находятся функции для работы с элементами класса Rules. *
     * Они не являются частью формата TopoR PCB.                     *
     * ***************************************************************/
    // Переименование ссылок на компонент, если его имя изменилось
    /// \param '1 \brief старое имя компонента
    /// \param '1 \brief новое имя компонента
    void Rename_compName(const QString& oldname, const QString& newname);
};
} // namespace TopoR
