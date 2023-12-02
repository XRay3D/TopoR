#include "Connectivity.h"

namespace TopoR_PCB_Classes {

bool Connectivity::Via::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::ShouldSerialize_Tracks() { return Tracks_.size(); }

bool Connectivity::Wire::Subwire::Teardrop::ShouldSerialize_Dots() { return Dots_.size(); }

bool Connectivity::Wire::Subwire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::Wire::Subwire::ShouldSerialize_Teardrops() { return Teardrops_.size(); }

bool Connectivity::Wire::Subwire::ShouldSerialize_Tracks() { return Tracks_.size(); }

bool Connectivity::Wire::ShouldSerialize_Subwires() { return Subwires_.size(); }

bool Connectivity::Copper_Connectivity::Island::ThermalSpoke::ShouldSerialize_Dots() { return Dots_.size(); }

bool Connectivity::Copper_Connectivity::Island::ShouldSerialize_ThermalSpokes() { return ThermalSpokes_.size(); }

bool Connectivity::Copper_Connectivity::getUseBackoffSpecified() const { return _useBackoff != Bool::off; }

bool Connectivity::Copper_Connectivity::getDeleteUnconnectedSpecified() const { return _deleteUnconnected != Bool::off; }

bool Connectivity::Copper_Connectivity::ShouldSerialize_Fill_lines() { return Fill_lines_.size(); }

bool Connectivity::ShouldSerialize_Vias() { return Vias_.size(); }

bool Connectivity::ShouldSerialize_Serpents() { return Serpents_.size(); }

bool Connectivity::ShouldSerialize_ZippedWires() { return ZippedWires_.size(); }

bool Connectivity::ShouldSerialize_Wires() { return Wires_.size(); }

bool Connectivity::ShouldSerialize_Coppers() { return Coppers_.size(); }

bool Connectivity::ShouldSerialize_NonfilledCoppers() { return NonfilledCoppers_.size(); }

} // namespace TopoR_PCB_Classes
