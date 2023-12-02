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

struct TopoR_PCB_File;

// Корневой тег. Включает все разделы файла.
/* [XmlRoot("TopoR_PCB_File")] public struct  TopoR_PCB_File */
struct TopoR_PCB_File /*: std::true_type*/ {

    // Раздел «Заголовок файла».
    /* [XmlElement("Header")] public Header Header_; */
    // Header Header_;

    // Раздел «Слои». (Обязательный раздел)
    /* [XmlElement("Layers")] public Layers Layers_; */
    // Layers Layers_;

    //  Раздел «Стили надписей».
    /* [XmlElement("TextStyles")] public TextStyles TextStyles_; */
    // TextStyles TextStyles_;

    // Раздел «Библиотечные элементы». (Обязательный раздел)
    /* [XmlElement("LocalLibrary")] public LocalLibrary LocalLibrary_; */
    LocalLibrary LocalLibrary_;

    // Раздел «Конструктив платы».
    /* [XmlElement("Constructive")] public Constructive Constructive_; */
    // Constructive Constructive_;

    // Раздел «Компоненты на плате». (Обязательный раздел).
    /* [XmlElement("ComponentsOnBoard")] public ComponentsOnBoard ComponentsOnBoard_; */
    // ComponentsOnBoard ComponentsOnBoard_;

    // Раздел «Текущий список соединений».
    /* [XmlElement("NetList")] public NetList NetList_; */
    // NetList NetList_;

    // Раздел «Группировка объектов».
    /* [XmlElement("Groups")] public Groups Groups_; */
    // Groups Groups_;

    // Раздел «Правила для высокоскоростных устройств».
    /* [XmlElement("HiSpeedRules")] public HiSpeedRules HiSpeedRules_; */
    // HiSpeedRules HiSpeedRules_;

    // Раздел «Правила».
    // <remarks>! Порядок следования правил в каждой секции определяет приоритет правил. Чем выше приоритет у правила, тем ниже оно описано.</remarks>
    /* [XmlElement("Rules")] public Rules Rules_; */
    // Rules Rules_;

    // Раздел «Соединения на плате».
    // <remarks>В этом разделе описывается конкретная реализация соединений: печатные проводники, межслойные переходы и области металлизации.</remarks>
    /* [XmlElement("Connectivity")] public Connectivity Connectivity_; */
    // Connectivity Connectivity_;

    // Раздел «Настройки дизайна».
    /* [XmlElement("Settings")] public Settings Settings_; */
    // Settings Settings_;

    // Раздел «Настройки отображения».
    /* [XmlElement("DisplayControl")] public DisplayControl DisplayControl_; */
    // DisplayControl DisplayControl_;

    // Раздел «Настройки диалогов».
    /* [XmlElement("DialogSettings")] public DialogSettings DialogSettings_; */
    // DialogSettings DialogSettings_;
};

} // namespace TopoR_PCB_Classes
