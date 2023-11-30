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

Layers::Layer::Layer(const QString& name, layer_type type, Bool compsOutline, float thickness) {
    _name = name;
    _type = type;
    _compsOutline = compsOutline;
    _thickness = thickness;
}

QString Layers::Layer::ToString() {
    return _name;
}

bool Layers::LayerStackUpContains(LayerRef lref) {
    return /*(_StackUpLayers.empty() ? nullptr : _StackUpLayers.Where([&](std::any r) {
                                                                 return r->_name == lref.value()._ReferenceName;
                                                             })
                                                   ->Count())
        >*/
        0;
}

bool Layers::LayerUnStackContain(LayerRef lref) {
    return /* (_UnStackLayers.empty() ? nullptr : _UnStackLayers.Where([&](std::any r) {
                                                                  return r->_name == lref.value()._ReferenceName;
                                                              })
                                                    ->Count())
         >*/
        0;
}

} // namespace TopoR_PCB_Classes
