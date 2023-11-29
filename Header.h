#pragma once

#include "Commons.h"
#include <string>
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */


namespace TopoR_PCB_Classes
{
	/// <summary>
	/// Раздел «Заголовок файла».
	/// </summary>
	class Header : public std::enable_shared_from_this<Header>
	{
		/// <summary>
		/// Единицы измерений для всего файла.
		/// </summary>
	public:
		class Units_Header : public std::enable_shared_from_this<Units_Header>
		{
			/// <summary>
			/// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("dist")] public dist _dist;
			dist _dist = static_cast<dist>(0);

			/// <summary>
			/// Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("time")] public time _time;
			time _time = static_cast<time>(0);
		};
		/// <summary>
		/// Название формата файла.
		/// </summary>

	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Format")] public string _Format;
		std::wstring _Format;

		/// <summary>
		/// Версия формата.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Version")] public string _Version;
		std::wstring _Version;

		/// <summary>
		/// Название программы, создавшей файл.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Program")] public string _Program;
		std::wstring _Program;

		/// <summary>
		/// Дата и время создания файла (в произвольной форме).
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Date")] public string _Date;
		std::wstring _Date;

		/// <summary>
		/// Формат импортированного файла, из которого был получен дизайн.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("OriginalFormat")] public string _OriginalFormat;
		std::wstring _OriginalFormat;

		/// <summary>
		/// Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("OriginalFile")] public string _OriginalFile;
		std::wstring _OriginalFile;

		/// <summary>
		/// Единицы измерения для всего файла.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Units")] public Units_Header _Units;
		std::shared_ptr<Units_Header> _Units;
	};
}
