#pragma once

#include "Commons.h"

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR {

struct Header {                       // Раздел «Заголовок файла».
    QString Format;                   // Название формата файла. Xml::Element
    QString Version;                  // Версия формата. Xml::Element
    QString Program;                  // Название программы, создавшей файл. Xml::Element
    QString Date;                     // Дата и время создания файла (в произвольной форме). Xml::Element
    QString OriginalFormat;           // Формат импортированного файла, из которого был получен дизайн. Xml::Element
    QString OriginalFile;             // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта. Xml::Element
    struct Units {                    // Единицы измерения для всего файла. Xml::Element
        Xml::Attr<dist, NoOpt> dist_; // Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
        Xml::Attr<time, NoOpt> time_; // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
    } units;
};

} // namespace TopoR
