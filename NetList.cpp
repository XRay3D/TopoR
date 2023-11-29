#include "NetList.h"
#include "Commons.h"

namespace TopoR_PCB_Classes {

bool NetList::Net::ShouldSerialize_refs() {
    return _refs.size();
}

bool NetList::ShouldSerialize_Nets() {
    return _Nets.size();
}

void NetList::Rename_compName(const std::string& oldname, const std::string& newname) {
    // for(auto a: _Nets.Where([&](std::any aa) {
    //         return aa::_refs != nullptr;
    //     })) {
    //     for(auto b: a::_refs::OfType<std::optional<PinRef>>().Where([&](std::any bb) {
    //             return bb.value()._compName == oldname;
    //         }))
    //         b->_compName = newname;
    //     for(auto b: a::_refs::OfType<std::optional<PadRef>>().Where([&](std::any bb) {
    //             return bb.value()._compName == oldname;
    //         }))
    //         b->_compName = newname;
    // }
}
} // namespace TopoR_PCB_Classes
