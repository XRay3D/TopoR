﻿#pragma once

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
class Header {

public:
    // Единицы измерений для всего файла.
    class Units_Header {
    public:
        // Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
        // [XmlAttribute("dist")] public dist _dist;
        dist _dist{};

        // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
        // [XmlAttribute("time")] public time _time;
        time _time{};
    };

public:
    // Название формата файла.
    // [XmlElement("Format")] public string _Format;
    std::string _Format;

    // Версия формата.
    // [XmlElement("Version")] public string _Version;
    std::string _Version;

    // Название программы, создавшей файл.
    // [XmlElement("Program")] public string _Program;
    std::string _Program;

    // Дата и время создания файла (в произвольной форме).
    // [XmlElement("Date")] public string _Date;
    std::string _Date;

    // Формат импортированного файла, из которого был получен дизайн.
    // [XmlElement("OriginalFormat")] public string _OriginalFormat;
    std::string _OriginalFormat;

    // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    // [XmlElement("OriginalFile")] public string _OriginalFile;
    std::string _OriginalFile;

    // Единицы измерения для всего файла.
    // [XmlElement("Units")] public Units_Header _Units;
    std::optional<Units_Header> _Units;
};
} // namespace TopoR_PCB_Classes
