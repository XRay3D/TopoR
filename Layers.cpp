#include "Layers.h"

namespace TopoR_PCB_Classes {

bool Layers::Layer::getCompsOutlineSpecified() const {
    return _type == layer_type::Assy;
}

bool Layers::Layer::getThicknessSpecified() const {
    return _type != layer_type::Assy;
}

Layers::Layer::Layer() {
}

Layers::Layer::Layer(const std::string& name, layer_type type, Bool compsOutline, float thickness) {
    _name = name;
    _type = type;
    _compsOutline = compsOutline;
    _thickness = thickness;
}

std::string Layers::Layer::ToString() {
    return _name;
}

bool Layers::ShouldSerialize_StackUpLayers() {
    return _StackUpLayers.size();
}

bool Layers::ShouldSerialize_UnStackLayers() {
    return _UnStackLayers.size();
}

bool Layers::LayerStackUpContains(std::optional<LayerRef> lref) {
    return /*(_StackUpLayers.empty() ? nullptr : _StackUpLayers.Where([&](std::any r) {
                                                                 return r->_name == lref.value()._ReferenceName;
                                                             })
                                                   ->Count())
        >*/
        0;
}

bool Layers::LayerUnStackContain(std::optional<LayerRef> lref) {
    return /* (_UnStackLayers.empty() ? nullptr : _UnStackLayers.Where([&](std::any r) {
                                                                  return r->_name == lref.value()._ReferenceName;
                                                              })
                                                    ->Count())
         >*/
        0;
}
} // namespace TopoR_PCB_Classes
