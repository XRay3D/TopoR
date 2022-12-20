#include "Groups.h"
#include "Commons.h"

namespace TopoR_PCB_Classes
{

	bool Groups::LayerGroup::ShouldSerialize_LayerRefs()
	{
		return _LayerRefs.empty() ? nullptr : _LayerRefs.size() > 0;
	}

	std::string Groups::LayerGroup::ToString()
	{
		return _name;
	}

	bool Groups::NetGroup::ShouldSerialize_NetRefs()
	{
		return _NetRefs.empty() ? nullptr : _NetRefs.size() > 0;
	}

	bool Groups::CompGroup::ShouldSerialize_CompRefs()
	{
		return _CompRefs.empty() ? nullptr : _CompRefs.size() > 0;
	}

	bool Groups::ShouldSerialize_LayerGroups()
	{
		return _LayerGroups.empty() ? nullptr : _LayerGroups.size() > 0;
	}

	bool Groups::ShouldSerialize_NetGroups()
	{
		return _NetGroups.empty() ? nullptr : _NetGroups.size() > 0;
	}

	bool Groups::ShouldSerialize_CompGroups()
	{
		return _CompGroups.empty() ? nullptr : _CompGroups.size() > 0;
	}

	void Groups::Rename_compName(const std::string &oldname, const std::string &newname)
	{
		for (auto a : _CompGroups.empty() ? nullptr : _CompGroups.Where([&] (std::any aa)
		{
			return aa::_CompRefs != nullptr;
		}))
		{
			for (auto b : a::_CompRefs::OfType<std::shared_ptr<CompInstanceRef>>().Where([&] (std::any bb)
			{
				return bb->_ReferenceName == oldname;
			}))
			{
				b->_ReferenceName = newname;
			}
		}
	}
}
