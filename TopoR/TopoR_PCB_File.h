#pragma once

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 * Мною, Дамиром aka x-ray, 08.02.2025 года сие перекидано на кресты.
 */

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

namespace TopoR {

// Корневой тег TopoR_PCB_File. Включает все разделы файла.
struct TopoR_PCB_File {
#if HEADER
    // Раздел «Заголовок файла».
    Header header;
#endif
#if LAYERS
    // Раздел «Слои». (Обязательный раздел)
    Layers layers;
#endif
#if TEXTSTYLES
    // Раздел «Стили надписей».
    TextStyles textStyles;
#endif
#if LOCALLIBRARY
    // Раздел «Библиотечные элементы». (Обязательный раздел)
    LocalLibrary localLibrary;
#endif
#if CONSTRUCTIVE
    // Раздел «Конструктив платы».
    Constructive constructive;
#endif
#if COMPONENTSONBOARD
    // Раздел «Компоненты на плате». (Обязательный раздел).
    ComponentsOnBoard componentsOnBoard;
#endif
#if NETLIST
    // Раздел «Текущий список соединений».
    NetList netList;
#endif
#if GROUPS
    // Раздел «Группировка объектов».
    Groups groups;
#endif
#if HISPEEDRULES
    // Раздел «Правила для высокоскоростных устройств».
    HiSpeedRules hiSpeedRules;
#endif
#if RULES
    // Раздел «ПРАВИЛА»
    // NOTE !Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
    Rules rules;
#endif
#if CONNECTIVITY
    // Раздел «Соединения на плате».
    // NOTE В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
    Connectivity connectivity;
#endif
#if SETTINGS
    // Раздел «Настройки дизайна».
    Settings settings;
#endif
#if DISPLAYCONTROL
    // Раздел «Настройки отображения».
    DisplayControl displayControl;
#endif
#if DIALOGSETTINGS
    // Раздел «Настройки диалогов».
    DialogSettings dialogSettings;
#endif
};

} // namespace TopoR
