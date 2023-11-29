#include "Connectivity.h"

namespace TopoR_PCB_Classes {

bool Connectivity::Via::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::ZippedWire::ShouldSerialize_Tracks() { return _Tracks.size(); }

bool Connectivity::Wire::Subwire::Teardrop::ShouldSerialize_Dots() { return _Dots.size(); }

bool Connectivity::Wire::Subwire::getFixedSpecified() const { return _fixed != Bool::off; }

bool Connectivity::Wire::Subwire::ShouldSerialize_Teardrops() { return _Teardrops.size(); }

bool Connectivity::Wire::Subwire::ShouldSerialize_Tracks() { return _Tracks.size(); }

bool Connectivity::Wire::ShouldSerialize_Subwires() { return _Subwires.size(); }

bool Connectivity::Copper_Connectivity::Island::ThermalSpoke::ShouldSerialize_Dots() { return _Dots.size(); }

bool Connectivity::Copper_Connectivity::Island::ShouldSerialize_ThermalSpokes() { return _ThermalSpokes.size(); }

bool Connectivity::Copper_Connectivity::getUseBackoffSpecified() const { return _useBackoff != Bool::off; }

bool Connectivity::Copper_Connectivity::getDeleteUnconnectedSpecified() const { return _deleteUnconnected != Bool::off; }

bool Connectivity::Copper_Connectivity::ShouldSerialize_Fill_lines() { return _Fill_lines.size(); }

bool Connectivity::ShouldSerialize_Vias() { return _Vias.size(); }

bool Connectivity::ShouldSerialize_Serpents() { return _Serpents.size(); }

bool Connectivity::ShouldSerialize_ZippedWires() { return _ZippedWires.size(); }

bool Connectivity::ShouldSerialize_Wires() { return _Wires.size(); }

bool Connectivity::ShouldSerialize_Coppers() { return _Coppers.size(); }

bool Connectivity::ShouldSerialize_NonfilledCoppers() { return _NonfilledCoppers.size(); }
} // namespace TopoR_PCB_Classes
