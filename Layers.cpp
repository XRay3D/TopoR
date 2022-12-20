#include "Layers.h"

// namespace TopoR_PCB_Classes {

bool Layer::getCompsOutlineSpecified() const { return type == layer_type::Assy; }

bool Layer::getThicknessSpecified() const { return type != layer_type::Assy; }

Layer::Layer() { }

Layer::Layer(const QString& name, layer_type type, Bool compsOutline, float thickness)
    : name { name }
    , type { type }
    , compsOutline { compsOutline }
    , thickness { thickness }
{
}

QString Layer::ToString() { return name; }

bool Layers_::ShouldSerialize_StackUpLayers() { return StackUpLayers.empty() ? false : StackUpLayers.size() > 0; }

bool Layers_::ShouldSerialize_UnStackLayers() { return UnStackLayers.empty() ? false : UnStackLayers.size() > 0; }

bool LayerStackUpContains(LayerRef& lref)
{
    //    return _StackUpLayers.empty() ? false : _StackUpLayers.Where([&](std::any r) {
    //                                                                return r->_name == lref->_ReferenceName;
    //                                                            })
    //                                                  ->Count()
    //            > 0;
    return false;
}

bool LayerUnStackContain(LayerRef& lref)
{
    //    return _UnStackLayers.empty() ? false : _UnStackLayers.Where([&](std::any r) {
    //                                                                return r->_name == lref->_ReferenceName;
    //                                                            })
    //                                                  ->Count()
    //            > 0;
    return false;
}
// } // namespace TopoR_PCB_Classes
