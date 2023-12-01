﻿#pragma once

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

namespace TopoR_PCB_Classes {

// Раздел «Стили надписей».

struct TextStyles {
    // Описание стиля надписей.
    struct TextStyle {
        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        XmlAttr<QString> name;

        // Параметр стиля надписей: название шрифта.
        /* [XmlAttribute("fontName")] public string _fontName; */
        XmlAttr<QString> fontName;

        // Параметр стиля надписей: высота символов в текущих единицах.
        /* [XmlAttribute("height", DataType = "float")] public float _height; */
        XmlAttr<float> height; //        float _height = 0.0F;

        // Параметр стиля надписей: жирность шрифта.
        /* [XmlAttribute("bold")] public Bool _bold; */
        XmlAttr<Bool> bold{};

        /* public bool _boldSpecified */
        bool getBoldSpecified() const;

        // Параметр стиля надписей: курсив.
        /* [XmlAttribute("italic")] public Bool _italic; */
        XmlAttr<Bool> italic{};

        /* public bool _italicSpecified */
        bool getItalicSpecified() const;
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string _version; */
    XmlAttr<QString> version;

    // Стили надписей.
    /* [XmlElement("TextStyle")] public List<TextStyle> _TextStyles; */
    std::vector<TextStyle> TextStyles;
    bool ShouldSerialize_TextStyles();

    /**********************************************************************
     * Здесь находятся функции для работы с элементами класса TextStyles. *
     * Они не являются частью формата TopoR PCB.                          *
     * ********************************************************************/

    /**********************************************************************/
};

} // namespace TopoR_PCB_Classes
