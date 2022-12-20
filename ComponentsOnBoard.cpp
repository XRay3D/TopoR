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
		return _Labels.empty() ? nullptr : _Labels.size() > 0;
	}

	bool ComponentsOnBoard::CompInstance::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Pins()
	{
		return _Pins.empty() ? nullptr : _Pins.size() > 0;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Mntholes()
	{
		return _Mntholes.empty() ? nullptr : _Mntholes.size() > 0;
	}

	bool ComponentsOnBoard::CompInstance::ShouldSerialize_Attributes()
	{
		return _Attributes.empty() ? nullptr : _Attributes.size() > 0;
	}

	std::string ComponentsOnBoard::CompInstance::ToString()
	{
		return _name;
	}

	bool ComponentsOnBoard::FreePad::getFixedSpecified() const
	{
		return _fixed != Bool::off;
	}

	bool ComponentsOnBoard::ShouldSerialize_Components()
	{
		return _Components.empty() ? nullptr : _Components.size() > 0;
	}

	bool ComponentsOnBoard::ShouldSerialize_FreePads()
	{
		return _FreePads.empty() ? nullptr : _FreePads.size() > 0;
	}

	std::string ComponentsOnBoard::AddComponent(const std::string &name, units units, const std::string &componentRef, const std::string &footprintRef)
	{
		float x = 0, y = 0; //координаты нового компонента
		if (_Components.empty())
		{
			return "";
		}
		while (ComponentIndexOf(name) >= 0) //проверка на уникальность имени и добавление префикса
		{
			name += "_";
		}
		for (std::int32_t i = _Components.size(); i > 0; i--) //вычисление максимально возможных координат
		{
			x = std::max(x, _Components[i - 1]->_Org._x);
			y = std::max(y, _Components[i - 1]->_Org._y);
		}
		float offset = units == units::mm ? 3 : Ut::UnitsConvert(3, dist::mm, dist::mil);
		x += offset; //добавление небольшого смещения
		y += offset;

		std::shared_ptr<CompInstance> c = std::make_shared<CompInstance>();
		c->_name = name;
		c->_side = side::Top;
		c->_uniqueId = UniqueId();
		c->_angle = 0;
		c->_fixed = Bool::off;
		c->_Org = std::make_shared<Org>();
		c->_Org->_x = x;
		c->_Org->_y = y;
		c->_ComponentRef = std::make_shared<ComponentRef>();
		c->_ComponentRef->_ReferenceName = componentRef;
		c->_FootprintRef = std::make_shared<FootprintRef>();
		c->_FootprintRef->_ReferenceName = footprintRef;
		_Components.push_back(c);
		return c->_name;
	}

	bool ComponentsOnBoard::RemoveComponent(const std::string &name)
	{
		std::int32_t x = ComponentIndexOf(name);
		if (x >= 0)
		{
			_Components.erase(_Components.begin() + x);
			return true;
		}
		return false;
	}

	std::int32_t ComponentsOnBoard::ComponentIndexOf(const std::string &name)
	{
		for (std::int32_t x = _Components.empty() ? nullptr : ((_Components.size() != nullptr) ? _Components.size() : 0); x > 0; x--)
		{
			if (_Components[x - 1]->_name == name)
			{
				return x - 1;
			}
		}
		return -1;
	}

	std::int32_t ComponentsOnBoard::RenameComponent(const std::string &oldname, const std::string &newname)
	{
		std::int32_t x = ComponentIndexOf(oldname);
		if (x >= 0)
		{
			_Components[x]->_name = newname;
			return x;
		}
		return -1;
	}

	std::string ComponentsOnBoard::UniqueId()
	{
		std::string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string uniqueId = "";
		std::shared_ptr<Random> rnd = std::make_shared<Random>();
		for (std::int32_t i = 0; i < 8; i++)
		{
			uniqueId += ABC[rnd->Next(26)];
		}
		if (_Components.empty() ? nullptr : _Components.size() > 0)
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
