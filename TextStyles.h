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
	/// Раздел «Стили надписей».
	/// </summary>
	class TextStyles : public std::enable_shared_from_this<TextStyles>
	{
		/// <summary>
		/// Описание стиля надписей.
		/// </summary>
	public:
		class TextStyle : public std::enable_shared_from_this<TextStyle>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::string _name;

			/// <summary>
			/// Параметр стиля надписей: название шрифта.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("fontName")] public string _fontName;
			std::string _fontName;

			/// <summary>
			/// Параметр стиля надписей: высота символов в текущих единицах.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("height", DataType = "float")] public float _height;
			float _height = 0.0F;

			/// <summary>
			/// Параметр стиля надписей: жирность шрифта.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("bold")] public Bool _bold;
			Bool _bold = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _boldSpecified
			bool getBoldSpecified() const;

			/// <summary>
			/// Параметр стиля надписей: курсив.
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("italic")] public Bool _italic;
			Bool _italic = static_cast<Bool>(0);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlIgnore] public bool _italicSpecified
			bool getItalicSpecified() const;
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::string _version;

		/// <summary>
		/// Стили надписей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TextStyle")] public List<TextStyle> _TextStyles;
		std::vector<std::shared_ptr<TextStyle>> _TextStyles;
		bool ShouldSerialize_TextStyles();

		/**********************************************************************
		 * Здесь находятся функции для работы с элементами класса TextStyles. *
		 * Они не являются частью формата TopoR PCB.                          *
		 * ********************************************************************/

		/**********************************************************************/
	};
}
