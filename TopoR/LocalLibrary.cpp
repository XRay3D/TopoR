#include "LocalLibrary.h"
namespace TopoR {
bool LocalLibrary::PadRect::getHandlingSpecified() const { return handling != Handling::None; }
bool LocalLibrary::PadRect::getHandlingValueSpecified() const { return handlingValue != 0; }

bool LocalLibrary::PadPoly::ShouldSerialize_Dots() { return Dots.size(); }

bool LocalLibrary::Padstack::ShouldSerialize_Pads() { return Pads.size(); }
bool LocalLibrary::Viastack::LayerRange::ShouldSerializeLayerRefs() { return LayerRefs.size(); }

bool LocalLibrary::Viastack::ShouldSerialize_ViaPads() { return ViaPads.size(); }

bool LocalLibrary::Footprint::ShouldSerialize_Pads() { return Pads.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_Texts() { return Texts.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_Details() { return Details.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_Coppers() { return Coppers.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_KeepoutsPlace() { return KeepoutsPlace.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_KeepoutsTrace() { return KeepoutsTrace.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_Mntholes() { return Mntholes.size(); }
bool LocalLibrary::Footprint::ShouldSerialize_Labels() { return Labels.size(); }
std::string LocalLibrary::Footprint::ToString() { return name; }
bool LocalLibrary::Component::ShouldSerialize_Pins() { return Pins.size(); }
bool LocalLibrary::Component::ShouldSerialize_Attributes() { return Attributes.size(); }
std::string LocalLibrary::Component::ToString() { return name; }
bool LocalLibrary::Package::ShouldSerialize_Pinpacks() { return Pinpacks.size(); }
bool LocalLibrary::ShouldSerialize_Padstacks() { return Padstacks.size(); }
bool LocalLibrary::ShouldSerialize_Viastacks() { return Viastacks.size(); }
bool LocalLibrary::ShouldSerialize_Footprints() { return Footprints.size(); }
bool LocalLibrary::ShouldSerialize_Components() { return Components.size(); }
bool LocalLibrary::ShouldSerialize_Packages() { return Packages.size(); }
} // namespace TopoR
