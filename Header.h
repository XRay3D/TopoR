#pragma once

#include "Commons.h"
#include <memory>
#include <string>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Заголовок файла».
struct Header {

    // Единицы измерений для всего файла.
    struct Units {
        // Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
        /* [XmlAttribute("dist")] public dist _dist; */
        Attribute<dist> dist{};

        // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
        /* [XmlAttribute("time")] public time _time; */
        Attribute<time> time{};
    };

    // Название формата файла.
    /* [XmlElement("Format")] public string _Format; */
    QString Format;

    // Версия формата.
    /* [XmlElement("Version")] public string _Version; */
    QString Version;

    // Название программы, создавшей файл.
    /* [XmlElement("Program")] public string _Program; */
    QString Program;

    // Дата и время создания файла (в произвольной форме).
    /* [XmlElement("Date")] public string _Date; */
    QString Date;

    // Формат импортированного файла, из которого был получен дизайн.
    /* [XmlElement("OriginalFormat")] public string _OriginalFormat; */
    QString OriginalFormat;

    // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    /* [XmlElement("OriginalFile")] public string _OriginalFile; */
    QString OriginalFile;

    // Единицы измерения для всего файла.
    /* [XmlElement("Units")] public Units_Header _Units; */
    Units _Units;
};

} // namespace TopoR_PCB_Classes
