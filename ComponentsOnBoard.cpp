#include "ComponentsOnBoard.h"

// namespace TopoR_PCB_Classes {

bool ComponentsOnBoard::CompInstance::CompInstance_Pin::ShouldSerialize_PadstackRef() {
    return {}; // FIXME _PadstackRef != nullptr;
}

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getMirrorSpecified() const {
    return _mirror != Bool::off;
}

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getVisibleSpecified() const {
    return _visible != Bool::off;
}

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::ShouldSerialize_Labels() {
    return _Labels.empty() ? false : _Labels.size() > 0;
}

bool ComponentsOnBoard::CompInstance::getFixedSpecified() const {
    return _fixed != Bool::off;
}

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Pins() {
    return _Pins.empty() ? false : _Pins.size() > 0;
}

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Mntholes() {
    return _Mntholes.empty() ? false : _Mntholes.size() > 0;
}

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Attributes() {
    return _Attributes.empty() ? false : _Attributes.size() > 0;
}

QString ComponentsOnBoard::CompInstance::ToString() {
    return _name;
}

bool ComponentsOnBoard::FreePad::getFixedSpecified() const {
    return _fixed != Bool::off;
}

bool ComponentsOnBoard::ShouldSerialize_Components() {
    return _Components.empty() ? false : _Components.size() > 0;
}

bool ComponentsOnBoard::ShouldSerialize_FreePads() {
    return _FreePads.empty() ? false : _FreePads.size() > 0;
}

QString ComponentsOnBoard::AddComponent(QString name, units units, const QString& componentRef, const QString& footprintRef) {
    float x = 0, y = 0; // координаты нового компонента
    if (_Components.empty()) {
        return "";
    }
    while (ComponentIndexOf(name) >= 0) // проверка на уникальность имени и добавление префикса
    {
        name += "_";
    }
    for (std::int32_t i = _Components.size(); i > 0; i--) // вычисление максимально возможных координат
    {
        x = std::max(x, _Components[i - 1]->_Org._x);
        y = std::max(y, _Components[i - 1]->_Org._y);
    }
    float offset = units == units::mm ? 3 : Ut::UnitsConvert(3, dist_::mm, dist_::mil);
    x += offset; // добавление небольшого смещения
    y += offset;

    CompInstance* c = new CompInstance();
    c->_name = name;
    c->_side = side::Top;
    c->_uniqueId = UniqueId();
    c->_angle = 0;
    c->_fixed = Bool::off;
    c->_Org = {}; // FIXME
    c->_Org._x = x;
    c->_Org._y = y;
    c->_ComponentRef = {}; // FIXME
    c->_ComponentRef._ReferenceName = componentRef;
    c->_FootprintRef = {}; // FIXME
    c->_FootprintRef._ReferenceName = footprintRef;
    _Components.push_back(c);

    // C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c was passed to a method or constructor. Handle memory management manually.
    return c->_name;
}

bool ComponentsOnBoard::RemoveComponent(const QString& name) {
    std::int32_t x = ComponentIndexOf(name);
    if (x >= 0) {
        _Components.erase(_Components.begin() + x);
        return true;
    }
    return false;
}

std::int32_t ComponentsOnBoard::ComponentIndexOf(const QString& name) {
    // FIXME   for (std::int32_t x = _Components.empty() ? false : ((_Components.size() != nullptr) ? _Components.size() : 0); x > 0; x--) {
    //        if (_Components[x - 1]->_name == name) {
    //            return x - 1;
    //        }
    //    }
    return -1;
}

std::int32_t ComponentsOnBoard::RenameComponent(const QString& oldname, const QString& newname) {
    std::int32_t x = ComponentIndexOf(oldname);
    if (x >= 0) {
        _Components[x]->_name = newname;
        return x;
    }
    return -1;
}

QString ComponentsOnBoard::UniqueId() {
    QString ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString uniqueId = "";
    //  FIXME  Random* rnd = new Random();
    for (std::int32_t i = 0; i < 8; i++) {
        //     FIXME   uniqueId += ABC[rand->Next(26)];
        uniqueId += ABC[rand() % 26];
    }
    if (_Components.empty() ? false : _Components.size() > 0) {
        for (auto c : _Components) {
            if (c->_uniqueId == uniqueId) {
                uniqueId = UniqueId();
            }
        }
    }

    // delete rnd;
    return uniqueId;
}
// } // namespace TopoR_PCB_Classes
