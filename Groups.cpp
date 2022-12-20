#include "Groups.h"
#include "Commons.h"

// namespace TopoR_PCB_Classes {

bool Groups::LayerGroup::ShouldSerialize_LayerRefs() {
    return _LayerRefs.empty() ? false : _LayerRefs.size() > 0;
}

QString Groups::LayerGroup::ToString() {
    return _name;
}

bool Groups::NetGroup::ShouldSerialize_NetRefs() {
    return _NetRefs.empty() ? false : _NetRefs.size() > 0;
}

bool Groups::CompGroup::ShouldSerialize_CompRefs() {
    return _CompRefs.empty() ? false : _CompRefs.size() > 0;
}

bool Groups::ShouldSerialize_LayerGroups() {
    return _LayerGroups.empty() ? false : _LayerGroups.size() > 0;
}

bool Groups::ShouldSerialize_NetGroups() {
    return _NetGroups.empty() ? false : _NetGroups.size() > 0;
}

bool Groups::ShouldSerialize_CompGroups() {
    return _CompGroups.empty() ? false : _CompGroups.size() > 0;
}

void Groups::Rename_compName(const QString& oldname, const QString& newname) {
    //    for (auto a : _CompGroups.empty() ? false : _CompGroups.Where([&](std::any aa) {
    //             return aa::_CompRefs != nullptr;
    //         })) {
    //        for (auto b : a::_CompRefs::OfType<CompInstanceRef*>().Where([&](std::any bb) {
    //                 return bb->_ReferenceName == oldname;
    //             })) {
    //            b->_ReferenceName = newname;
    //        }
    //    }
}
// } // namespace TopoR_PCB_Classes
