#include "DialogSettings.h"
namespace TopoR {
bool DialogSettings::DRCSettings::getCreateLogSpecified() const { return std::to_underlying(createLog); }
bool DialogSettings::DRCSettings::getCheckNetIntegritySpecified() const { return std::to_underlying(checkNetIntegrity); }
bool DialogSettings::DRCSettings::getCheckNetWidthSpecified() const { return std::to_underlying(checkNetWidth); }
bool DialogSettings::DRCSettings::getCheckClearancesSpecified() const { return std::to_underlying(checkClearances); }
bool DialogSettings::DRCSettings::getTextToCopperSpecified() const { return std::to_underlying(textToCopper); }
bool DialogSettings::DRCSettings::getTextToKeepoutSpecified() const { return std::to_underlying(textToKeepout); }
bool DialogSettings::DRCSettings::getTextToViaSpecified() const { return std::to_underlying(textToVia); }
bool DialogSettings::DRCSettings::getTextToWireSpecified() const { return std::to_underlying(textToWire); }
bool DialogSettings::DRCSettings::getTextToPadSpecified() const { return std::to_underlying(textToPad); }
bool DialogSettings::DRCSettings::getTextToBoardSpecified() const { return std::to_underlying(textToBoard); }
bool DialogSettings::DRCSettings::getCopperToCopperSpecified() const { return std::to_underlying(copperToCopper); }
bool DialogSettings::DRCSettings::getCopperToKeepoutSpecified() const { return std::to_underlying(copperToKeepout); }
bool DialogSettings::DRCSettings::getCopperToWireSpecified() const { return std::to_underlying(copperToWire); }
bool DialogSettings::DRCSettings::getCopperToViaSpecified() const { return std::to_underlying(copperToVia); }
bool DialogSettings::DRCSettings::getCopperToPadSpecified() const { return std::to_underlying(copperToPad); }
bool DialogSettings::DRCSettings::getCopperToBoardSpecified() const { return std::to_underlying(copperToBoard); }
bool DialogSettings::DRCSettings::getWireToKeepoutSpecified() const { return std::to_underlying(wireToKeepout); }
bool DialogSettings::DRCSettings::getViaToKeepoutSpecified() const { return std::to_underlying(viaToKeepout); }
bool DialogSettings::DRCSettings::getPadToKeepoutSpecified() const { return std::to_underlying(padToKeepout); }
bool DialogSettings::DRCSettings::getWireToWireSpecified() const { return std::to_underlying(wireToWire); }
bool DialogSettings::DRCSettings::getWireToViaSpecified() const { return std::to_underlying(wireToVia); }
bool DialogSettings::DRCSettings::getWireToPadSpecified() const { return std::to_underlying(wireToPad); }
bool DialogSettings::DRCSettings::getWireToBoardSpecified() const { return std::to_underlying(wireToBoard); }
bool DialogSettings::DRCSettings::getViaToViaSpecified() const { return std::to_underlying(viaToVia); }
bool DialogSettings::DRCSettings::getViaToPadSpecified() const { return std::to_underlying(viaToPad); }
bool DialogSettings::DRCSettings::getViaToBoardSpecified() const { return std::to_underlying(viaToBoard); }
bool DialogSettings::DRCSettings::getPadToPadSpecified() const { return std::to_underlying(padToPad); }
bool DialogSettings::DRCSettings::getPadToBoardSpecified() const { return std::to_underlying(padToBoard); }
bool DialogSettings::GerberSettings::ShouldSerialize_ExportFiles() {
    return {}; //    return ExportFiles.size();
}
bool DialogSettings::DXFSettings::getOutputBoardLayerSpecified() const { return std::to_underlying(outputBoardLayer); }
bool DialogSettings::DXFSettings::getOutputDrillLayerSpecified() const { return std::to_underlying(outputDrillLayer); }
bool DialogSettings::DXFSettings::ShouldSerialize_ExportLayers() {
    return {}; //    return ExportLayers.size();
}
bool DialogSettings::DrillSettings::ShouldSerialize_ExportFiles() {
    return {}; //    return ExportFiles.size();
}
bool DialogSettings::BOMSettings::getCountSpecified() const { return std::to_underlying(count); }
bool DialogSettings::BOMSettings::getPartNameSpecified() const { return std::to_underlying(partName); }
bool DialogSettings::BOMSettings::getFootprintSpecified() const { return std::to_underlying(footprint); }
bool DialogSettings::BOMSettings::getRefDesSpecified() const { return std::to_underlying(refDes); }
bool DialogSettings::BOMSettings::ShouldSerialize_AttributeRefs() {
    return {}; //    return AttributeRefs.size();
}
bool DialogSettings::MessagesFilter::getW5003Specified() const { return std::to_underlying(W5003); }
bool DialogSettings::MessagesFilter::getW5012Specified() const { return std::to_underlying(W5012); }
bool DialogSettings::MessagesFilter::getW5013Specified() const { return std::to_underlying(W5013); }
bool DialogSettings::MessagesFilter::getW5014Specified() const { return std::to_underlying(W5014); }
bool DialogSettings::MessagesFilter::getW5015Specified() const { return std::to_underlying(W5015); }
bool DialogSettings::MessagesFilter::getW5016Specified() const { return std::to_underlying(W5016); }
bool DialogSettings::MessagesFilter::getW5017Specified() const { return std::to_underlying(W5017); }
bool DialogSettings::MessagesFilter::getW5018Specified() const { return std::to_underlying(W5018); }
bool DialogSettings::MessagesFilter::getW5023Specified() const { return std::to_underlying(W5023); }
bool DialogSettings::MessagesFilter::getW5024Specified() const { return std::to_underlying(W5024); }
bool DialogSettings::MessagesFilter::getW5026Specified() const { return std::to_underlying(W5026); }
bool DialogSettings::MessagesFilter::getW5034Specified() const { return std::to_underlying(W5034); }
bool DialogSettings::MessagesFilter::getW5036Specified() const { return std::to_underlying(W5036); }
bool DialogSettings::MessagesFilter::getW5037Specified() const { return std::to_underlying(W5037); }
bool DialogSettings::MessagesFilter::getWClrnBtwCompsSpecified() const { return std::to_underlying(WClrnBtwComps); }
bool DialogSettings::MessagesFilter::getWClrnBtwObjSameNetSpecified() const { return std::to_underlying(WClrnBtwObjSameNet); }
} // namespace TopoR
