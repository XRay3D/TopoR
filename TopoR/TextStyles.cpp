#include "TextStyles.h"
namespace TopoR_PCB_Classes {

const TextStyles::TextStyle *TextStyles::getTextStyle(const QString &name) const {
    for(auto&& textStyle: TextStyles)
        if(name == textStyle.name)
            return &textStyle;
    return {};
}

} // namespace TopoR_PCB_Classes
