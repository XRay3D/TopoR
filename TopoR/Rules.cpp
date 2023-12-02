#include "Rules.h"

namespace TopoR_PCB_Classes {

bool Rules::WidthOfWires::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::WidthOfWires::ShouldSerialize_LayersRefs() { return LayersRefs_.size(); }

bool Rules::WidthOfWires::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::ClearanceNetToNet::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::ClearanceNetToNet::ShouldSerialize_LayersRefs() { return LayersRefs_.size(); }

bool Rules::ClearanceNetToNet::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::ClearanceCompToComp::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::ClearanceCompToComp::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::ViastacksOfNets::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::ViastacksOfNets::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::ViastacksOfNets::ShouldSerialize_Viastacks() { return Viastacks_.size(); }

bool Rules::PlaneLayerNets::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::PlaneLayerNets::ShouldSerialize_LayersRefs() { return LayersRefs_.size(); }

bool Rules::PlaneLayerNets::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::SignalLayerNets::getEnabledSpecified() const { return _enabled != Bool::off; }

bool Rules::SignalLayerNets::ShouldSerialize_LayersRefs() { return LayersRefs_.size(); }

bool Rules::SignalLayerNets::ShouldSerialize_ObjectsAffected() { return ObjectsAffected_.size(); }

bool Rules::NetProperty::getFlexfixSpecified() const { return _flexfix != Bool::off; }

bool Rules::NetProperty::getRouteSpecified() const { return _route != Bool::off; }

bool Rules::NetProperty::ShouldSerialize_NetRefs() { return NetRefs_.size(); }

bool Rules::PadConnectSettings::ShouldSerialize_PadstackRefs() { return PadstackRefs_.size(); }

bool Rules::PadConnectSettings::ShouldSerialize_PinRefs() { return PinRefs_.size(); }

bool Rules::PadConnectSettings::ShouldSerialize_PadRefs() { return PadRefs_.size(); }

bool Rules::ShouldSerialize_RulesWidthOfWires() { return RulesWidthOfWires_.size(); }

bool Rules::ShouldSerialize_RulesClearancesNetToNet() { return RulesClearancesNetToNet_.size(); }

bool Rules::ShouldSerialize_RulesClearancesCompToComp() { return RulesClearancesCompToComp_.size(); }

bool Rules::ShouldSerialize_RulesViastacksOfNets() { return RulesViastacksOfNets_.size(); }

bool Rules::ShouldSerialize_RulesPlaneLayersNets() { return RulesPlaneLayersNets_.size(); }

bool Rules::ShouldSerialize_RulesSignalLayersNets() { return RulesSignalLayersNets_.size(); }

bool Rules::ShouldSerialize_NetProperties() { return NetProperties_.size(); }

void Rules::Rename_compName(const QString& oldname, const QString& newname) {
    // for(auto a: (_PadConnectSettings == nullptr ? nullptr : ((_PadConnectSettings->_PadRefs.empty() ? nullptr : _PadConnectSettings->_PadRefs.Where([&](std::any aa) { return aa.value()._compName == oldname; })))))
    //     a->_compName = newname;
    // for(auto a: (_PadConnectSettings == nullptr ? nullptr : ((_PadConnectSettings->_PinRefs.empty() ? nullptr : _PadConnectSettings->_PinRefs.Where([&](std::any aa) { return aa.value()._compName == oldname; })))))
    //     a->_compName = newname;

    // for(auto a: (_RulesClearancesCompToComp.empty() ? nullptr : RulesClearancesCompToComp_.Where([&](std::any aa) { return aa::_ObjectsAffected != nullptr; })))
    //     for(auto b: a::_ObjectsAffected::OfType<ComponentRef>().Where([&](std::any bb) { return bb.value()._ReferenceName == oldname; }))
    //         b->_ReferenceName = newname;

    /****************************************************************/
}

} // namespace TopoR_PCB_Classes
