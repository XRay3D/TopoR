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
namespace TopoR {
// Корневой тег. Включает все разделы файла.
struct[[= XML::Root("TopoR_PCB_File")]] TopoR_PCB_File {
    /*
    // Раздел «Заголовок файла».
    [[= XML::Elem("Header")]] Header header;
    // Раздел «Слои». (Обязательный раздел)
    [[= XML::Elem("Layers")]] Layers layers;
    // Раздел «Стили надписей».
    [[= XML::Elem("TextStyles")]] TextStyles textStyles;
    // Раздел «Библиотечные элементы». (Обязательный раздел)
    [[= XML::Elem("LocalLibrary")]] LocalLibrary localLibrary;
    // Раздел «Конструктив платы».
    [[= XML::Elem("Constructive")]] Constructive constructive;
    // Раздел «Компоненты на плате». (Обязательный раздел).
    [[= XML::Elem("ComponentsOnBoard")]] ComponentsOnBoard componentsOnBoard;
    // Раздел «Текущий список соединений».
    [[= XML::Elem("NetList")]] NetList netList;
    // Раздел «Группировка объектов».
    [[= XML::Elem("Groups")]] Groups groups;
    // Раздел «Правила для высокоскоростных устройств».
    [[= XML::Elem("HiSpeedRules")]] HiSpeedRules hiSpeedRules;
    // Раздел «Правила».
    // ! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.
    [[= XML::Elem("Rules")]] Rules rules;
    // Раздел «Соединения на плате».
    // В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.
    */
    [[= XML::Elem("Connectivity")]] Connectivity connectivity;
    // Раздел «Настройки дизайна».
    /*
    [[= XML::Elem("Settings")]] Settings settings;
    // Раздел «Настройки отображения».
    [[= XML::Elem("DisplayControl")]] DisplayControl displayControl;
    // Раздел «Настройки диалогов».
    [[= XML::Elem("DialogSettings")]] DialogSettings dialogSettings;
    */
};
} // namespace TopoR
