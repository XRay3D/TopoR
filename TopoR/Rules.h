#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Правила».
/// \note !Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
struct Rules {
    // Описание правила ширины проводников.
    struct WidthOfWires {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        /* public bool enabledSpecified_ */
        // Параметр правила ширины проводников: минимальная ширина проводника.
        // [Xml::Attribute("widthMin", DataType = "double")] public double widthMin_;
        Xml::Attr<double> widthMin;
        // Параметр правила ширины проводников: номинальная ширина проводника.
        // [Xml::Attribute("widthNom", DataType = "double")] public double widthNom_;
        Xml::Attr<double> widthNom;
        // Ссылка на слои. См. также LayersRefs_
        /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
        // [Xml::Element(AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef)] public Object LayersRef_;
        Xml::Variant<
            AllLayers,
            AllLayersInner,
            AllLayersInnerSignal,
            AllLayersSignal,
            AllLayersOuter,
            LayerGroupRef,
            LayerRef // NOTE ???
            >
            LayersRef;
        // Ссылка на слои. См. также LayersRef_
        /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
        // [Xml::Element("LayerRef")] public List<LayerRef> LayersRefs_;
        Xml::ArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected")][Xml::ArrayItem(NetRef,NetGroupRef,AllNets)] public List<Object> ObjectsAffected_;
        Xml::ArrayElem<Xml::Variant<NetRef, NetGroupRef, AllNets>> ObjectsAffected;
    };
    // Описание правила зазоров между цепями.
    struct ClearanceNetToNet {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        /* public bool enabledSpecified_ */
        // Параметр правила зазоров между цепями: минимальный зазор.
        // [Xml::Attribute("clrnMin", DataType = "double")] public double clrnMin_;
        Xml::Attr<double> clrnMin;
        // Параметр правила зазоров между цепями: номинальный зазор.
        // [Xml::Attribute("clrnNom", DataType = "double")] public double clrnNom_;
        Xml::Attr<double> clrnNom;
        // Ссылка на слои. См. также LayersRefs_
        /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
        // [Xml::Element(AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef)] public Object LayersRef_;
        Xml::Variant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef_;
        // Ссылка на слои. См. также LayersRef_
        /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
        // [Xml::Element("LayerRef")] public List<LayerRef> LayersRefs_;
        Xml::ArrayElem<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected")][Xml::ArrayItem(NetRef,NetGroupRef,AllNets,SignalRef,DiffSignalRef,SignalGroupRef)] public List<Object> ObjectsAffected_;
        Xml::ArrayElem<Xml::Variant<NetRef, NetGroupRef, AllNets, SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
    };
    // Описание правила зазоров между компонентами.
    struct ClearanceCompToComp {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        /* public bool enabledSpecified_ */
        // Параметр правила зазоров между цепями: минимальный зазор.
        // [Xml::Attribute("clrn", DataType = "double")] public double clrn_;
        Xml::Attr<double> clrn;
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected")][Xml::ArrayItem(ComponentRef,CompGroupRef,AllComps)] public List<Object> ObjectsAffected_;
        Xml::ArrayElem<Xml::Variant<ComponentRef, CompGroupRef, AllComps>> ObjectsAffected;
    };
    // Описание зазоров до края платы.
    struct RulesClearancesToBoard {
        // Устанавливает зазор от проводников до края платы.
        // [Xml::Attribute("wires", DataType = "double")] public double clrn_;
        Xml::Attr<double> wires;
        // Устанавливает зазор от компонентов до края платы.
        // [Xml::Attribute("comps", DataType = "double")] public double comps_;
        Xml::Attr<double> comps;
    };
    // Описание правила назначения цепям стеков переходных отверстий.
    struct ViastacksOfNets {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        /* public bool enabledSpecified_ */
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected")][Xml::ArrayItem(NetRef,NetGroupRef,AllNets,SignalRef,DiffSignalRef,SignalGroupRef)] public List<Object> ObjectsAffected_;
        Xml::ArrayElem<Xml::Variant<NetRef, NetGroupRef, AllNets, SignalRef, DiffSignalRef, SignalGroupRef>> ObjectsAffected;
        // Назначенные типы переходных отверстий.
        // [Xml::Array("Viastacks")][Xml::ArrayItem(AllViastacks,AllViastacksThrough,AllViastacksNotThrough,ViastackRef)] public List<Object> Viastacks_;
        Xml::ArrayElem<Xml::Variant<AllViastacks, AllViastacksThrough, AllViastacksNotThrough, ViastackRef>> Viastacks;
    };
    // Описание правила назначения цепям опорных слоёв.
    struct PlaneLayerNets {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        // Ссылка на слои. См. также LayersRefs_
        /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
        // [Xml::Element(AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef)] public Object LayersRef_;
        Xml::Variant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayerRef_;
        // Ссылка на слои. См. также LayersRef_
        /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
        // [Xml::Element("LayerRef")] public List<LayerRef> LayersRefs_;
        Xml::Array<LayerRef> LayersRefs;
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected")][Xml::ArrayItem("NetRef")] public List<NetRef> ObjectsAffected_;
        Xml::ArrayElem<NetRef> ObjectsAffected;
    };
    // Описание правила назначения цепям сигнальных слоёв.
    struct SignalLayerNets {
        // Флаг применения правила.
        // [Xml::Attribute("enabled")] public Bool enabled_;
        Xml::Attr<Bool> enabled;
        /* public bool enabledSpecified_ */
        // Ссылка на слои. См. также LayersRefs_
        /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
        // [Xml::Element(AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef)] public Object LayersRef_;
        // Xml::Variant<AllLayers,
        //     AllLayersInner,
        //     AllLayersInnerSignal,
        //     AllLayersSignal,
        //     AllLayersOuter,
        //     LayerGroupRef>
        //     LayersRef;
        // Ссылка на слои. См. также LayersRef_
        /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
        // [Xml::Element("LayerRef")] public List<LayerRef> LayersRefs_;
        Xml::Array<Xml::Variant<AllLayers,
            AllLayersInner,
            AllLayersInnerSignal,
            AllLayersSignal,
            AllLayersOuter,
            LayerGroupRef,
            LayerRef>>
            LayersRefs;
        // Объекты воздействия правила.
        // [Xml::Array("ObjectsAffected"),NetRef,NetGroupRef)] public List<Object> ObjectsAffected_;
        Xml::ArrayElem<Xml::Variant<NetRef, NetGroupRef>> ObjectsAffected;
    };
    // Свойства цепи.
    struct NetProperty {
        // Свойство цепи: гибкая фиксация.
        // [Xml::Attribute("flexfix")] public Bool flexfix_;
        Xml::Attr<Bool, NoOpt> flexfix;
        /* public bool flexfixSpecified_ */
        // Свойство цепи: флаг трассировки для автоматического трассировщика.
        // [Xml::Attribute("route")] public Bool route_;
        Xml::Attr<Bool> route;
        /* public bool routeSpecified_ */
        // Ссылка на цепь.
        // [Xml::Element("NetRef")] public List<NetRef> NetRefs_;
        Xml::Array<NetRef> NetRefs;
    };
    // Настройки подключения к углам прямоугольных контактных площадок.
    struct PadConnectSettings {
        // Настройка подключения к углам прямоугольных контактных площадок: режим подключения.
        // [Xml::Attribute("mode")] public mode_PadConnectSettings mode_;
        Xml::Attr<mode_PadConnectSettings, NoOpt> mode;
        // Ссылки на стеки контактных площадок.
        // [Xml::Element("PadstackRef")] public List<PadstackRef> PadstackRefs_;
        Xml::Array /*Elem*/<PadstackRef> PadstackRefs;
        // Ссылки на контакты.
        // [Xml::Element("PinRef")] public List<PinRef> PinRefs_;
        Xml::ArrayElem<PinRef> PinRefs;
        // Ссылки на выводы посадочных мест.
        // [Xml::Element("PadRef")] public List<PadRef> PadRefs_;
        Xml::ArrayElem<PadRef> PadRefs;
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Правила ширин проводников.
    // [Xml::Array("RulesWidthOfWires")][Xml::ArrayItem("WidthOfWires")] public List<WidthOfWires> RulesWidthOfWires_;
    Xml::ArrayElem<WidthOfWires> RulesWidthOfWires;
    // Правила зазоров между цепями.
    // [Xml::Array("RulesClearancesNetToNet")][Xml::ArrayItem("ClearanceNetToNet")] public List<ClearanceNetToNet> RulesClearancesNetToNet_;
    Xml::ArrayElem<ClearanceNetToNet> RulesClearancesNetToNet;
    // Правила зазоров между компонентами.
    // [Xml::Array("RulesClearancesCompToComp")][Xml::ArrayItem("ClearanceCompToComp")] public List<ClearanceCompToComp> RulesClearancesCompToComp_;
    Xml::ArrayElem<ClearanceCompToComp> RulesClearancesCompToComp;
    // Правило зазоров до края платы.
    // [Xml::Element("RulesClearancesToBoard")] public RulesClearancesToBoard rulesClearancesToBoard;
    RulesClearancesToBoard rulesClearancesToBoard;
    // Правила назначения цепям стеков переходных отверстий.
    // [Xml::Array("RulesViastacksOfNets")][Xml::ArrayItem("ViastacksOfNets")] public List<ViastacksOfNets> RulesViastacksOfNets_;
    Xml::ArrayElem<ViastacksOfNets> RulesViastacksOfNets;
    // Правила назначения цепям опорных слоёв.
    // [Xml::Array("RulesPlaneLayersNets")][Xml::ArrayItem("PlaneLayerNets")] public List<PlaneLayerNets> RulesPlaneLayersNets_;
    Xml::ArrayElem<PlaneLayerNets> RulesPlaneLayersNets;
    // Правила назначения цепям сигнальных слоёв.
    // [Xml::Array("RulesSignalLayersNets")][Xml::ArrayItem("SignalLayerNets")] public List<SignalLayerNets> RulesSignalLayersNets_;
    Xml::ArrayElem<SignalLayerNets> RulesSignalLayersNets;
    // Свойства цепей
    // [Xml::Array("NetProperties")][Xml::ArrayItem("NetProperty")] public List<NetProperty> NetProperties_;
    Xml::ArrayElem<NetProperty> NetProperties;
    // Настройки подключения к углам прямоугольных контактных площадок.
    // [Xml::Element("PadConnectSettings")] public PadConnectSettings padConnectSettings;
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
