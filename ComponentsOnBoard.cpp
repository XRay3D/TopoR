#include "ComponentsOnBoard.h"

namespace TopoR_PCB_Classes
{

	bool ComponentsOnBoard::CompInstance::CompInstance_Pin::ShouldSerialize_PadstackRef()
	{
		return _PadstackRef != nullptr;
	}

	bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getMirrorSpecified() const
	{
		return _mirror != Bool::off;
	}

	bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::CompInstance_Attribute_Label::getVisibleSpecified() const
	{
		return _visible != Bool::off;
	}

	bool ComponentsOnBoard::CompInstance::CompInstance_Attribute::ShouldSerialize_Labels()
	{
		return (_Labels.empty() ? nullptr : _Labels.size()) > 0;
	}

	bool ComponentsOnBoard::CompInstance::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Pins()
	{
		return (_Pins.empty() ? nullptr : _Pins.size()) > 0;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Mntholes()
	{
		return (_Mntholes.empty() ? nullptr : _Mntholes.size()) > 0;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Attributes()
	{
		return (_Attributes.empty() ? nullptr : _Attributes.size()) > 0;
	}

	std::wstring ComponentsOnBoard::CompInstance::ToString()
	{
		return _name;
	}

	bool ComponentsOnBoard::FreePad::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool ComponentsOnBoard::ShouldSerialize_Components()
	{
		return (_Components.empty() ? nullptr : _Components.size()) > 0;
	}

	bool ComponentsOnBoard::ShouldSerialize_FreePads()
	{
		return (_FreePads.empty() ? nullptr : _FreePads.size()) > 0;
	}

	std::wstring ComponentsOnBoard::AddComponent(const std::wstring &name, units units, const std::wstring &componentRef, const std::wstring &footprintRef)
	{
		float x = 0, y = 0; //координаты нового компонента
		if (_Components.empty())
		{
			return L"";
		}
		while (ComponentIndexOf(name) >= 0) //проверка на уникальность имени и добавление префикса
		{
			name += L"_";
		}
		for (int i = _Components.size(); i > 0; i--) //вычисление максимально возможных координат
		{
			x = std::max(x, _Components[i - 1]->_Org._x);
			y = std::max(y, _Components[i - 1]->_Org._y);
		}
		float offset = units == units::mm ? 3 : Ut::UnitsConvert(3, dist::mm, dist::mil);
		x += offset; //добавление небольшого смещения
		y += offset;

		std::shared_ptr<Org> tempVar = std::make_shared<Org>();
		tempVar->_x = x;
		tempVar->_y = y;
		std::shared_ptr<ComponentRef> tempVar2 = std::make_shared<ComponentRef>();
		tempVar2->_ReferenceName = componentRef;
		std::shared_ptr<FootprintRef> tempVar3 = std::make_shared<FootprintRef>();
		tempVar3->_ReferenceName = footprintRef;
		std::shared_ptr<CompInstance> c = {._name = name, ._side = side::Top, ._uniqueId = UniqueId(), ._angle = 0, ._fixed = Bool::off, ._Org = tempVar, ._ComponentRef = tempVar2, ._FootprintRef = tempVar3};
		_Components.push_back(c);
		return c->_name;
	}

	bool ComponentsOnBoard::RemoveComponent(const std::wstring &name)
	{
		int x = ComponentIndexOf(name);
		if (x >= 0)
		{
			_Components.erase(_Components.begin() + x);
			return true;
		}
		return false;
	}

	int ComponentsOnBoard::ComponentIndexOf(const std::wstring &name)
	{
		for (int x = _Components.empty() ? nullptr : ((_Components.size() != nullptr) ? _Components.size() : 0); x > 0; x--)
		{
			if (_Components[x - 1]->_name == name)
			{
				return x - 1;
			}
		}
		return -1;
	}

	int ComponentsOnBoard::RenameComponent(const std::wstring &oldname, const std::wstring &newname)
	{
		int x = ComponentIndexOf(oldname);
		if (x >= 0)
		{
			_Components[x]->_name = newname;
			return x;
		}
		return -1;
	}

	std::wstring ComponentsOnBoard::UniqueId()
	{
		std::wstring ABC = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::wstring uniqueId = L"";
		std::shared_ptr<Random> rnd = std::make_shared<Random>();
		for (int i = 0; i < 8; i++)
		{
			uniqueId += ABC[rnd->Next(26)];
		}
		if ((_Components.empty() ? nullptr : _Components.size()) > 0)
		{
			for (auto c : _Components)
			{
				if (c->_uniqueId == uniqueId)
				{
					uniqueId = UniqueId();
				}
			}
		}
		return uniqueId;
	}
}
