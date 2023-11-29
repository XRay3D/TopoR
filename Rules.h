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

// Раздел «Правила».

// <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
class Rules {

    // Описание правила ширины проводников.

public:
    class WidthOfWires {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Параметр правила ширины проводников: минимальная ширина проводника.

        //[XmlAttribute("widthMin", DataType = "float")] public float _widthMin;
        float _widthMin = 0.0F;

        // Параметр правила ширины проводников: номинальная ширина проводника.

        //[XmlAttribute("widthNom", DataType = "float")] public float _widthNom;
        float _widthNom = 0.0F;

        // Ссылка на слои. См. также _LayersRefs

        // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

        //[XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
        std::any _LayersRef;

        // Ссылка на слои. См. также _LayersRef

        // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

        //[XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
        std::vector<std::optional<LayerRef>> _LayersRefs;
        bool ShouldSerialize_LayersRefs();

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets))] public List<Object> _ObjectsAffected;
        std::vector<std::any> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();
    };

    // Описание правила зазоров между цепями.

public:
    class ClearanceNetToNet {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Параметр правила зазоров между цепями: минимальный зазор.

        //[XmlAttribute("clrnMin", DataType = "float")] public float _clrnMin;
        float _clrnMin = 0.0F;

        // Параметр правила зазоров между цепями: номинальный зазор.

        //[XmlAttribute("clrnNom", DataType = "float")] public float _clrnNom;
        float _clrnNom = 0.0F;

        // Ссылка на слои. См. также _LayersRefs

        // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

        //[XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
        std::any _LayersRef;

        // Ссылка на слои. См. также _LayersRef

        // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

        //[XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
        std::vector<std::optional<LayerRef>> _LayersRefs;
        bool ShouldSerialize_LayersRefs();

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets)), XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
        std::vector<std::any> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();
    };

    // Описание правила зазоров между компонентами.

public:
    class ClearanceCompToComp {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Параметр правила зазоров между цепями: минимальный зазор.

        //[XmlAttribute("clrn", DataType = "float")] public float _clrn;
        float _clrn = 0.0F;

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("ComponentRef", typeof(ComponentRef)), XmlArrayItem("CompGroupRef", typeof(CompGroupRef)), XmlArrayItem("AllComps", typeof(AllComps))] public List<Object> _ObjectsAffected;
        std::vector<std::any> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();
    };

    // Описание зазоров до края платы.

public:
    class RulesClearancesToBoard {

        // Устанавливает зазор от проводников до края платы.

    public:
        //[XmlAttribute("wires", DataType = "float")] public float _clrn;
        float _clrn = 0.0F;

        // Устанавливает зазор от компонентов до края платы.

        //[XmlAttribute("comps", DataType = "float")] public float _comps;
        float _comps = 0.0F;
    };

    // Описание правила назначения цепям стеков переходных отверстий.

public:
    class ViastacksOfNets {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef)), XmlArrayItem("AllNets", typeof(AllNets)), XmlArrayItem("SignalRef", typeof(SignalRef)), XmlArrayItem("DiffSignalRef", typeof(DiffSignalRef)), XmlArrayItem("SignalGroupRef", typeof(SignalGroupRef))] public List<Object> _ObjectsAffected;
        std::vector<std::any> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();

        // Назначенные типы переходных отверстий.

        //[XmlArray("Viastacks")][XmlArrayItem("AllViastacks", typeof(AllViastacks)), XmlArrayItem("AllViastacksThrough", typeof(AllViastacksThrough)), XmlArrayItem("AllViastacksNotThrough", typeof(AllViastacksNotThrough)), XmlArrayItem("ViastackRef", typeof(ViastackRef))] public List<Object> _Viastacks;
        std::vector<std::any> _Viastacks;
        bool ShouldSerialize_Viastacks();
    };

    // Описание правила назначения цепям опорных слоёв.

public:
    class PlaneLayerNets {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Ссылка на слои. См. также _LayersRefs

        // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

        //[XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
        std::any _LayersRef;

        // Ссылка на слои. См. также _LayersRef

        // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

        //[XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
        std::vector<std::optional<LayerRef>> _LayersRefs;
        bool ShouldSerialize_LayersRefs();

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("NetRef")] public List<NetRef> _ObjectsAffected;
        std::vector<std::optional<NetRef>> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();
    };

    // Описание правила назначения цепям сигнальных слоёв.

public:
    class SignalLayerNets {

        // Флаг применения правила.

    public:
        //[XmlAttribute("enabled")] public Bool _enabled;
        Bool _enabled{};

        //[XmlIgnore] public bool _enabledSpecified
        bool getEnabledSpecified() const;

        // Ссылка на слои. См. также _LayersRefs

        // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

        //[XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
        std::any _LayersRef;

        // Ссылка на слои. См. также _LayersRef

        // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

        //[XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
        std::vector<std::optional<LayerRef>> _LayersRefs;
        bool ShouldSerialize_LayersRefs();

        // Объекты воздействия правила.

        //[XmlArray("ObjectsAffected")][XmlArrayItem("NetRef", typeof(NetRef)), XmlArrayItem("NetGroupRef", typeof(NetGroupRef))] public List<Object> _ObjectsAffected;
        std::vector<std::any> _ObjectsAffected;
        bool ShouldSerialize_ObjectsAffected();
    };

    // Свойства цепи.

public:
    class NetProperty {

        // Свойство цепи: гибкая фиксация.

    public:
        //[XmlAttribute("flexfix")] public Bool _flexfix;
        Bool _flexfix{};

        //[XmlIgnore] public bool _flexfixSpecified
        bool getFlexfixSpecified() const;

        // Свойство цепи: флаг трассировки для автоматического трассировщика.

        //[XmlAttribute("route")] public Bool _route;
        Bool _route{};

        //[XmlIgnore] public bool _routeSpecified
        bool getRouteSpecified() const;

        // Ссылка на цепь.

        //[XmlElement("NetRef")] public List<NetRef> _NetRefs;
        std::vector<std::optional<NetRef>> _NetRefs;
        bool ShouldSerialize_NetRefs();
    };

    // Настройки подключения к углам прямоугольных контактных площадок.

public:
    class PadConnectSettings {

        // Настройка подключения к углам прямоугольных контактных площадок: режим подключения.

    public:
        //[XmlAttribute("mode")] public mode_PadConnectSettings _mode;
        mode_PadConnectSettings _mode{};

        // Ссылки на стеки контактных площадок.

        //[XmlElement("PadstackRef")] public List<PadstackRef> _PadstackRefs;
        std::vector<std::optional<PadstackRef>> _PadstackRefs;
        bool ShouldSerialize_PadstackRefs();

        // Ссылки на контакты.

        //[XmlElement("PinRef")] public List<PinRef> _PinRefs;
        std::vector<std::optional<PinRef>> _PinRefs;
        bool ShouldSerialize_PinRefs();

        // Ссылки на выводы посадочных мест.

        //[XmlElement("PadRef")] public List<PadRef> _PadRefs;
        std::vector<std::optional<PadRef>> _PadRefs;
        bool ShouldSerialize_PadRefs();
    };

    // Версия раздела.

public:
    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Правила ширин проводников.

    //[XmlArray("RulesWidthOfWires")][XmlArrayItem("WidthOfWires")] public List<WidthOfWires> _RulesWidthOfWires;
    std::vector<std::optional<WidthOfWires>> _RulesWidthOfWires;
    bool ShouldSerialize_RulesWidthOfWires();

    // Правила зазоров между цепями.

    //[XmlArray("RulesClearancesNetToNet")][XmlArrayItem("ClearanceNetToNet")] public List<ClearanceNetToNet> _RulesClearancesNetToNet;
    std::vector<std::optional<ClearanceNetToNet>> _RulesClearancesNetToNet;
    bool ShouldSerialize_RulesClearancesNetToNet();

    // Правила зазоров между компонентами.

    //[XmlArray("RulesClearancesCompToComp")][XmlArrayItem("ClearanceCompToComp")] public List<ClearanceCompToComp> _RulesClearancesCompToComp;
    std::vector<std::optional<ClearanceCompToComp>> _RulesClearancesCompToComp;
    bool ShouldSerialize_RulesClearancesCompToComp();

    // Правило зазоров до края платы.

    //[XmlElement("RulesClearancesToBoard")] public RulesClearancesToBoard _RulesClearancesToBoard;
    std::optional<RulesClearancesToBoard> _RulesClearancesToBoard;

    // Правила назначения цепям стеков переходных отверстий.

    //[XmlArray("RulesViastacksOfNets")][XmlArrayItem("ViastacksOfNets")] public List<ViastacksOfNets> _RulesViastacksOfNets;
    std::vector<std::optional<ViastacksOfNets>> _RulesViastacksOfNets;
    bool ShouldSerialize_RulesViastacksOfNets();

    // Правила назначения цепям опорных слоёв.

    //[XmlArray("RulesPlaneLayersNets")][XmlArrayItem("PlaneLayerNets")] public List<PlaneLayerNets> _RulesPlaneLayersNets;
    std::vector<std::optional<PlaneLayerNets>> _RulesPlaneLayersNets;
    bool ShouldSerialize_RulesPlaneLayersNets();

    // Правила назначения цепям сигнальных слоёв.

    //[XmlArray("RulesSignalLayersNets")][XmlArrayItem("SignalLayerNets")] public List<SignalLayerNets> _RulesSignalLayersNets;
    std::vector<std::optional<SignalLayerNets>> _RulesSignalLayersNets;
    bool ShouldSerialize_RulesSignalLayersNets();

    // Свойства цепей

    //[XmlArray("NetProperties")][XmlArrayItem("NetProperty")] public List<NetProperty> _NetProperties;
    std::vector<std::optional<NetProperty>> _NetProperties;
    bool ShouldSerialize_NetProperties();

    // Настройки подключения к углам прямоугольных контактных площадок.

    //[XmlElement("PadConnectSettings")] public PadConnectSettings _PadConnectSettings;
    std::optional<PadConnectSettings> _PadConnectSettings;

    /*****************************************************************
     * Здесь находятся функции для работы с элементами класса Rules. *
     * Они не являются частью формата TopoR PCB.                     *
     * ***************************************************************/

    // Переименование ссылок на компонент, если его имя изменилось

    // <param name="oldname">старое имя компонента</param>
    // <param name="newname">новое имя компонента</param>
    void Rename_compName(const std::string& oldname, const std::string& newname);
};
} // namespace TopoR_PCB_Classes