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
        /* [XmlAttribute("dist")] public dist dist_; */
        XmlAttr<dist> dist_;
        // Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
        /* [XmlAttribute("time")] public time time_; */
        XmlAttr<time> time_;
    };
    // Название формата файла.
    /* [XmlElement("Format")] public string Format_; */
    QString Format;
    // Версия формата.
    /* [XmlElement("Version")] public string Version_; */
    QString Version;
    // Название программы, создавшей файл.
    /* [XmlElement("Program")] public string Program_; */
    QString Program;
    // Дата и время создания файла (в произвольной форме).
    /* [XmlElement("Date")] public string Date_; */
    QString Date;
    // Формат импортированного файла, из которого был получен дизайн.
    /* [XmlElement("OriginalFormat")] public string OriginalFormat_; */
    QString OriginalFormat;
    // Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    /* [XmlElement("OriginalFile")] public string OriginalFile_; */
    QString OriginalFile;
    // Единицы измерения для всего файла.
    /* [XmlElement("Units")] public unitsHeader units; */
    Units units;
};
} // namespace TopoR_PCB_Classes
