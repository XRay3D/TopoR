#include "Connectivity.h"

namespace TopoR_PCB_Classes
{

	bool Connectivity::Via::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool Connectivity::ZippedWire::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool Connectivity::ZippedWire::ShouldSerialize_Tracks()
	{
		return (_Tracks.empty() ? nullptr : _Tracks.size()) > 0;
	}

	bool Connectivity::Wire::Subwire::Teardrop::ShouldSerialize_Dots()
	{
		return (_Dots.empty() ? nullptr : _Dots.size()) > 0;
	}

	bool Connectivity::Wire::Subwire::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool Connectivity::Wire::Subwire::ShouldSerialize_Teardrops()
	{
		return (_Teardrops.empty() ? nullptr : _Teardrops.size()) > 0;
	}

	bool Connectivity::Wire::Subwire::ShouldSerialize_Tracks()
	{
		return (_Tracks.empty() ? nullptr : _Tracks.size()) > 0;
	}

	bool Connectivity::Wire::ShouldSerialize_Subwires()
	{
		return (_Subwires.empty() ? nullptr : _Subwires.size()) > 0;
	}

	bool Connectivity::Copper_Connectivity::Island::ThermalSpoke::ShouldSerialize_Dots()
	{
		return (_Dots.empty() ? nullptr : _Dots.size()) > 0;
	}

	bool Connectivity::Copper_Connectivity::Island::ShouldSerialize_ThermalSpokes()
	{
		return (_ThermalSpokes.empty() ? nullptr : _ThermalSpokes.size()) > 0;
	}

	bool Connectivity::Copper_Connectivity::getUseBackoffSpecified() const
	{
		return _useBackoff != Bool::off;
	}

	bool Connectivity::Copper_Connectivity::getDeleteUnconnectedSpecified() const
	{
		return _deleteUnconnected != Bool::off;
	}

	bool Connectivity::Copper_Connectivity::ShouldSerialize_Fill_lines()
	{
		return (_Fill_lines.empty() ? nullptr : _Fill_lines.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_Vias()
	{
		return (_Vias.empty() ? nullptr : _Vias.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_Serpents()
	{
		return (_Serpents.empty() ? nullptr : _Serpents.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_ZippedWires()
	{
		return (_ZippedWires.empty() ? nullptr : _ZippedWires.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_Wires()
	{
		return (_Wires.empty() ? nullptr : _Wires.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_Coppers()
	{
		return (_Coppers.empty() ? nullptr : _Coppers.size()) > 0;
	}

	bool Connectivity::ShouldSerialize_NonfilledCoppers()
	{
		return (_NonfilledCoppers.empty() ? nullptr : _NonfilledCoppers.size()) > 0;
	}
}
