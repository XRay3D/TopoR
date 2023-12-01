﻿#pragma once

#include "Commons.h"
#include <cmath>
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

// Компоненты на плате (обязательный раздел).

struct ComponentsOnBoard {

    // Описание компонента на плате.

    // <remarks>! Если компонент расположен на нижней стороне платы, его посадочное место отображается зеркально относительно вертикальной оси посадочного места, описанного в библиотеке(т.е.без угла поворота). Стеки контактных площадок переворачиваются.</remarks>

    struct CompInstance {

        // Описание контакта компонента на плате.

        // <remarks>! Если PadstackRef не указан, то стек контактных площадок берётся из посадочного места.</remarks>

        struct CompInstance_Pin {

            // Номер контакта компонента.

            /* [XmlAttribute("padNum", DataType = "int")] public int _padNum; */
            XmlAttr<int>padNum;
            int _padNum = 0;

            // Ссылка на стек контактных площадок.

            /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
            PadstackRef _PadstackRef;
            bool ShouldSerialize_PadstackRef();

            // Точка привязки объекта.

            /* [XmlElement("Org")] public Org _Org; */
            Org _Org;
        };

        // Описание монтажного отверстия в компоненте на плате.

        struct CompInstance_Mnthole {

            // Ссылка на монтажное отверстие в посадочном месте.

            /* [XmlAttribute("mntholeRef")] public string _mntholeRef; */
            QString _mntholeRef;

            // Задаёт угол в градусах c точностью до тысячных долей.

            /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
            XmlAttr<float>angle;
            float _angle = 0.0F;

            // Ссылка на стек контактных площадок.

            /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
            PadstackRef _PadstackRef;

            // Cсылка на цепь.

            /* [XmlElement("NetRef")] public NetRef _NetRef; */
            NetRef _NetRef;
        };

        // Описание атрибута компонента на плате.

        struct CompInstance_Attribute {

            // Описание ярлыка компонента на плате.

            struct CompInstance_Attribute_Label {

                // Задаёт угол в градусах c точностью до тысячных долей.

                /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
                XmlAttr<float>angle;
                float _angle = 0.0F;

                // Параметр надписей и ярлыков: зеркальность отображения.

                /* [XmlAttribute("mirror")] public Bool _mirror; */
                Bool _mirror{};

                /* public bool _mirrorSpecified */
                bool getMirrorSpecified() const;

                // Параметр надписей (ярлыков): способ выравнивания текста.

                /* [XmlAttribute("align")] public align _align; */
                align _align{};

                // Флаг видимости.

                /* [XmlAttribute("visible")] public Bool _visible; */
                Bool _visible{};

                /* public bool _visibleSpecified */
                bool getVisibleSpecified() const;

                // Ссылка на слой.

                /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
                LayerRef _LayerRef;

                // Ссылка на стиль надписей.

                /* [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef; */
                TextStyleRef _TextStyleRef;

                // Точка привязки объекта.

                /* [XmlElement("Org")] public Org _Org; */
                Org _Org;
            };

            // Тип предопределённого атрибута компонента.

            /* [XmlAttribute("type")] public type _type; */
            type _type{};

            // Имя объекта или ссылка на именованный объект.

            /* [XmlAttribute("name")] public string _name; */
            QString _name;

            // Значение атрибута.

            /* [XmlAttribute("value")] public string _value; */
            QString _value;

            // Ярлыки.

            /* [XmlElement("Label")] public List<CompInstance_Attribute_Label> _Labels; */
            std::vector<CompInstance_Attribute_Label> _Labels;
            bool ShouldSerialize_Labels();
        };

        // Имя объекта или ссылка на именованный объект.

        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Уникальный идентификатор компонента. Используется при синхронизации. Необязательный атрибут.
        // Если не задан, то будет создан при импорте файла.

        /* [XmlAttribute("uniqueId")] public string _uniqueId; */
        QString _uniqueId;

        // Сторона объекта.

        // <remarks>!Значение Both возможно только при описании запретов размещения.</remarks>

        /* [XmlAttribute("side")] public side _side; */
        side _side{};

        // Задаёт угол в градусах c точностью до тысячных долей.

        /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
        XmlAttr<float>angle;
        float _angle = 0.0F;

        // Признак фиксации.

        /* [XmlAttribute("fixed")] public Bool _fixed; */
        Bool _fixed{};

        /* public bool _fixedSpecified */
        bool getFixedSpecified() const;

        // Ссылка на схемный компонент.

        /* [XmlElement("ComponentRef")] public ComponentRef _ComponentRef; */
        ComponentRef _ComponentRef;

        // Ссылка на посадочное место.

        /* [XmlElement("FootprintRef")] public FootprintRef _FootprintRef; */
        FootprintRef _FootprintRef;

        // Точка привязки объекта.

        /* [XmlElement("Org")] public Org _Org; */
        Org _Org;

        // Контакты компонента на плате.

        /* [XmlArray("Pins")][XmlArrayItem("Pin")] public List<CompInstance_Pin> _Pins; */
        std::vector<CompInstance_Pin> _Pins;
        bool ShouldSerialize_Pins();

        // Монтажные отверстия.

        /* [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<CompInstance_Mnthole> _Mntholes; */
        std::vector<CompInstance_Mnthole> _Mntholes;
        bool ShouldSerialize_Mntholes();

        // Атрибуты компонента.

        /* [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<CompInstance_Attribute> _Attributes; */
        std::vector<CompInstance_Attribute> _Attributes;
        bool ShouldSerialize_Attributes();

        /************************************************************************
         * Здесь находятся функции для работы с элементами класса CompInstance. *
         * Они не являются частью формата TopoR PCB.                            *
         * **********************************************************************/

        // Для отображения имени компонента

        // <returns></returns>
        QString ToString();
        /***********************************************************************/
    };

    // Описание одиночного контакта..

    struct FreePad {

        // Сторона объекта.

        /* [XmlAttribute("side")] public side _side; */
        side _side{};

        // Задаёт угол в градусах c точностью до тысячных долей.

        /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
        XmlAttr<float>angle;
        float _angle = 0.0F;

        // Признак фиксации.

        /* [XmlAttribute("fixed")] public Bool _fixed; */
        Bool _fixed{};

        /* public bool _fixedSpecified */
        bool getFixedSpecified() const;

        // Ссылка на стек контактных площадок.

        /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
        PadstackRef _PadstackRef;

        // Cсылка на цепь.

        /* [XmlElement("NetRef")] public NetRef _NetRef; */
        NetRef _NetRef;

        // Точка привязки объекта.

        /* [XmlElement("Org")] public Org _Org; */
        Org _Org;
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string _version; */
    QString _version;

    // Описание компонентов на плате (инстанции компонентов)

    /* [XmlArray("Components")][XmlArrayItem("CompInstance")] public List<CompInstance> _Components; */
    std::vector<CompInstance> _Components;
    bool ShouldSerialize_Components();

    // Описание одиночных контактов.(инстанции компонентов)

    /* [XmlArray("FreePads")][XmlArrayItem("FreePad")] public List<FreePad> _FreePads; */
    std::vector<FreePad> _FreePads;
    bool ShouldSerialize_FreePads();

    /*****************************************************************************
     * Здесь находятся функции для работы с элементами класса ComponentsOnBoard. *
     * Они не являются частью формата TopoR PCB.                                 *
     * ***************************************************************************/

    // Добавление компонента

    // <param name="name">Имя нового компонента. Если имя неуникально, будет добавлен префикс _</param>
    // <param name="units">текущие единицы измерения</param>
    // <param name="componentRef">ссылка на библиотеку компонентов</param>
    // <param name="footprintRef">ссылка на библиотеку посадочных мест</param>
    // <returns>Имя нового компонента</returns>
    QString AddComponent(const QString& name, units units, const QString& componentRef, const QString& footprintRef);

    // Удаление компонента по имени

    // <param name="name">уникальный имя компонента</param>
    // <returns>true - если было произведено удаление, иначе (компонент не найден) - false</returns>
    bool RemoveComponent(const QString& name);

    // Индекс компонента

    // <param name="name">уникальное имя компонента</param>
    // <returns>индекс компонента или -1, если компонент отсутствует</returns>
    int ComponentIndexOf(const QString& name);

    // Переименование компонента

    // <param name="oldname">старое имя компонента</param>
    // <param name="newname">новое имя компонента</param>
    // <returns>индекс компонента, если было произведено переименование, -1, если компонент не найден</returns>
    int RenameComponent(const QString& oldname, const QString& newname);

    // Генерация уникального идентификатора

    // <returns>string like "ABCDEFGH"</returns>
    QString UniqueId();

    /*************************************************************************************/
};

} // namespace TopoR_PCB_Classes
