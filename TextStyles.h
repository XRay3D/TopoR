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

namespace TopoR_PCB_Classes {

// Раздел «Стили надписей».

class TextStyles {

    // Описание стиля надписей.

public:
    class TextStyle {

        // Имя объекта или ссылка на именованный объект.

    public:
        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Параметр стиля надписей: название шрифта.

        //[XmlAttribute("fontName")] public string _fontName;
        std::string _fontName;

        // Параметр стиля надписей: высота символов в текущих единицах.

        //[XmlAttribute("height", DataType = "float")] public float _height;
        float _height = 0.0F;

        // Параметр стиля надписей: жирность шрифта.

        //[XmlAttribute("bold")] public Bool _bold;
        Bool _bold{};

        //[XmlIgnore] public bool _boldSpecified
        bool getBoldSpecified() const;

        // Параметр стиля надписей: курсив.

        //[XmlAttribute("italic")] public Bool _italic;
        Bool _italic{};

        //[XmlIgnore] public bool _italicSpecified
        bool getItalicSpecified() const;
    };

    // Версия раздела.

public:
    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Стили надписей.

    //[XmlElement("TextStyle")] public List<TextStyle> _TextStyles;
    std::vector<std::optional<TextStyle>> _TextStyles;
    bool ShouldSerialize_TextStyles();

    /**********************************************************************
     * Здесь находятся функции для работы с элементами класса TextStyles. *
     * Они не являются частью формата TopoR PCB.                          *
     * ********************************************************************/

    /**********************************************************************/
};
} // namespace TopoR_PCB_Classes
