#include "TextStyles.h"

namespace TopoR_PCB_Classes {

bool TextStyles::TextStyle::getBoldSpecified() const {
    return bold != Bool::off;
}

bool TextStyles::TextStyle::getItalicSpecified() const {
    return italic != Bool::off;
}

bool TextStyles::ShouldSerialize_TextStyles() {
    return TextStyles.size();
}

} // namespace TopoR_PCB_Classes
