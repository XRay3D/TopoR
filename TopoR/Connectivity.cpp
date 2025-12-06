#include "Connectivity.h"
namespace TopoR {
bool Connectivity::Via::getFixedSpecified() const { return std::to_underlying(fixed); }
bool Connectivity::ZippedWire::getFixedSpecified() const { return std::to_underlying(fixed); }
bool Connectivity::ZippedWire::ShouldSerialize_Tracks() { return Tracks.size(); }
bool Connectivity::Wire::Subwire::Teardrop::ShouldSerialize_Dots() { return Dots.size(); }
bool Connectivity::Wire::Subwire::getFixedSpecified() const { return std::to_underlying(fixed); }
bool Connectivity::Wire::Subwire::ShouldSerialize_Teardrops() { return Teardrops.size(); }
bool Connectivity::Wire::Subwire::ShouldSerialize_Tracks() { return Tracks.size(); }
// bool Connectivity::Wire::ShouldSerialize_Subwires() { return Subwires.size(); }
bool Connectivity::Copper::Island::ThermalSpoke::ShouldSerialize_Dots() { return Dots.size(); }
bool Connectivity::Copper::Island::ShouldSerialize_ThermalSpokes() { return ThermalSpokes.size(); }
bool Connectivity::Copper::getUseBackoffSpecified() const { return std::to_underlying(useBackoff); }
bool Connectivity::Copper::getDeleteUnconnectedSpecified() const { return std::to_underlying(deleteUnconnected); }
bool Connectivity::Copper::ShouldSerialize_Fill_lines() { return FillLines.size(); }
bool Connectivity::ShouldSerialize_Vias() { return Vias.size(); }
bool Connectivity::ShouldSerialize_Serpents() { return Serpents.size(); }
bool Connectivity::ShouldSerialize_ZippedWires() { return ZippedWires.size(); }
bool Connectivity::ShouldSerialize_Wires() { return Wires.size(); }
bool Connectivity::ShouldSerialize_Coppers() { return Coppers.size(); }
bool Connectivity::ShouldSerialize_NonfilledCoppers() { return NonfilledCoppers.size(); }
} // namespace TopoR
