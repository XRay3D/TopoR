#pragma once

// clang-format off

#include "Commons.h"

#if HEADER
#include "Header.h"
#endif
#if LAYERS
#include "Layers.h"
#endif
#if TEXTSTYLES
#include "TextStyles.h"
#endif
#if COMPONENTSONBOARD
#include "ComponentsOnBoard.h"
#endif
#if CONNECTIVITY
#include "Connectivity.h"
#endif
#if CONSTRUCTIVE
#include "Constructive.h"
#endif
#if DIALOGSETTINGS
#include "DialogSettings.h"
#endif
#if DISPLAYCONTROL
#include "DisplayControl.h"
#endif
#if GROUPS
#include "Groups.h"
#endif
#if HISPEEDRULES
#include "HiSpeedRules.h"
#endif
#if LOCALLIBRARY
#include "LocalLibrary.h"
#endif
#if NETLIST
#include "NetList.h"
#endif
#if RULES
#include "Rules.h"
#endif
#if SETTINGS
#include "Settings.h"
#endif
// clang-format on

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 *
 * NOTE XmlArrayElem<Package> пустые пропускать и не сериализовать.
 */
namespace TopoR {
struct TopoR_PCB_File;
// Корневой тег. Включает все разделы файла.
// [XmlRoot("TopoR_PCB_File")] */
struct TopoR_PCB_File /*: std::true_type*/ {
#if HEADER
    // Раздел «Заголовок файла».
    // [XmlElement("Header")] */
    Header header;
#endif
#if LAYERS
    // Раздел «Слои». (Обязательный раздел)
    // [XmlElement("Layers")] */
    Layers layers;
#endif
#if TEXTSTYLES
    //  Раздел «Стили надписей».
    // [XmlElement("TextStyles")] */
    TextStyles textStyles;
#endif
#if LOCALLIBRARY
    // Раздел «Библиотечные элементы». (Обязательный раздел)
    // [XmlElement("LocalLibrary")] */
    LocalLibrary localLibrary;
#endif
#if CONSTRUCTIVE
    // Раздел «Конструктив платы».
    // [XmlElement("Constructive")] */
    Constructive constructive;
#endif
#if COMPONENTSONBOARD
    // Раздел «Компоненты на плате». (Обязательный раздел).
    // [XmlElement("ComponentsOnBoard")] */
    ComponentsOnBoard componentsOnBoard;
#endif
#if NETLIST
    // Раздел «Текущий список соединений».
    // [XmlElement("NetList")] */
    NetList netList;
#endif
#if GROUPS
    // Раздел «Группировка объектов».
    // [XmlElement("Groups")] */
    Groups groups;
#endif
#if HISPEEDRULES
    // Раздел «Правила для высокоскоростных устройств».
    // [XmlElement("HiSpeedRules")] */
    HiSpeedRules hiSpeedRules;
#endif
#if RULES
    // РАЗДЕЛ «ПРАВИЛА»RULES
    /// \note !Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
    // [XmlElement("Rules")] */
    Rules rules;
#endif
#if CONNECTIVITY
    // РАЗДЕЛ «СОЕДИНЕНИЯ НА ПЛCONNECTIVITYте».
    /// \note В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
    // [XmlElement("Connectivity")] */
    Connectivity connectivity;
#endif
#if SETTINGS
    // Раздел «Настройки дизайна».
    // [XmlElement("Settings")] */
    Settings settings;
#endif
#if DISPLAYCONTROL
    // Раздел «Настройки отображения».
    // [XmlElement("DisplayControl")] */
    DisplayControl displayControl;
#endif
#if DIALOGSETTINGS
    // Раздел «Настройки диалогов».
    // [XmlElement("DialogSettings")] */
    DialogSettings dialogSettings;
#endif
};
} // namespace TopoR
