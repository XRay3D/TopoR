#include "Layers.h"
/*****************************************************************
 * Здесь находятся функции для работы с элементами класса Layer. *
 * Они не являются частью формата TopoR PCB.                     *
 * ***************************************************************/
namespace TopoR {
// bool Layers::Layer::getCompsOutlineSpecified() const {
//     return type == LayerType::Assy;
// }
// bool Layers::Layer::getThicknessSpecified() const {
//     return type != LayerType::Assy;
// }
bool Layers::LayerStackUpContains(LayerRef lref) {
    return /*(_StackUpLayers.empty() ? nullptr : StackUpLayers.Where([&](std::any r) {
                                                                 return r->_name == lref.value()._ReferenceName;
                                                             })
                                                   ->Count())
        >*/
        0;
}
bool Layers::LayerUnStackContain(LayerRef lref) {
    return /* (_UnStackLayers.empty() ? nullptr : UnStackLayers.Where([&](std::any r) {
                                                                  return r->_name == lref.value()._ReferenceName;
                                                              })
                                                    ->Count())
         >*/
        0;
}
} // namespace TopoR
