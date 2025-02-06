#pragma once
#include "Commons.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Стили надписей».
struct TextStyles {
    // Описание стиля надписей.
    struct TextStyle {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Параметр стиля надписей: название шрифта.
        // [Xml::Attribute("fontName")] public string fontName_;
        Xml::Attr<QString> fontName;
        // Параметр стиля надписей: высота символов в текущих единицах.
        // [Xml::Attribute("height", DataType = "double")] public double height_;
        Xml::Attr<double> height;
        // Параметр стиля надписей: жирность шрифта.
        // [Xml::Attribute("bold")] public Bool bold_;
        Xml::Attr<Bool> bold;
        /* public bool boldSpecified_ */
        // Параметр стиля надписей: курсив.
        // [Xml::Attribute("italic")] public Bool italic_;
        Xml::Attr<Bool> italic;
        /* public bool italicSpecified_ */
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Стили надписей.
    // [Xml::Element("TextStyle")] public List<TextStyle> TextStyles_;
    Xml::Array<TextStyle> TextStyles;
    /**********************************************************************
     * Здесь находятся функции для работы с элементами класса TextStyles. *
     * Они не являются частью формата TopoR PCB.                          *
     * ********************************************************************/

    const TextStyle* getTextStyle(const QString& name) const;
    /**********************************************************************/
};
} // namespace TopoR
