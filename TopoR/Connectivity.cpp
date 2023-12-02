#include "Connectivity.h"

namespace TopoR_PCB_Classes {

bool Connectivity::Via::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::ShouldSerialize_Tracks() { return Tracks.size(); }

bool Connectivity::Wire::Subwire::Teardrop::ShouldSerialize_Dots() { return Dots.size(); }

bool Connectivity::Wire::Subwire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::Wire::Subwire::ShouldSerialize_Teardrops() { return Teardrops.size(); }

bool Connectivity::Wire::Subwire::ShouldSerialize_Tracks() { return Tracks.size(); }

bool Connectivity::Wire::ShouldSerialize_Subwires() { return Subwires.size(); }

bool Connectivity::Copper_Connectivity::Island::ThermalSpoke::ShouldSerialize_Dots() { return Dots.size(); }

bool Connectivity::Copper_Connectivity::Island::ShouldSerialize_ThermalSpokes() { return ThermalSpokes.size(); }

bool Connectivity::Copper_Connectivity::getUseBackoffSpecified() const { return _useBackoff != Bool::off; }

bool Connectivity::Copper_Connectivity::getDeleteUnconnectedSpecified() const { return _deleteUnconnected != Bool::off; }

bool Connectivity::Copper_Connectivity::ShouldSerialize_Fill_lines() { return Fill_lines.size(); }

bool Connectivity::ShouldSerialize_Vias() { return Vias.size(); }

bool Connectivity::ShouldSerialize_Serpents() { return Serpents.size(); }

bool Connectivity::ShouldSerialize_ZippedWires() { return ZippedWires.size(); }

bool Connectivity::ShouldSerialize_Wires() { return Wires.size(); }

bool Connectivity::ShouldSerialize_Coppers() { return Coppers.size(); }

bool Connectivity::ShouldSerialize_NonfilledCoppers() { return NonfilledCoppers.size(); }

} // namespace TopoR_PCB_Classes
