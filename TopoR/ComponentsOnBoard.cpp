#include "ComponentsOnBoard.h"
namespace TopoR {
// QString ComponentsOnBoard::CompInstance::ToString() { return name; }
// QString ComponentsOnBoard::AddComponent(const QString& name, units units, const QString& componentRef, const QString& footprintRef) {
//     /* float x = 0, y = 0; // координаты нового компонента
//      if(_Components.empty()) return"";
//      while(ComponentIndexOf(name) >= 0) // проверка на уникальность имени и добавление префикса
//          name +="_";
//      forint.size(); i--) // вычисление максимально возможных координат
//      {
//          x = std::max(x, Components_[i - 1].value()._Org._x);
//          y = std::max(y, Components_[i - 1].value()._Org._y);
//      }
//      float offset = units == units::mm ? 3 : Ut::UnitsConvert(3, dist::mm, dist::mil);
//      x += offset; // добавление небольшого смещения
//      y += offset;
//      Org tempVar = std::make_shared<Org>();
//      tempVar.value()._x = x;
//      tempVar.value()._y = y;
//      ComponentRef tempVar2 = std::make_shared<ComponentRef>();
//      tempVar2.value()._ReferenceName = componentRef;
//      FootprintRef tempVar3 = std::make_shared<FootprintRef>();
//      tempVar3.value()._ReferenceName = footprintRef;
//      CompInstance c = {._name = name, ._side = side::Top, ._uniqueId = UniqueId(), ._angle = 0, ._fixed = Bool::off, ._Org = tempVar, ._ComponentRef = tempVar2, ._FootprintRef = tempVar3};
//      Components.push_back(c);
//      return c.value()._name;*/
//     return {};
// }
// bool ComponentsOnBoard::RemoveComponent(const QString& name) {
//     int x = ComponentIndexOf(name);
//     if(x >= 0) {
//         Components.erase(Components.begin() + x);
//         return true;
//     }
//     return false;
// }
// int ComponentsOnBoard::ComponentIndexOf(const QString& name) {
//     /* forint.size(); x--)
//          if(_Components[x - 1].value()._name == name)            return x - 1;*/
//     return -1;
// }
// int ComponentsOnBoard::RenameComponent(const QString& oldname, const QString& newname) {
//     // int x = ComponentIndexOf(oldname);
//     // if (x >= 0) {
//     //     Components_[x].value()._name = newname;
//     //     return x;
//     // }
//     return -1;
// }
// QString ComponentsOnBoard::UniqueId() {
//     QString ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//     QString uniqueId = "";
//     /*   Random rnd = std::make_shared<Random>();
//       for(int i = 0; i < 8; i++)
//           uniqueId += ABC[rnd.value().Next(26)];
//       if(_Components.size()) {
//           for(auto c: Components_)
//               if(c.value()._uniqueId == uniqueId)
//                   uniqueId = UniqueId();
//       }*/
//     return uniqueId;
// }
} // namespace TopoR
