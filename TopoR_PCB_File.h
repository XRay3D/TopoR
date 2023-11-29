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
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Корневой тег. Включает все разделы файла.
// [XmlRoot("TopoR_PCB_File")] public struct  TopoR_PCB_File
struct TopoR_PCB_File {

    // Раздел «Заголовок файла».
    // [XmlElement("Header")] public Header _Header;
    std::optional<Header> _Header;
    /*
        // Раздел «Слои». (Обязательный раздел)
        // [XmlElement("Layers")] public Layers _Layers;
        std::optional<Layers> _Layers;

        // Раздел «Стили надписей».
        // [XmlElement("TextStyles")] public TextStyles _TextStyles;
        std::optional<TextStyles> _TextStyles;

        // Раздел «Библиотечные элементы». (Обязательный раздел)
        // [XmlElement("LocalLibrary")] public LocalLibrary _LocalLibrary;
        std::optional<LocalLibrary> _LocalLibrary;

        // Раздел «Конструктив платы».
        // [XmlElement("Constructive")] public Constructive _Constructive;
        std::optional<Constructive> _Constructive;

        // Раздел «Компоненты на плате». (Обязательный раздел).
        // [XmlElement("ComponentsOnBoard")] public ComponentsOnBoard _ComponentsOnBoard;
        std::optional<ComponentsOnBoard> _ComponentsOnBoard;

        // Раздел «Текущий список соединений».
        // [XmlElement("NetList")] public NetList _NetList;
        std::optional<NetList> _NetList;

        // Раздел «Группировка объектов».
        // [XmlElement("Groups")] public Groups _Groups;
        std::optional<Groups> _Groups;

        // Раздел «Правила для высокоскоростных устройств».
        // [XmlElement("HiSpeedRules")] public HiSpeedRules _HiSpeedRules;
        std::optional<HiSpeedRules> _HiSpeedRules;

        // Раздел «Правила».

        // <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
        // [XmlElement("Rules")] public Rules _Rules;
        std::optional<Rules> _Rules;

        // Раздел «Соединения на плате».

        // <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
        // [XmlElement("Connectivity")] public Connectivity _Connectivity;
        std::optional<Connectivity> _Connectivity;

        // Раздел «Настройки дизайна».
        // [XmlElement("Settings")] public Settings _Settings;
        std::optional<Settings> _Settings;

        // Раздел «Настройки отображения».
        // [XmlElement("DisplayControl")] public DisplayControl _DisplayControl;
        std::optional<DisplayControl> _DisplayControl;

        // Раздел «Настройки диалогов».
        // [XmlElement("DialogSettings")] public DialogSettings _DialogSettings;
        std::optional<DialogSettings> _DialogSettings;*/
};
} // namespace TopoR_PCB_Classes
