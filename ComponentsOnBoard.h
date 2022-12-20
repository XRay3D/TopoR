#pragma once

#include "Commons.h"
#include <string>
#include <vector>
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */


namespace TopoR_PCB_Classes
{
	/// <summary>
	/// Компоненты на плате (обязательный раздел).
	/// </summary>
	class ComponentsOnBoard : public std::enable_shared_from_this<ComponentsOnBoard>
	{
		/// <summary>
		/// Описание компонента на плате.
		/// </summary>
		/// <remarks>! Если компонент расположен на нижней стороне платы, его посадочное место отображается зеркально относительно вертикальной оси посадочного места, описанного в библиотеке(т.е.без угла поворота). Стеки контактных площадок переворачиваются.</remarks>
	public:
		class CompInstance : public std::enable_shared_from_this<CompInstance>
		{

			/// <summary>
			/// Описание контакта компонента на плате.
			/// </summary>
			/// <remarks>! Если PadstackRef не указан, то стек контактных площадок берётся из посадочного места.</remarks>
		public:
			class CompInstance_Pin : public std::enable_shared_from_this<CompInstance_Pin>
			{
				/// <summary>
				/// Номер контакта компонента.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("padNum", DataType = "int")] public int _padNum;
				std::int32_t _padNum = 0;

				/// <summary>
				/// Ссылка на стек контактных площадок.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadstackRef")] public PadstackRef _PadstackRef;
				std::shared_ptr<PadstackRef> _PadstackRef;
				bool ShouldSerialize_PadstackRef();
				/// <summary>
				/// Точка привязки объекта.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
				std::shared_ptr<Org> _Org;
			};

			/// <summary>
			/// Описание монтажного отверстия в компоненте на плате.
			/// </summary>
		public:
			class CompInstance_Mnthole : public std::enable_shared_from_this<CompInstance_Mnthole>
			{
				/// <summary>
				/// Ссылка на монтажное отверстие в посадочном месте.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("mntholeRef")] public string _mntholeRef;
				std::string _mntholeRef;

				/// <summary>
				/// Задаёт угол в градусах c точностью до тысячных долей.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
				float _angle = 0.0F;

				/// <summary>
				/// Ссылка на стек контактных площадок.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadstackRef")] public PadstackRef _PadstackRef;
				std::shared_ptr<PadstackRef> _PadstackRef;

				/// <summary>
				/// Cсылка на цепь.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
				std::shared_ptr<NetRef> _NetRef;
			};

			/// <summary>
			/// Описание атрибута компонента на плате.
			/// </summary>
		public:
			class CompInstance_Attribute : public std::enable_shared_from_this<CompInstance_Attribute>
			{
				/// <summary>
				/// Описание ярлыка компонента на плате.
				/// </summary>
			public:
				class CompInstance_Attribute_Label : public std::enable_shared_from_this<CompInstance_Attribute_Label>
				{
					/// <summary>
					/// Задаёт угол в градусах c точностью до тысячных долей.
					/// </summary>
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
					float _angle = 0.0F;

					/// <summary>
					/// Параметр надписей и ярлыков: зеркальность отображения.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("mirror")] public Bool _mirror;
					Bool _mirror = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _mirrorSpecified
					bool getMirrorSpecified() const;

					/// <summary>
					/// Параметр надписей (ярлыков): способ выравнивания текста.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("align")] public align _align;
					align _align = static_cast<align>(0);

					/// <summary>
					/// Флаг видимости.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("visible")] public Bool _visible;
					Bool _visible = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _visibleSpecified
					bool getVisibleSpecified() const;

					/// <summary>
					/// Ссылка на слой.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef")] public LayerRef _LayerRef;
					std::shared_ptr<LayerRef> _LayerRef;

					/// <summary>
					/// Ссылка на стиль надписей.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef;
					std::shared_ptr<TextStyleRef> _TextStyleRef;

					/// <summary>
					/// Точка привязки объекта.
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
					std::shared_ptr<Org> _Org;
				};

				/// <summary>
				/// Тип предопределённого атрибута компонента.
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("type")] public type _type;
				type _type = static_cast<type>(0);

				/// <summary>
				/// Имя объекта или ссылка на именованный объект.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
				std::string _name;

				/// <summary>
				/// Значение атрибута.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("value")] public string _value;
				std::string _value;

				/// <summary>
				/// Ярлыки.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Label")] public List<CompInstance_Attribute_Label> _Labels;
				std::vector<std::shared_ptr<CompInstance_Attribute_Label>> _Labels;
				bool ShouldSerialize_Labels();
			};

			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::string _name;

			/// <summary>
			/// Уникальный идентификатор компонента. Используется при синхронизации. Необязательный атрибут.
			/// Если не задан, то будет создан при импорте файла.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("uniqueId")] public string _uniqueId;
			std::string _uniqueId;

			/// <summary>
			/// Сторона объекта.
			/// </summary>
			/// <remarks>!Значение Both возможно только при описании запретов размещения.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("side")] public side _side;
			side _side = static_cast<side>(0);

			/// <summary>
			/// Задаёт угол в градусах c точностью до тысячных долей.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
			float _angle = 0.0F;

			/// <summary>
			/// Признак фиксации.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fixed")] public Bool _fixed;
			Bool _fixed = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _fixedSpecified
			bool getFixedSpecified() const;

			/// <summary>
			/// Ссылка на схемный компонент.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ComponentRef")] public ComponentRef _ComponentRef;
			std::shared_ptr<ComponentRef> _ComponentRef;

			/// <summary>
			/// Ссылка на посадочное место.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("FootprintRef")] public FootprintRef _FootprintRef;
			std::shared_ptr<FootprintRef> _FootprintRef;

			/// <summary>
			/// Точка привязки объекта.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
			std::shared_ptr<Org> _Org;

			/// <summary>
			/// Контакты компонента на плате.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Pins")][XmlArrayItem("Pin")] public List<CompInstance_Pin> _Pins;
			std::vector<std::shared_ptr<CompInstance_Pin>> _Pins;
			bool ShouldSerialize_Pins();
			/// <summary>
			/// Монтажные отверстия.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<CompInstance_Mnthole> _Mntholes;
			std::vector<std::shared_ptr<CompInstance_Mnthole>> _Mntholes;
			bool ShouldSerialize_Mntholes();
			/// <summary>
			/// Атрибуты компонента.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<CompInstance_Attribute> _Attributes;
			std::vector<std::shared_ptr<CompInstance_Attribute>> _Attributes;
			bool ShouldSerialize_Attributes();


			/************************************************************************
			 * Здесь находятся функции для работы с элементами класса CompInstance. *
			 * Они не являются частью формата TopoR PCB.                            *
			 * **********************************************************************/
			/// <summary>
			/// Для отображения имени компонента
			/// </summary>
			/// <returns></returns>
			std::string ToString();
			/***********************************************************************/
		};

		/// <summary>
		/// Описание одиночного контакта..
		/// </summary>
	public:
		class FreePad : public std::enable_shared_from_this<FreePad>
		{
			/// <summary>
			/// Сторона объекта.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("side")] public side _side;
			side _side = static_cast<side>(0);

			/// <summary>
			/// Задаёт угол в градусах c точностью до тысячных долей.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("angle", DataType = "float")] public float _angle;
			float _angle = 0.0F;

			/// <summary>
			/// Признак фиксации.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fixed")] public Bool _fixed;
			Bool _fixed = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _fixedSpecified
			bool getFixedSpecified() const;

			/// <summary>
			/// Ссылка на стек контактных площадок.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("PadstackRef")] public PadstackRef _PadstackRef;
			std::shared_ptr<PadstackRef> _PadstackRef;

			/// <summary>
			/// Cсылка на цепь.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef")] public NetRef _NetRef;
			std::shared_ptr<NetRef> _NetRef;

			/// <summary>
			/// Точка привязки объекта.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Org")] public Org _Org;
			std::shared_ptr<Org> _Org;
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::string _version;

		/// <summary>
		/// Описание компонентов на плате (инстанции компонентов)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("Components")][XmlArrayItem("CompInstance")] public List<CompInstance> _Components;
		std::vector<std::shared_ptr<CompInstance>> _Components;
		bool ShouldSerialize_Components();
		/// <summary>
		/// Описание одиночных контактов.(инстанции компонентов)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("FreePads")][XmlArrayItem("FreePad")] public List<FreePad> _FreePads;
		std::vector<std::shared_ptr<FreePad>> _FreePads;
		bool ShouldSerialize_FreePads();


		/*****************************************************************************
		 * Здесь находятся функции для работы с элементами класса ComponentsOnBoard. *
		 * Они не являются частью формата TopoR PCB.                                 *
		 * ***************************************************************************/

		/// <summary>
		/// Добавление компонента
		/// </summary>
		/// <param name="name">Имя нового компонента. Если имя неуникально, будет добавлен префикс _</param>
		/// <param name="units">текущие единицы измерения</param>
		/// <param name="componentRef">ссылка на библиотеку компонентов</param>
		/// <param name="footprintRef">ссылка на библиотеку посадочных мест</param>
		/// <returns>Имя нового компонента</returns>
		std::string AddComponent(const std::string &name, units units, const std::string &componentRef, const std::string &footprintRef);
		/// <summary>
		/// Удаление компонента по имени
		/// </summary>
		/// <param name="name">уникальный имя компонента</param>
		/// <returns>true - если было произведено удаление, иначе (компонент не найден) - false</returns>
		bool RemoveComponent(const std::string &name);
		/// <summary>
		/// Индекс компонента
		/// </summary>
		/// <param name="name">уникальное имя компонента</param>
		/// <returns>индекс компонента или -1, если компонент отсутствует</returns>
		std::int32_t ComponentIndexOf(const std::string &name);

		/// <summary>
		/// Переименование компонента
		/// </summary>
		/// <param name="oldname">старое имя компонента</param>
		/// <param name="newname">новое имя компонента</param>
		/// <returns>индекс компонента, если было произведено переименование, -1, если компонент не найден</returns>
		std::int32_t RenameComponent(const std::string &oldname, const std::string &newname);

		/// <summary>
		/// Генерация уникального идентификатора
		/// </summary>
		/// <returns>string like "ABCDEFGH"</returns>
		std::string UniqueId();

		/*************************************************************************************/

	};
}
