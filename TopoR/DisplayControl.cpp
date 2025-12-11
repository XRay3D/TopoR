#include "DisplayControl.h"
namespace TopoR {
bool DisplayControl::Show::getShowBoardOutlineSpecified() const { return std::to_underlying(showBoardOutline); }
bool DisplayControl::Show::getShowWiresSpecified() const { return std::to_underlying(showWires); }
bool DisplayControl::Show::getShowCoppersSpecified() const { return std::to_underlying(showCoppers); }
bool DisplayControl::Show::getShowTextsSpecified() const { return std::to_underlying(showTexts); }
bool DisplayControl::Show::getThroughPadSpecified() const { return std::to_underlying(throughPad); }
bool DisplayControl::Show::getThroughViaSpecified() const { return std::to_underlying(throughVia); }
bool DisplayControl::Show::getBurriedViaSpecified() const { return std::to_underlying(burriedVia); }
bool DisplayControl::Show::getBlindViaSpecified() const { return std::to_underlying(blindVia); }
bool DisplayControl::Show::getFixedViaSpecified() const { return std::to_underlying(fixedVia); }
bool DisplayControl::Show::getShowViasSpecified() const { return std::to_underlying(showVias); }
bool DisplayControl::Show::getShowSignalLayersSpecified() const { return std::to_underlying(showSignalLayers); }
bool DisplayControl::Show::getShowTopMechLayersSpecified() const { return std::to_underlying(showTopMechLayers); }
bool DisplayControl::Show::getShowBotMechLayersSpecified() const { return std::to_underlying(showBotMechLayers); }
bool DisplayControl::Show::getShowDocLayersSpecified() const { return std::to_underlying(showDocLayers); }
bool DisplayControl::Show::getShowTopMechDetailsSpecified() const { return std::to_underlying(showTopMechDetails); }
bool DisplayControl::Show::getShowBotMechDetailsSpecified() const { return std::to_underlying(showBotMechDetails); }
bool DisplayControl::Show::getShowMetalPadsSpecified() const { return std::to_underlying(showMetalPads); }
bool DisplayControl::Show::getShowTopMechPadsSpecified() const { return std::to_underlying(showTopMechPads); }
bool DisplayControl::Show::getShowBotMechPadsSpecified() const { return std::to_underlying(showBotMechPads); }
bool DisplayControl::Show::getShowNetLinesSpecified() const { return std::to_underlying(showNetLines); }
bool DisplayControl::Show::getShowMountingHolesSpecified() const { return std::to_underlying(showMountingHoles); }
bool DisplayControl::Show::getShowThinWiresSpecified() const { return std::to_underlying(showThinWires); }
bool DisplayControl::Show::getShowComponentsSpecified() const { return std::to_underlying(showComponents); }
bool DisplayControl::Show::getShowCompTopSpecified() const { return std::to_underlying(showCompTop); }
bool DisplayControl::Show::getShowCompBotSpecified() const { return std::to_underlying(showCompBot); }
bool DisplayControl::Show::getShowCompsDesSpecified() const { return std::to_underlying(showCompsDes); }
bool DisplayControl::Show::getShowPinsNameSpecified() const { return std::to_underlying(showPinsName); }
bool DisplayControl::Show::getShowPinsNetSpecified() const { return std::to_underlying(showPinsNet); }
bool DisplayControl::Show::getShowCompsBoundSpecified() const { return std::to_underlying(showCompsBound); }
bool DisplayControl::Show::getShowLabelRefDesSpecified() const { return std::to_underlying(showLabelRefDes); }
bool DisplayControl::Show::getShowLabelPartNameSpecified() const { return std::to_underlying(showLabelPartName); }
bool DisplayControl::Show::getShowLabelOtherSpecified() const { return std::to_underlying(showLabelOther); }
bool DisplayControl::Show::getShowViolationsSpecified() const { return std::to_underlying(showViolations); }
bool DisplayControl::Show::getShowNarrowSpecified() const { return std::to_underlying(showNarrow); }
bool DisplayControl::Show::getShowTrimmedSpecified() const { return std::to_underlying(showTrimmed); }
bool DisplayControl::Show::getShowDRCViolationsSpecified() const { return std::to_underlying(showDRCViolations); }
bool DisplayControl::Show::getShowKeepoutsSpecified() const { return std::to_underlying(showKeepouts); }
bool DisplayControl::Show::getShowRouteKeepoutsSpecified() const { return std::to_underlying(showRouteKeepouts); }
bool DisplayControl::Show::getShowPlaceKeepoutsSpecified() const { return std::to_underlying(showPlaceKeepouts); }
bool DisplayControl::Show::getShowActiveLayerOnlySpecified() const { return std::to_underlying(showActiveLayerOnly); }
bool DisplayControl::Show::getShowSerpentAreaSpecified() const { return std::to_underlying(showSerpentArea); }
bool DisplayControl::Grid::getGridShowSpecified() const { return std::to_underlying(gridShow); }
bool DisplayControl::Grid::getAlignToGridSpecified() const { return std::to_underlying(alignTogrid); }
bool DisplayControl::Grid::getSnapToAngleSpecified() const { return std::to_underlying(snapToAngle); }
bool DisplayControl::LayerOptions::Show::getVisibleSpecified() const { return std::to_underlying(visible); }
bool DisplayControl::LayerOptions::Show::getDetailsSpecified() const { return std::to_underlying(details); }
bool DisplayControl::LayerOptions::Show::getPadsSpecified() const { return std::to_underlying(pads); }
bool DisplayControl::ColorNets::getEnabledSpecified() const { return std::to_underlying(enabled); }
bool DisplayControl::ColorNets::getColorizeWireSpecified() const { return std::to_underlying(colorizeWire); }
bool DisplayControl::ColorNets::getColorizePadSpecified() const { return std::to_underlying(colorizePad); }
bool DisplayControl::ColorNets::getColorizeCopperSpecified() const { return std::to_underlying(colorizeCopper); }
bool DisplayControl::ColorNets::getColorizeViaSpecified() const { return std::to_underlying(colorizeVia); }
bool DisplayControl::ColorNets::getColorizeNetlineSpecified() const { return std::to_underlying(colorizeNetline); }
bool DisplayControl::ColorNets::ShouldSerialize_SetColors() {
    return {}; //    return SetColors.size();
}
bool DisplayControl::FilterNetlines::getEnabledSpecified() const { return std::to_underlying(enabled); }
bool DisplayControl::FilterNetlines::ShouldSerialize_Refs() {
    return {}; //    return Refs.size();
}
bool DisplayControl::ShouldSerialize_LayersVisualOptions() {
    return {}; //    return LayersVisualOptions.size();
}
} // namespace TopoR
