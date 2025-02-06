#pragma once
#include "Commons.h"
#include <memory>
#include <string>
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Заголовок файла».
struct Header {
    // Единицы измерений для всего файла.
    struct Units {
        // Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
        // [Xml::Attribute("dist")] public dist dist_;
        Xml::Attr<dist, NoOpt> dist_;
        // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
        // [Xml::Attribute("time")] public time time_;
        Xml::Attr<time, NoOpt> time_;
    };
    // Название формата файла.
    // [Xml::Element("Format")] public string Format_;
    QString Format;
    // Версия формата.
    // [Xml::Element("Version")] public string Version_;
    QString Version;
    // Название программы, создавшей файл.
    // [Xml::Element("Program")] public string Program_;
    QString Program;
    // Дата и время создания файла (в произвольной форме).
    // [Xml::Element("Date")] public string Date_;
    QString Date;
    // Формат импортированного файла, из которого был получен дизайн.
    // [Xml::Element("OriginalFormat")] public string OriginalFormat_;
    QString OriginalFormat;
    // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    // [Xml::Element("OriginalFile")] public string OriginalFile_;
    QString OriginalFile;
    // Единицы измерения для всего файла.
    // [Xml::Element("Units")] public unitsHeader units;
    Units units;
};
} // namespace TopoR
