#pragma once

#include "Commons.h"
#include <string>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

// namespace TopoR_PCB_Classes {

/// <summary>
/// Единицы измерений для всего файла.
/// </summary>
class Units_Header : public QSerializer {
    Q_GADGET
    QS_META_OBJECT_METHOD
    /// <summary>
    /// Единицы измерения длины для всего файла. Значение по умолчанию – mm (миллиметр).
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("dist")] public dist _dist;
    //    QS_ATTR(dist_, dist) // = static_cast<dist>(0);

    /// <summary>
    /// Единицы измерения времени для всего файла. Значение по умолчанию – ps (пикосекунда).
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("time")] public time _time;
    //    QS_ATTR(time_, time) // = static_cast<enum time>(0);
};

/// <summary>
/// Раздел «Заголовок файла».
/// </summary>
class Header_ : public QSerializer {
    Q_GADGET
    QS_META_OBJECT_METHOD
    /// <summary>
    /// Название формата файла.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Format")] public string _Format;
    QS_FIELD(QString, Format)

    /// <summary>
    /// Версия формата.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Version")] public string _Version;
    QS_FIELD(QString, Version)

    /// <summary>
    /// Название программы, создавшей файл.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Program")] public string _Program;
    QS_FIELD(QString, Program)

    /// <summary>
    /// Дата и время создания файла (в произвольной форме).
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Date")] public string _Date;
    QS_FIELD(QString, Date)

    /// <summary>
    /// Формат импортированного файла, из которого был получен дизайн.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("OriginalFormat")] public string _OriginalFormat;
    QS_FIELD(QString, OriginalFormat)

    /// <summary>
    /// Импортированный файл. Путь к файлу задаётся относительно каталога содержащего файл проекта.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("OriginalFile")] public string _OriginalFile;
    QS_FIELD(QString, OriginalFile)

    /// <summary>
    /// Единицы измерения для всего файла.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlElement("Units")] public Units_Header _Units;
    QS_OBJECT(Units_Header, Units)
    //    virtual ~Header()
    //    {
    //        // delete _Units;
    //    }
};
// } // namespace TopoR_PCB_Classes
