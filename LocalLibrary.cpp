#include "LocalLibrary.h"

namespace TopoR_PCB_Classes {

bool LocalLibrary::PadRect::getHandlingSpecified() const {
    return _handling != type_handling::None;
}

bool LocalLibrary::PadRect::getHandlingValueSpecified() const {
    return _handlingValue != 0;
}

bool LocalLibrary::PadRect::getCustomSpecified() const {
    return _custom != Bool::off;
}

bool LocalLibrary::PadRect::getCornerLBSpecified() const {
    return _cornerLB != Bool::off;
}

bool LocalLibrary::PadRect::getCornerRBSpecified() const {
    return _cornerRB != Bool::off;
}

bool LocalLibrary::PadRect::getCornerRTSpecified() const {
    return _cornerRT != Bool::off;
}

bool LocalLibrary::PadRect::getCornerLTSpecified() const {
    return _cornerLT != Bool::off;
}

bool LocalLibrary::PadPoly::ShouldSerialize_Dots() {
    return _Dots.size();
}

bool LocalLibrary::Padstack::getMetallizedSpecified() const {
    return _metallized != Bool::off;
}

bool LocalLibrary::Padstack::ShouldSerialize_Pads() {
    return _Pads.size();
}

bool LocalLibrary::Viastack::LayerRange::ShouldSerialize_LayerRefs() {
    return _LayerRefs.size();
}

bool LocalLibrary::Viastack::getViaOnPinSpecified() const {
    return _viaOnPin != Bool::off;
}

bool LocalLibrary::Viastack::ShouldSerialize_ViaPads() {
    return _ViaPads.size();
}

bool LocalLibrary::Footprint::Label_Footprint::getMirrorSpecified() const {
    return _mirror != Bool::off;
}

bool LocalLibrary::Footprint::Pad::getFlippedSpecified() const {
    return _flipped != Bool::off;
}

bool LocalLibrary::Footprint::ShouldSerialize_Pads() {
    return _Pads.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_Texts() {
    return _Texts.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_Details() {
    return _Details.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_Coppers() {
    return _Coppers.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_KeepoutsPlace() {
    return _KeepoutsPlace.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_KeepoutsTrace() {
    return _KeepoutsTrace.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_Mntholes() {
    return _Mntholes.size();
}

bool LocalLibrary::Footprint::ShouldSerialize_Labels() {
    return _Labels.size();
}

QString LocalLibrary::Footprint::ToString() {
    return _name;
}

bool LocalLibrary::Component::ShouldSerialize_Pins() {
    return _Pins.size();
}

bool LocalLibrary::Component::ShouldSerialize_Attributes() {
    return _Attributes.size();
}

QString LocalLibrary::Component::ToString() {
    return _name;
}

bool LocalLibrary::Package::ShouldSerialize_Pinpacks() {
    return _Pinpacks.size();
}

bool LocalLibrary::ShouldSerialize_Padstacks() {
    return _Padstacks.size();
}

bool LocalLibrary::ShouldSerialize_Viastacks() {
    return _Viastacks.size();
}

bool LocalLibrary::ShouldSerialize_Footprints() {
    return _Footprints.size();
}

bool LocalLibrary::ShouldSerialize_Components() {
    return _Components.size();
}

bool LocalLibrary::ShouldSerialize_Packages() {
    return _Packages.size();
}

} // namespace TopoR_PCB_Classes
