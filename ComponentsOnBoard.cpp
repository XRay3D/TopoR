#include "ComponentsOnBoard.h"

namespace TopoR_PCB_Classes {

bool ComponentsOnBoard::CompInstance::CompInstance_Pin::ShouldSerialize_PadstackRef() { return _PadstackRef.has_value(); }

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getMirrorSpecified() const { return _mirror != Bool::off; }

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getVisibleSpecified() const { return _visible != Bool::off; }

bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::ShouldSerialize_Labels() { return _Labels.size(); }

bool ComponentsOnBoard::CompInstance::getFixedSpecified() const { return _fixed != Bool::off; }

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Pins() { return _Pins.size(); }

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Mntholes() { return _Mntholes.size(); }

bool ComponentsOnBoard::CompInstance::ShouldSerialize_Attributes() { return _Attributes.size(); }

std::string ComponentsOnBoard::CompInstance::ToString() { return _name; }

bool ComponentsOnBoard::FreePad::getFixedSpecified() const { return _fixed != Bool::off; }

bool ComponentsOnBoard::ShouldSerialize_Components() { return _Components.size(); }

bool ComponentsOnBoard::ShouldSerialize_FreePads() { return _FreePads.size(); }

std::string ComponentsOnBoard::AddComponent(const std::string& name, units units, const std::string& componentRef, const std::string& footprintRef) {
    /* float x = 0, y = 0; // координаты нового компонента
     if(_Components.empty()) return"";
     while(ComponentIndexOf(name) >= 0) // проверка на уникальность имени и добавление префикса
         name +="_";
     forint.size(); i--) // вычисление максимально возможных координат
     {
         x = std::max(x, _Components[i - 1].value()._Org._x);
         y = std::max(y, _Components[i - 1].value()._Org._y);
     }
     float offset = units == units::mm ? 3 : Ut::UnitsConvert(3, dist::mm, dist::mil);
     x += offset; // добавление небольшого смещения
     y += offset;

     std::optional<Org> tempVar = std::make_shared<Org>();
     tempVar.value()._x = x;
     tempVar.value()._y = y;
     std::optional<ComponentRef> tempVar2 = std::make_shared<ComponentRef>();
     tempVar2.value()._ReferenceName = componentRef;
     std::optional<FootprintRef> tempVar3 = std::make_shared<FootprintRef>();
     tempVar3.value()._ReferenceName = footprintRef;
     std::optional<CompInstance> c = {._name = name, ._side = side::Top, ._uniqueId = UniqueId(), ._angle = 0, ._fixed = Bool::off, ._Org = tempVar, ._ComponentRef = tempVar2, ._FootprintRef = tempVar3};
     _Components.push_back(c);
     return c.value()._name;*/
    return {};
}

bool ComponentsOnBoard::RemoveComponent(const std::string& name) {
    int x = ComponentIndexOf(name);
    if(x >= 0) {
        _Components.erase(_Components.begin() + x);
        return true;
    }
    return false;
}

int ComponentsOnBoard::ComponentIndexOf(const std::string& name) {
    /* forint.size(); x--)
         if(_Components[x - 1].value()._name == name)            return x - 1;*/
    return -1;
}

int ComponentsOnBoard::RenameComponent(const std::string& oldname, const std::string& newname) {
    int x = ComponentIndexOf(oldname);
    if(x >= 0) {
        _Components[x].value()._name = newname;
        return x;
    }
    return -1;
}

std::string ComponentsOnBoard::UniqueId() {
    std::string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string uniqueId = "";
    /*   std::optional<Random> rnd = std::make_shared<Random>();
      for(int i = 0; i < 8; i++)
          uniqueId += ABC[rnd.value().Next(26)];
      if(_Components.size()) {
          for(auto c: _Components)
              if(c.value()._uniqueId == uniqueId)
                  uniqueId = UniqueId();
      }*/
    return uniqueId;
}
} // namespace TopoR_PCB_Classes
