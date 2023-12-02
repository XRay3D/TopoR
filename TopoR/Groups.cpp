#include "Groups.h"
#include "Commons.h"

namespace TopoR_PCB_Classes {

bool Groups::LayerGroup::ShouldSerialize_LayerRefs() {
    return LayerRefs.size();
}

QString Groups::LayerGroup::ToString() {
    return name;
}

bool Groups::NetGroup::ShouldSerialize_NetRefs() {
    return NetRefs.size();
}

bool Groups::CompGroup::ShouldSerialize_CompRefs() {
    return CompRefs.size();
}

bool Groups::ShouldSerialize_LayerGroups() {
    return LayerGroups.size();
}

bool Groups::ShouldSerialize_NetGroups() {
    return NetGroups.size();
}

bool Groups::ShouldSerialize_CompGroups() {
    return CompGroups.size();
}

void Groups::Rename_compName(const QString& oldname, const QString& newname) {
    /*  for(auto a: (_CompGroups.empty() ? nullptr : CompGroups.Where([&](std::any aa) {
              return aa::_CompRefs != nullptr;
          })))
          for(auto b: a::_CompRefs::OfType<CompInstanceRef>().Where([&](std::any bb) {
                  return bb.value()._ReferenceName == oldname;
              }))
              b->_ReferenceName = newname;*/
}

} // namespace TopoR_PCB_Classes
