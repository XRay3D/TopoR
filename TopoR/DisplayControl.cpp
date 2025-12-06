#include "DisplayControl.h"
namespace TopoR {
bool DisplayControl::Show_DisplayControl::getShowBoardOutlineSpecified() const { return std::to_underlying(showBoardOutline); }
bool DisplayControl::Show_DisplayControl::getShowWiresSpecified() const { return std::to_underlying(showWires); }
bool DisplayControl::Show_DisplayControl::getShowCoppersSpecified() const { return std::to_underlying(showCoppers); }
bool DisplayControl::Show_DisplayControl::getShowTextsSpecified() const { return std::to_underlying(showTexts); }
bool DisplayControl::Show_DisplayControl::getThroughPadSpecified() const { return std::to_underlying(throughPad); }
bool DisplayControl::Show_DisplayControl::getThroughViaSpecified() const { return std::to_underlying(throughVia); }
bool DisplayControl::Show_DisplayControl::getBurriedViaSpecified() const { return std::to_underlying(burriedVia); }
bool DisplayControl::Show_DisplayControl::getBlindViaSpecified() const { return std::to_underlying(blindVia); }
bool DisplayControl::Show_DisplayControl::getFixedViaSpecified() const { return std::to_underlying(fixedVia); }
bool DisplayControl::Show_DisplayControl::getShowViasSpecified() const { return std::to_underlying(showVias); }
bool DisplayControl::Show_DisplayControl::getShowSignalLayersSpecified() const { return std::to_underlying(showSignalLayers); }
bool DisplayControl::Show_DisplayControl::getShowTopMechLayersSpecified() const { return std::to_underlying(showTopMechLayers); }
bool DisplayControl::Show_DisplayControl::getShowBotMechLayersSpecified() const { return std::to_underlying(showBotMechLayers); }
bool DisplayControl::Show_DisplayControl::getShowDocLayersSpecified() const { return std::to_underlying(showDocLayers); }
bool DisplayControl::Show_DisplayControl::getShowTopMechDetailsSpecified() const { return std::to_underlying(showTopMechDetails); }
bool DisplayControl::Show_DisplayControl::getShowBotMechDetailsSpecified() const { return std::to_underlying(showBotMechDetails); }
bool DisplayControl::Show_DisplayControl::getShowMetalPadsSpecified() const { return std::to_underlying(showMetalPads); }
bool DisplayControl::Show_DisplayControl::getShowTopMechPadsSpecified() const { return std::to_underlying(showTopMechPads); }
bool DisplayControl::Show_DisplayControl::getShowBotMechPadsSpecified() const { return std::to_underlying(showBotMechPads); }
bool DisplayControl::Show_DisplayControl::getShowNetLinesSpecified() const { return std::to_underlying(showNetLines); }
bool DisplayControl::Show_DisplayControl::getShowMountingHolesSpecified() const { return std::to_underlying(showMountingHoles); }
bool DisplayControl::Show_DisplayControl::getShowThinWiresSpecified() const { return std::to_underlying(showThinWires); }
bool DisplayControl::Show_DisplayControl::getShowComponentsSpecified() const { return std::to_underlying(showComponents); }
bool DisplayControl::Show_DisplayControl::getShowCompTopSpecified() const { return std::to_underlying(showCompTop); }
bool DisplayControl::Show_DisplayControl::getShowCompBotSpecified() const { return std::to_underlying(showCompBot); }
bool DisplayControl::Show_DisplayControl::getShowCompsDesSpecified() const { return std::to_underlying(showCompsDes); }
bool DisplayControl::Show_DisplayControl::getShowPinsNameSpecified() const { return std::to_underlying(showPinsName); }
bool DisplayControl::Show_DisplayControl::getShowPinsNetSpecified() const { return std::to_underlying(showPinsNet); }
bool DisplayControl::Show_DisplayControl::getShowCompsBoundSpecified() const { return std::to_underlying(showCompsBound); }
bool DisplayControl::Show_DisplayControl::getShowLabelRefDesSpecified() const { return std::to_underlying(showLabelRefDes); }
bool DisplayControl::Show_DisplayControl::getShowLabelPartNameSpecified() const { return std::to_underlying(showLabelPartName); }
bool DisplayControl::Show_DisplayControl::getShowLabelOtherSpecified() const { return std::to_underlying(showLabelOther); }
bool DisplayControl::Show_DisplayControl::getShowViolationsSpecified() const { return std::to_underlying(showViolations); }
bool DisplayControl::Show_DisplayControl::getShowNarrowSpecified() const { return std::to_underlying(showNarrow); }
bool DisplayControl::Show_DisplayControl::getShowTrimmedSpecified() const { return std::to_underlying(showTrimmed); }
bool DisplayControl::Show_DisplayControl::getShowDRCViolationsSpecified() const { return std::to_underlying(showDRCViolations); }
bool DisplayControl::Show_DisplayControl::getShowKeepoutsSpecified() const { return std::to_underlying(showKeepouts); }
bool DisplayControl::Show_DisplayControl::getShowRouteKeepoutsSpecified() const { return std::to_underlying(showRouteKeepouts); }
bool DisplayControl::Show_DisplayControl::getShowPlaceKeepoutsSpecified() const { return std::to_underlying(showPlaceKeepouts); }
bool DisplayControl::Show_DisplayControl::getShowActiveLayerOnlySpecified() const { return std::to_underlying(showActiveLayerOnly); }
bool DisplayControl::Show_DisplayControl::getShowSerpentAreaSpecified() const { return std::to_underlying(showSerpentArea); }
bool DisplayControl::Grid::getGridShowSpecified() const { return std::to_underlying(gridShow); }
bool DisplayControl::Grid::getAlignToGridSpecified() const { return std::to_underlying(alignToGrid); }
bool DisplayControl::Grid::getSnapToAngleSpecified() const { return std::to_underlying(snapToAngle); }
bool DisplayControl::LayerOptions::Show_LayerOptions::getVisibleSpecified() const { return std::to_underlying(visible); }
bool DisplayControl::LayerOptions::Show_LayerOptions::getDetailsSpecified() const { return std::to_underlying(details); }
bool DisplayControl::LayerOptions::Show_LayerOptions::getPadsSpecified() const { return std::to_underlying(pads); }
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
