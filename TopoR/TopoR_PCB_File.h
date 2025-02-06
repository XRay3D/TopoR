#pragma once

#include "Commons.h"

#if HEADER
#include "Header.h"
#else
#define Header void*
#endif
#if LAYERS
#include "Layers.h"
#else
#define Layers void*
#endif
#if TEXTSTYLES
#include "TextStyles.h"
#else
#define TextStyles void*
#endif
#if COMPONENTSONBOARD
#include "ComponentsOnBoard.h"
#else
#define ComponentsOnBoard void*
#endif
#if CONNECTIVITY
#include "Connectivity.h"
#else
#define Connectivity void*
#endif
#if CONSTRUCTIVE
#include "Constructive.h"
#else
#define Constructive void*
#endif
#if DIALOGSETTINGS
#include "DialogSettings.h"
#else
#define DialogSettings void*
#endif
#if DISPLAYCONTROL
#include "DisplayControl.h"
#else
#define DisplayControl void*
#endif
#if GROUPS
#include "Groups.h"
#else
#define Groups void*
#endif
#if HISPEEDRULES
#include "HiSpeedRules.h"
#else
#define HiSpeedRules void*
#endif
#if LOCALLIBRARY
#include "LocalLibrary.h"
#else
#define LocalLibrary void*
#endif
#if NETLIST
#include "NetList.h"
#else
#define NetList void*
#endif
#if RULES
#include "Rules.h"
#else
#define Rules void*
#endif
#if SETTINGS
#include "Settings.h"
#else
#define Settings void*
#endif

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 *
 * NOTE Xml::ArrayElem<Package> пустые пропускать и не сериализовать.
 */

namespace TopoR {

struct TopoR_PCB_File {                  // Корневой тег TopoR_PCB_File. Включает все разделы файла.
    Header header;                       // Раздел «Заголовок файла».
    Layers layers;                       // Раздел «Слои». (Обязательный раздел)
    TextStyles textStyles;               // Раздел «Стили надписей».
    LocalLibrary localLibrary;           // Раздел «Библиотечные элементы». (Обязательный раздел)
    Constructive constructive;           // Раздел «Конструктив платы».
    ComponentsOnBoard componentsOnBoard; // Раздел «Компоненты на плате». (Обязательный раздел).
    NetList netList;                     // Раздел «Текущий список соединений».
    Groups groups;                       // Раздел «Группировка объектов».
    HiSpeedRules hiSpeedRules;           // Раздел «Правила для высокоскоростных устройств».
    Rules rules;                         // Раздел «ПРАВИЛА»
                                         /// \note !Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
    Connectivity connectivity;           // Раздел «Соединения на плате».
                                         /// \note В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
    Settings settings;                   // Раздел «Настройки дизайна».
    DisplayControl displayControl;       // Раздел «Настройки отображения».
    DialogSettings dialogSettings;       // Раздел «Настройки диалогов».
};

} // namespace TopoR

#undef ComponentsOnBoard
#undef Connectivity
#undef Constructive
#undef DialogSettings
#undef DisplayControl
#undef Groups
#undef Header
#undef HiSpeedRules
#undef Layers
#undef LocalLibrary
#undef NetList
#undef Rules
#undef Settings
#undef TextStyles
