#include "Groups.h"
#include "Commons.h"

namespace TopoR_PCB_Classes {

bool Groups::LayerGroup::ShouldSerialize_LayerRefs() {
    return _LayerRefs.size();
}

std::string Groups::LayerGroup::ToString() {
    return _name;
}

bool Groups::NetGroup::ShouldSerialize_NetRefs() {
    return _NetRefs.size();
}

bool Groups::CompGroup::ShouldSerialize_CompRefs() {
    return _CompRefs.size();
}

bool Groups::ShouldSerialize_LayerGroups() {
    return _LayerGroups.size();
}

bool Groups::ShouldSerialize_NetGroups() {
    return _NetGroups.size();
}

bool Groups::ShouldSerialize_CompGroups() {
    return _CompGroups.size();
}

void Groups::Rename_compName(const std::string& oldname, const std::string& newname) {
    /*  for(auto a: (_CompGroups.empty() ? nullptr : _CompGroups.Where([&](std::any aa) {
              return aa::_CompRefs != nullptr;
          })))
          for(auto b: a::_CompRefs::OfType<std::optional<CompInstanceRef>>().Where([&](std::any bb) {
                  return bb.value()._ReferenceName == oldname;
              }))
              b->_ReferenceName = newname;*/
}
} // namespace TopoR_PCB_Classes
