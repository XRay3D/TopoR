#include "NetList.h"
#include "Commons.h"

namespace TopoR_PCB_Classes
{

	bool NetList::Net::ShouldSerialize_refs()
	{
		return _refs.empty() ? nullptr : _refs.size() > 0;
	}

	bool NetList::ShouldSerialize_Nets()
	{
		return _Nets.empty() ? nullptr : _Nets.size() > 0;
	}

	void NetList::Rename_compName(const std::string &oldname, const std::string &newname)
	{
		for (auto a : _Nets.Where([&] (std::any aa)
		{
			return aa::_refs != nullptr;
		}))
		{
			for (auto b : a::_refs::OfType<std::shared_ptr<PinRef>>().Where([&] (std::any bb)
			{
				return bb->_compName == oldname;
			}))
			{
				b->_compName = newname;
			}
			for (auto b : a::_refs::OfType<std::shared_ptr<PadRef>>().Where([&] (std::any bb)
			{
				return bb->_compName == oldname;
			}))
			{
				b->_compName = newname;
			}
		}
	}
}
