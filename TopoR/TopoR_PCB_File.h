#pragma once

// clang-format off
#include "Header.h"
#include "Layers.h"
#include "TextStyles.h"
#if 1
#include "ComponentsOnBoard.h"
#include "Connectivity.h"
#include "Constructive.h"
#include "DialogSettings.h"
#include "DisplayControl.h"
#include "Groups.h"
#include "HiSpeedRules.h"
#include "LocalLibrary.h"
#include "NetList.h"
#include "Rules.h"
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
#if 1
    // Раздел «Заголовок файла».
    // [XmlElement("Header")] */
    Header header;
    // Раздел «Слои». (Обязательный раздел)
    // [XmlElement("Layers")] */
    Layers layers;
    //  Раздел «Стили надписей».
    // [XmlElement("TextStyles")] */
    TextStyles textStyles;
    // Раздел «Библиотечные элементы». (Обязательный раздел)
    // [XmlElement("LocalLibrary")] */
#endif
    LocalLibrary localLibrary;
    // Раздел «Конструктив платы».
    // [XmlElement("Constructive")] */
#if 1
    Constructive constructive;
    // Раздел «Компоненты на плате». (Обязательный раздел).
    // [XmlElement("ComponentsOnBoard")] */
    ComponentsOnBoard componentsOnBoard;
    // Раздел «Текущий список соединений».
    // [XmlElement("NetList")] */
    NetList netList;
    // Раздел «Группировка объектов».
    // [XmlElement("Groups")] */
    Groups groups;
    // Раздел «Правила для высокоскоростных устройств».
    // [XmlElement("HiSpeedRules")] */
    HiSpeedRules hiSpeedRules;
    // Раздел «Правила».
    /// \note !Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
    // [XmlElement("Rules")] */
    Rules rules;
    // Раздел «Соединения на плате».
    /// \note В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
    // [XmlElement("Connectivity")] */
    Connectivity connectivity;
    // Раздел «Настройки дизайна».
    // [XmlElement("Settings")] */
    Settings settings;
    // Раздел «Настройки отображения».
    // [XmlElement("DisplayControl")] */
    DisplayControl displayControl;
    // Раздел «Настройки диалогов».
    // [XmlElement("DialogSettings")] */
    DialogSettings dialogSettings;
#endif
};
} // namespace TopoR
