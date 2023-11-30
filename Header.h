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
    struct Units_Header {
        // Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
        // [XmlAttribute("dist")] public dist _dist;
        Attribute<dist> _dist{};

        // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
        // [XmlAttribute("time")] public time _time;
        Attribute<time> _time{};
    };

    // Название формата файла.
    // [XmlElement("Format")] public string _Format;
    QString _Format;

    // Версия формата.
    // [XmlElement("Version")] public string _Version;
    QString _Version;

    // Название программы, создавшей файл.
    // [XmlElement("Program")] public string _Program;
    QString _Program;

    // Дата и время создания файла (в произвольной форме).
    // [XmlElement("Date")] public string _Date;
    QString _Date;

    // Формат импортированного файла, из которого был получен дизайн.
    // [XmlElement("OriginalFormat")] public string _OriginalFormat;
    QString _OriginalFormat;

    // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    // [XmlElement("OriginalFile")] public string _OriginalFile;
    QString _OriginalFile;

    // Единицы измерения для всего файла.
    // [XmlElement("Units")] public Units_Header _Units;
    Units_Header _Units;
};

} // namespace TopoR_PCB_Classes
