#include "Rules.h"

namespace TopoR_PCB_Classes
{

	bool Rules::WidthOfWires::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::WidthOfWires::ShouldSerialize_LayersRefs()
	{
		return (_LayersRefs.empty() ? nullptr : _LayersRefs.size()) > 0;
	}

	bool Rules::WidthOfWires::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::ClearanceNetToNet::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::ClearanceNetToNet::ShouldSerialize_LayersRefs()
	{
		return (_LayersRefs.empty() ? nullptr : _LayersRefs.size()) > 0;
	}

	bool Rules::ClearanceNetToNet::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::ClearanceCompToComp::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::ClearanceCompToComp::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::ViastacksOfNets::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::ViastacksOfNets::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::ViastacksOfNets::ShouldSerialize_Viastacks()
	{
		return (_Viastacks.empty() ? nullptr : _Viastacks.size()) > 0;
	}

	bool Rules::PlaneLayerNets::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::PlaneLayerNets::ShouldSerialize_LayersRefs()
	{
		return (_LayersRefs.empty() ? nullptr : _LayersRefs.size()) > 0;
	}

	bool Rules::PlaneLayerNets::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::SignalLayerNets::getEnabledSpecified() const
	{
		return _enabled != Bool::off;
	}

	bool Rules::SignalLayerNets::ShouldSerialize_LayersRefs()
	{
		return (_LayersRefs.empty() ? nullptr : _LayersRefs.size()) > 0;
	}

	bool Rules::SignalLayerNets::ShouldSerialize_ObjectsAffected()
	{
		return (_ObjectsAffected.empty() ? nullptr : _ObjectsAffected.size()) > 0;
	}

	bool Rules::NetProperty::getFlexfixSpecified() const
	{
		return _flexfix != Bool::off;
	}

	bool Rules::NetProperty::getRouteSpecified() const
	{
		return _route != Bool::off;
	}

	bool Rules::NetProperty::ShouldSerialize_NetRefs()
	{
		return (_NetRefs.empty() ? nullptr : _NetRefs.size()) > 0;
	}

	bool Rules::PadConnectSettings::ShouldSerialize_PadstackRefs()
	{
		return (_PadstackRefs.empty() ? nullptr : _PadstackRefs.size()) > 0;
	}

	bool Rules::PadConnectSettings::ShouldSerialize_PinRefs()
	{
		return (_PinRefs.empty() ? nullptr : _PinRefs.size()) > 0;
	}

	bool Rules::PadConnectSettings::ShouldSerialize_PadRefs()
	{
		return (_PadRefs.empty() ? nullptr : _PadRefs.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesWidthOfWires()
	{
		return (_RulesWidthOfWires.empty() ? nullptr : _RulesWidthOfWires.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesClearancesNetToNet()
	{
		return (_RulesClearancesNetToNet.empty() ? nullptr : _RulesClearancesNetToNet.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesClearancesCompToComp()
	{
		return (_RulesClearancesCompToComp.empty() ? nullptr : _RulesClearancesCompToComp.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesViastacksOfNets()
	{
		return (_RulesViastacksOfNets.empty() ? nullptr : _RulesViastacksOfNets.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesPlaneLayersNets()
	{
		return (_RulesPlaneLayersNets.empty() ? nullptr : _RulesPlaneLayersNets.size()) > 0;
	}

	bool Rules::ShouldSerialize_RulesSignalLayersNets()
	{
		return (_RulesSignalLayersNets.empty() ? nullptr : _RulesSignalLayersNets.size()) > 0;
	}

	bool Rules::ShouldSerialize_NetProperties()
	{
		return (_NetProperties.empty() ? nullptr : _NetProperties.size()) > 0;
	}

	void Rules::Rename_compName(const std::wstring &oldname, const std::wstring &newname)
	{
		for (auto a : (_PadConnectSettings == nullptr ? nullptr : ((_PadConnectSettings->_PadRefs.empty() ? nullptr : _PadConnectSettings->_PadRefs.Where([&] (std::any aa)
		{
			return aa->_compName == oldname;
		})))))
		{
			a->_compName = newname;
		}
		for (auto a : (_PadConnectSettings == nullptr ? nullptr : ((_PadConnectSettings->_PinRefs.empty() ? nullptr : _PadConnectSettings->_PinRefs.Where([&] (std::any aa)
		{
			return aa->_compName == oldname;
		})))))
		{
			a->_compName = newname;
		}

		for (auto a : (_RulesClearancesCompToComp.empty() ? nullptr : _RulesClearancesCompToComp.Where([&] (std::any aa)
		{
			return aa::_ObjectsAffected != nullptr;
		})))
		{
			for (auto b : a::_ObjectsAffected::OfType<std::shared_ptr<ComponentRef>>().Where([&] (std::any bb)
			{
				return bb->_ReferenceName == oldname;
			}))
			{
				b->_ReferenceName = newname;
			}
		}

	/****************************************************************/

	}
}
