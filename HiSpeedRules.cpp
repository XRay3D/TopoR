#include "HiSpeedRules.h"

namespace TopoR_PCB_Classes
{

	bool HiSpeedRules::Impedance::ShouldSerialize_LayerImpedanceRules()
	{
		return _LayerImpedanceRules.empty() ? nullptr : _LayerImpedanceRules.size() > 0;
	}

	bool HiSpeedRules::ImpedanceDiff::ShouldSerialize_LayerImpedanceDiffRules()
	{
		return _LayerImpedanceDiffRules.empty() ? nullptr : _LayerImpedanceDiffRules.size() > 0;
	}

	bool HiSpeedRules::SignalCluster::PinPair::ShouldSerialize_PinRefs()
	{
		return _PinRefs.empty() ? nullptr : _PinRefs.size() > 0;
	}

	bool HiSpeedRules::DiffSignal::ShouldSerialize_SignalRefs()
	{
		return _SignalRefs.empty() ? nullptr : _SignalRefs.size() > 0;
	}

	bool HiSpeedRules::SignalGroup::ShouldSerialize_References()
	{
		return _References.empty() ? nullptr : _References.size() > 0;
	}

	bool HiSpeedRules::RulesDelay::DelayEqual::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool HiSpeedRules::RulesDelay::DelayEqual::ShouldSerialize_ObjectsAffected()
	{
		return _ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size() > 0;
	}

	bool HiSpeedRules::RulesDelay::DelayConstant::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool HiSpeedRules::RulesDelay::DelayConstant::ShouldSerialize_ObjectsAffected()
	{
		return _ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size() > 0;
	}

	bool HiSpeedRules::RulesDelay::DelayRelation::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayEquals()
	{
		return _DelayEquals.empty() ? nullptr : _DelayEquals.size() > 0;
	}

	bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayConstants()
	{
		return _DelayConstants.empty() ? nullptr : _DelayConstants.size() > 0;
	}

	bool HiSpeedRules::RulesDelay::ShouldSerialize_DelayRelations()
	{
		return _DelayRelations.empty() ? nullptr : _DelayRelations.size() > 0;
	}

	bool HiSpeedRules::SignalSearchSettings::RuleDiffSignalNetsNames::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool HiSpeedRules::SignalSearchSettings::ExcludedNets::ShouldSerialize_NetRefs()
	{
		return _NetRefs.empty() ? nullptr : _NetRefs.size() > 0;
	}

	bool HiSpeedRules::SignalSearchSettings::getCreatePinPairsSpecified() const
	{
		return _createPinPairs != Bool::off;
	}

	bool HiSpeedRules::SignalSearchSettings::ShouldSerialize_RulesDiffSignalNetsNames()
	{
		return _RulesDiffSignalNetsNames.empty() ? nullptr : _RulesDiffSignalNetsNames.size() > 0;
	}

	bool HiSpeedRules::ShouldSerialize_RulesImpedances()
	{
		return _RulesImpedances.empty() ? nullptr : _RulesImpedances.size() > 0;
	}

	bool HiSpeedRules::ShouldSerialize_SignalClusters()
	{
		return _SignalClusters.empty() ? nullptr : _SignalClusters.size() > 0;
	}

	bool HiSpeedRules::ShouldSerialize_DiffSignals()
	{
		return _DiffSignals.empty() ? nullptr : _DiffSignals.size() > 0;
	}

	bool HiSpeedRules::ShouldSerialize_SignalGroups()
	{
		return _SignalGroups.empty() ? nullptr : _SignalGroups.size() > 0;
	}

	void HiSpeedRules::Rename_compName(const std::string &oldname, const std::string &newname)
	{
		for (auto a : _SignalClusters)
		{
			if (a->_SourcePinRef->_compName == oldname)
			{
				a->_SourcePinRef->_compName = newname;
			}
			for (auto b : a->_Signals)
			{
				if (b->_ReceiverPinRef->_compName == oldname)
				{
					b->_ReceiverPinRef->_compName = newname;
				}
				for (auto c : b->_Components == nullptr ? nullptr : b->_Components.Where([&] (std::any r)
				{
					return r->_ReferenceName == oldname;
				}))
				{
					c->_ReferenceName = newname;
				}
			}
			for (auto b : a->_PinPairs)
			{
				for (auto c : b->_PinRefs == nullptr ? nullptr : b->_PinRefs.Where([&] (std::any r)
				{
					return r->_compName == oldname;
				}))
				{
					c->_compName = newname;
				}
			}
		}
	}
}
