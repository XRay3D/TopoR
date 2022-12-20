#pragma once

#include "Header.h"
#include "Layers.h"
#include "TextStyles.h"
#include "LocalLibrary.h"
#include "Constructive.h"
#include "ComponentsOnBoard.h"
#include "NetList.h"
#include "Groups.h"
#include "HiSpeedRules.h"
#include "Rules.h"
#include "Connectivity.h"
#include "Settings.h"
#include "DisplayControl.h"
#include "DialogSettings.h"
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */



namespace TopoR_PCB_Classes
{
	/// <summary>
	/// Корневой тег. Включает все разделы файла.
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlRoot("TopoR_PCB_File")] public class TopoR_PCB_File
	class TopoR_PCB_File : public std::enable_shared_from_this<TopoR_PCB_File>
	{
		/// <summary>
		/// Раздел «Заголовок файла».
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Header")] public Header _Header;
		std::shared_ptr<Header> _Header;

		/// <summary>
		/// Раздел «Слои». (Обязательный раздел)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Layers")] public Layers _Layers;
		std::shared_ptr<Layers> _Layers;

		/// <summary>
		/// Раздел «Стили надписей».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("TextStyles")] public TextStyles _TextStyles;
		std::shared_ptr<TextStyles> _TextStyles;

		/// <summary>
		/// Раздел «Библиотечные элементы». (Обязательный раздел)
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LocalLibrary")] public LocalLibrary _LocalLibrary;
		std::shared_ptr<LocalLibrary> _LocalLibrary;

		/// <summary>
		/// Раздел «Конструктив платы».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Constructive")] public Constructive _Constructive;
		std::shared_ptr<Constructive> _Constructive;

		/// <summary>
		/// Раздел «Компоненты на плате». (Обязательный раздел).
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("ComponentsOnBoard")] public ComponentsOnBoard _ComponentsOnBoard;
		std::shared_ptr<ComponentsOnBoard> _ComponentsOnBoard;

		/// <summary>
		/// Раздел «Текущий список соединений».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetList")] public NetList _NetList;
		std::shared_ptr<NetList> _NetList;

		/// <summary>
		/// Раздел «Группировка объектов».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Groups")] public Groups _Groups;
		std::shared_ptr<Groups> _Groups;

		/// <summary>
		/// Раздел «Правила для высокоскоростных устройств».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("HiSpeedRules")] public HiSpeedRules _HiSpeedRules;
		std::shared_ptr<HiSpeedRules> _HiSpeedRules;

		/// <summary>
		/// Раздел «Правила».
		/// </summary>
		/// <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Rules")] public Rules _Rules;
		std::shared_ptr<Rules> _Rules;

		/// <summary>
		/// Раздел «Соединения на плате».
		/// </summary>
		/// <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Connectivity")] public Connectivity _Connectivity;
		std::shared_ptr<Connectivity> _Connectivity;

		/// <summary>
		/// Раздел «Настройки дизайна».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("Settings")] public Settings _Settings;
		std::shared_ptr<Settings> _Settings;

		/// <summary>
		/// Раздел «Настройки отображения».
		/// </summary>

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DisplayControl")] public DisplayControl _DisplayControl;
		std::shared_ptr<DisplayControl> _DisplayControl;

		/// <summary>
		/// Раздел «Настройки диалогов».
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("DialogSettings")] public DialogSettings _DialogSettings;
		std::shared_ptr<DialogSettings> _DialogSettings;
	};
}
