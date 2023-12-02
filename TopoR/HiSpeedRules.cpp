﻿#include "HiSpeedRules.h"

namespace TopoR_PCB_Classes {

bool HiSpeedRules::Impedance::ShouldSerialize_LayerImpedanceRules() { return LayerImpedanceRules.size(); }

bool HiSpeedRules::ImpedanceDiff::ShouldSerialize_LayerImpedanceDiffRules() { return LayerImpedanceDiffRules.size(); }

bool HiSpeedRules::SignalCluster::PinPair::ShouldSerialize_PinRefs() { return PinRefs.size(); }

bool HiSpeedRules::DiffSignal::ShouldSerialize_SignalRefs() { return SignalRefs.size(); }

bool HiSpeedRules::SignalGroup::ShouldSerialize_References() { return References.size(); }

bool HiSpeedRules::RulesDelay::DelayEqual::getEnabledSpecified() const { return _enabled != Bool::off; }

bool HiSpeedRules::RulesDelay::DelayEqual::ShouldSerialize_ObjectsAffected() { return ObjectsAffected.size(); }

bool HiSpeedRules::RulesDelay::DelayConstant::getEnabledSpecified() const { return _enabled != Bool::off; }

bool HiSpeedRules::RulesDelay::DelayConstant::ShouldSerialize_ObjectsAffected() { return ObjectsAffected.size(); }

bool HiSpeedRules::RulesDelay::DelayRelation::getEnabledSpecified() const { return _enabled != Bool::off; }

bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayEquals() { return DelayEquals.size(); }

bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayConstants() { return DelayConstants.size(); }

bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayRelations() { return DelayRelations.size(); }

bool HiSpeedRules::SignalSearchSettings::RuleDiffSignalNetsNames::getEnabledSpecified() const { return _enabled != Bool::off; }

bool HiSpeedRules::SignalSearchSettings::ExcludedNets::ShouldSerialize_NetRefs() { return NetRefs.size(); }

bool HiSpeedRules::SignalSearchSettings::getCreatePinPairsSpecified() const { return _createPinPairs != Bool::off; }

bool HiSpeedRules::SignalSearchSettings::ShouldSerialize_RulesDiffSignalNetsNames() { return RulesDiffSignalNetsNames.size(); }

bool HiSpeedRules::ShouldSerialize_RulesImpedances() { return RulesImpedances.size(); }

bool HiSpeedRules::ShouldSerialize_SignalClusters() { return SignalClusters.size(); }

bool HiSpeedRules::ShouldSerialize_DiffSignals() { return DiffSignals.size(); }

bool HiSpeedRules::ShouldSerialize_SignalGroups() { return SignalGroups.size(); }

void HiSpeedRules::Rename_compName(const QString& oldname, const QString& newname) {
    /* for(auto a: _SignalClusters) {
         if(a->_SourcePinRef.value()._compName == oldname)
             a->_SourcePinRef.value()._compName = newname;
         for(auto b: a.value()._Signals) {
             if(b->_ReceiverPinRef.value()._compName == oldname)
                 b->_ReceiverPinRef.value()._compName = newname;
             for(auto c: (b->_Components == nullptr ? nullptr : b.value()._Components.Where([&](std::any r) {
                     return r.value()._ReferenceName == oldname;
                 })))
                 c->_ReferenceName = newname;
         }
         for(auto b: a.value()._PinPairs)
             for(auto c: (b->_PinRefs == nullptr ? nullptr : b.value()._PinRefs.Where([&](std::any r) {
                     return r.value()._compName == oldname;
                 })))
                 c->_compName = newname;
     }*/
}

} // namespace TopoR_PCB_Classes
