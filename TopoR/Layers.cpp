#include "Layers.h"

/*****************************************************************
 * Здесь находятся функции для работы с элементами класса Layer. *
 * Они не являются частью формата TopoR PCB.                     *
 * ***************************************************************/
namespace TopoR_PCB_Classes {

bool Layers::Layer::getCompsOutlineSpecified() const {
    return type == layer_type::Assy;
}

bool Layers::Layer::getThicknessSpecified() const {
    return type != layer_type::Assy;
}

bool Layers::LayerStackUpContains(LayerRef lref) {
    return /*(_StackUpLayers.empty() ? nullptr : StackUpLayers_.Where([&](std::any r) {
                                                                 return r->_name == lref.value()._ReferenceName;
                                                             })
                                                   ->Count())
        >*/
        0;
}

bool Layers::LayerUnStackContain(LayerRef lref) {
    return /* (_UnStackLayers.empty() ? nullptr : UnStackLayers_.Where([&](std::any r) {
                                                                  return r->_name == lref.value()._ReferenceName;
                                                              })
                                                    ->Count())
         >*/
        0;
}

} // namespace TopoR_PCB_Classes
