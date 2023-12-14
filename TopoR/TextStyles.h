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
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;
        // Параметр стиля надписей: название шрифта.
        /* [XmlAttribute("fontName")] public string fontName_; */
        XmlAttr<QString> fontName;
        // Параметр стиля надписей: высота символов в текущих единицах.
        /* [XmlAttribute("height", DataType = "float")] public float height_; */
        XmlAttr<float> height;
        // Параметр стиля надписей: жирность шрифта.
        /* [XmlAttribute("bold")] public Bool bold_; */
        XmlAttr<Bool> bold{};
        /* public bool boldSpecified_ */
        // Параметр стиля надписей: курсив.
        /* [XmlAttribute("italic")] public Bool italic_; */
        XmlAttr<Bool> italic{};
        /* public bool italicSpecified_ */
    };
    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;
    // Стили надписей.
    /* [XmlElement("TextStyle")] public List<TextStyle> TextStyles_; */
    XmlArray<TextStyle> TextStyles;
    /**********************************************************************
     * Здесь находятся функции для работы с элементами класса TextStyles. *
     * Они не являются частью формата TopoR PCB.                          *
     * ********************************************************************/

    const TextStyle* getTextStyle(const QString& name) const;
    /**********************************************************************/
};
} // namespace TopoR
