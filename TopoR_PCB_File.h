#pragma once

#include "ComponentsOnBoard.h"
#include "Connectivity.h"
#include "Constructive.h"
#include "DialogSettings.h"
#include "DisplayControl.h"
#include "Groups.h"
#include "Header.h"
#include "HiSpeedRules.h"
#include "Layers.h"
#include "LocalLibrary.h"
#include "NetList.h"
#include "Rules.h"
#include "Settings.h"
#include "TextStyles.h"

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

// namespace TopoR_PCB_Classes {
/// <summary>
/// Корневой тег. Включает все разделы файла.
/// </summary>
// C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
// ORIGINAL LINE: [XmlRoot("TopoR_PCB_File")] public class TopoR_PCB_File
class TopoR_PCB_File : public QSerializer {
    Q_GADGET
    QS_META_OBJECT_METHOD
    /// <summary>
    /// Раздел «Заголовок файла».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Header")] public Header _Header;
    QS_OBJECT(Header_, Header);

    /// <summary>
    /// Раздел «Слои». (Обязательный раздел)
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Layers")] public Layers _Layers;
    QS_OBJECT(Layers_, Layers)

    /// <summary>
    /// Раздел «Стили надписей».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("TextStyles")] public TextStyles _TextStyles;
    TextStyles _TextStyles;

    /// <summary>
    /// Раздел «Библиотечные элементы». (Обязательный раздел)
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("LocalLibrary")] public LocalLibrary _LocalLibrary;
    LocalLibrary _LocalLibrary;

    /// <summary>
    /// Раздел «Конструктив платы».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Constructive")] public Constructive _Constructive;
    Constructive _Constructive;

    /// <summary>
    /// Раздел «Компоненты на плате». (Обязательный раздел).
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("ComponentsOnBoard")] public ComponentsOnBoard _ComponentsOnBoard;
    ComponentsOnBoard _ComponentsOnBoard;

    /// <summary>
    /// Раздел «Текущий список соединений».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("NetList")] public NetList _NetList;
    NetList _NetList;

    /// <summary>
    /// Раздел «Группировка объектов».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Groups")] public Groups _Groups;
    Groups _Groups;

    /// <summary>
    /// Раздел «Правила для высокоскоростных устройств».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("HiSpeedRules")] public HiSpeedRules _HiSpeedRules;
    HiSpeedRules _HiSpeedRules;

    /// <summary>
    /// Раздел «Правила».
    /// </summary>
    /// <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Rules")] public Rules _Rules;
    Rules _Rules;

    /// <summary>
    /// Раздел «Соединения на плате».
    /// </summary>
    /// <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Connectivity")] public Connectivity _Connectivity;
    Connectivity _Connectivity;

    /// <summary>
    /// Раздел «Настройки дизайна».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Settings")] public Settings _Settings;
    Settings _Settings;

    /// <summary>
    /// Раздел «Настройки отображения».
    /// </summary>

    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("DisplayControl")] public DisplayControl _DisplayControl;
    DisplayControl _DisplayControl;

    /// <summary>
    /// Раздел «Настройки диалогов».
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("DialogSettings")] public DialogSettings _DialogSettings;
    DialogSettings _DialogSettings;
    //    virtual ~TopoR_PCB_File() {
    // delete _Header;
    // delete _Layers;
    // delete _TextStyles;
    // delete _LocalLibrary;
    // delete _Constructive;
    // delete _ComponentsOnBoard;
    // delete _NetList;
    // delete _Groups;
    // delete _HiSpeedRules;
    // delete _Rules;
    // delete _Connectivity;
    // delete _Settings;
    // delete _DisplayControl;
    // delete _DialogSettings;
    //    }
};
// } // namespace TopoR_PCB_Classes
