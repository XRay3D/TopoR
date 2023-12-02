#include "NetList.h"
#include "Commons.h"

namespace TopoR_PCB_Classes {

bool NetList::Net::ShouldSerialize_refs() {
    return refs_.size();
}

bool NetList::ShouldSerialize_Nets() {
    return Nets_.size();
}

void NetList::Rename_compName(const QString& oldname, const QString& newname) {
    // for(auto a: Nets_.Where([&](std::any aa) {
    //         return aa::_refs != nullptr;
    //     })) {
    //     for(auto b: a::_refs::OfType<PinRef>().Where([&](std::any bb) {
    //             return bb.value()._compName == oldname;
    //         }))
    //         b->_compName = newname;
    //     for(auto b: a::_refs::OfType<PadRef>().Where([&](std::any bb) {
    //             return bb.value()._compName == oldname;
    //         }))
    //         b->_compName = newname;
    // }
}

} // namespace TopoR_PCB_Classes
