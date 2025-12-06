#include "Settings.h"
namespace TopoR {
bool Settings::Autoroute::getTeardropsSpecified() const { return std::to_underlying(teardrops); }
bool Settings::Autoroute::getWeakCheckSpecified() const { return std::to_underlying(weakCheck); }
bool Settings::Autoroute::getTakeCurLayoutSpecified() const { return std::to_underlying(takeCurLayout); }
bool Settings::Autoroute::getDirectConnectSMDSpecified() const { return std::to_underlying(directConnectSMD); }
bool Settings::Autoroute::getDontStretchWireToPolypinSpecified() const { return std::to_underlying(dontStretchWireToPolypin); }
bool Settings::Placement::PlacementArea::ShouldSerialize_Dots() {
    return {}; //    return Dots.size();
}
bool Settings::Labels_Settings::getRotateWithCompSpecified() const { return std::to_underlying(rotateWithComp); }
bool Settings::Labels_Settings::getUseOrientRulesSpecified() const { return std::to_underlying(useOrientRules); }
bool Settings::Labels_Settings::getTopHorzRotateSpecified() const { return std::to_underlying(topHorzRotate); }
bool Settings::Labels_Settings::getTopVertRotateSpecified() const { return std::to_underlying(topVertRotate); }
bool Settings::Labels_Settings::getBottomHorzRotateSpecified() const { return std::to_underlying(bottomHorzRotate); }
bool Settings::Labels_Settings::getBottomVertRotateSpecified() const { return std::to_underlying(bottomVertRotate); }
} // namespace TopoR
