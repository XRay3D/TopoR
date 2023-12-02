#include "Groups.h"
#include "Commons.h"

namespace TopoR_PCB_Classes {

bool Groups::LayerGroup::ShouldSerialize_LayerRefs() {
    return LayerRefs_.size();
}

QString Groups::LayerGroup::ToString() {
    return name_;
}

bool Groups::NetGroup::ShouldSerialize_NetRefs() {
    return NetRefs_.size();
}

bool Groups::CompGroup::ShouldSerialize_CompRefs() {
    return CompRefs_.size();
}

bool Groups::ShouldSerialize_LayerGroups() {
    return LayerGroups_.size();
}

bool Groups::ShouldSerialize_NetGroups() {
    return NetGroups_.size();
}

bool Groups::ShouldSerialize_CompGroups() {
    return CompGroups_.size();
}

void Groups::Rename_compName(const QString& oldname, const QString& newname) {
    /*  for(auto a: (_CompGroups.empty() ? nullptr : CompGroups_.Where([&](std::any aa) {
              return aa::_CompRefs != nullptr;
          })))
          for(auto b: a::_CompRefs::OfType<CompInstanceRef>().Where([&](std::any bb) {
                  return bb.value()._ReferenceName == oldname;
              }))
              b->_ReferenceName = newname;*/
}

} // namespace TopoR_PCB_Classes
