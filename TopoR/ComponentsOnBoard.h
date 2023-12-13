#pragma once
#include "Commons.h"
#include <string>
#include <vector>
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Комоненты на плате (обязательный раздел).
struct ComponentsOnBoard {
    // Описание компонента на плате.
    // <rearks>! Если компонент расположен на нижней стороне платы, его посадочное место отображается зеркально относительно вертикальной оси посадочного места, описанного в библиотеке(т.е.без угла поворота). Стеки контактных площадок переворачиваются.</remarks>
    struct CompInstance {
        // Описание контакта компонента на плате.
        // <remarks>! Если PadstackRef не указан, то стек контактных площадок берётся из посадочного места.</remarks>
        struct Pin {
            // Номер контакта компонента.
            /* [XmlAttribute("padNum", DataType = "int")] public int padNum_; */
            XmlAttr<int> padNum;
            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
            PadstackRef padstackRef;
            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org org; */
            Org org;
        };
        // Описание монтажного отверстия в компоненте на плате.
        struct Mnthole {
            // Ссылка на монтажное отверстие в посадочном месте.
            /* [XmlAttribute("mntholeRef")] public string mntholeRef_; */
            XmlAttr<QString> mntholeRef;
            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
            XmlAttr<float> angle;
            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
            PadstackRef padstackRef;
            // Cсылка на цепь.
            /* [XmlElement("NetRef")] public NetRef netRef; */
            NetRef netRef;
        };
        // Описание атрибута компонента на плате.
        struct Attribute {
            // Описание ярлыка компонента на плате.
            struct Label {
                // Задаёт угол в градусах c точностью до тысячных долей.
                /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
                XmlAttr<float> angle;
                // Параметр надписей и ярлыков: зеркальность отображения.
                /* [XmlAttribute("mirror")] public Bool mirror_; */
                XmlAttr<Bool> mirror;
                // Параметр надписей (ярлыков): способ выравнивания текста.
                /* [XmlAttribute("align")] public align align_; */
                XmlAttr<align> align_;
                // Флаг видимости.
                /* [XmlAttribute("visible")] public Bool visible_; */
                XmlAttr<Bool> visible;
                /* [XmlIgnore] public bool visibleSpecified_ */
                bool getVisibleSpecified() const;
                // Ссылка на слой.
                /* [XmlElement("LayerRef")] public LayerRef layerRef; */
                LayerRef layerRef;
                // Ссылка на стиль надписей.
                /* [XmlElement("TextStyleRef")] public TextStyleRef textStyleRef; */
                TextStyleRef textStyleRef;
                // Точка привязки объекта.
                /* [XmlElement("Org")] public Org org; */
                Org org;
                QTransform transform() const {
                    QTransform transform;
                    transform.translate(org.x, org.y);
                    transform.rotate(angle);
                    return transform;
                }
            };
            // Тип предопределённого атрибута компонента.
            /* [XmlAttribute("type")] public type type_; */
            XmlAttr<type> type_;
            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;
            // Значение атрибута.
            /* [XmlAttribute("value")] public string value_; */
            XmlAttr<QString> value;
            // Ярлыки.
            /* [XmlElement("Label")] public List<Label> Labels; */
            XmlArray<Label> Labels;
        };
        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;
        // Уникальный идентификатор компонента. Используется при синхронизации. Необязательный атрибут.
        // Если не задан, то будет создан при импорте файла.
        /* [XmlAttribute("uniqueId")] public string uniqueId_; */
        XmlAttr<QString> uniqueId;
        // Сторона объекта.
        // <remarks>!Значение Both возможно только при описании запретов размещения.</remarks>
        /* [XmlAttribute("side")] public side side_; */
        XmlAttr<side> side_;
        // Задаёт угол в градусах c точностью до тысячных долей.
        /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
        XmlAttr<float> angle;
        // Признак фиксации.
        /* [XmlAttribute("fixed")] public Bool fixed_; */
        XmlAttr<Bool> fixed;
        // Ссылка на схемный компонент.
        /* [XmlElement("ComponentRef")] public ComponentRef componentRef; */
        ComponentRef componentRef;
        // Ссылка на посадочное место.
        /* [XmlElement("FootprintRef")] public FootprintRef footprintRef; */
        FootprintRef footprintRef;
        // Точка привязки объекта.
        /* [XmlElement("Org")] public Org org; */
        Org org;
        // Контакты компонента на плате.
        /* [XmlArray("Pins")][XmlArrayItem("Pin")] public List<Pin> Pins; */
        XmlArray<Pin> Pins;
        // Монтажные отверстия.
        /* [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<Mnthole> Mntholes; */
        XmlArray<Mnthole> Mntholes;
        // Атрибуты компонента.
        /* [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<Attribute> Attributes; */
        XmlArrayElem<Attribute> Attributes;
        /************************************************************************
         * Здесь находятся функции для работы с элементами класса CompInstance. *
         * Они не являются частью формата TopoR PCB.                            *
         * **********************************************************************/
        // Для отображения имени компонента
        // <returns></returns>
        QString ToString();
        QTransform transform() const {
            QTransform transform;
            transform.translate(org.x, org.y);
            transform.rotate(angle);
            return transform;
        }
        /***********************************************************************/
    };
    // Описание одиночного контакта..
    struct FreePad {
        // Сторона объекта.
        /* [XmlAttribute("side")] public side side_; */
        XmlAttr<side> side_;
        // Задаёт угол в градусах c точностью до тысячных долей.
        /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
        XmlAttr<float> angle;
        // Признак фиксации.
        /* [XmlAttribute("fixed")] public Bool fixed_; */
        XmlAttr<Bool> fixed;

        /* [XmlIgnore] public bool fixedSpecified_ */
        bool getFixedSpecified() const;
        // Ссылка на стек контактных площадок.
        /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
        PadstackRef padstackRef;
        // Cсылка на цепь.
        /* [XmlElement("NetRef")] public NetRef netRef; */
        NetRef netRef;
        // Точка привязки объекта.
        /* [XmlElement("Org")] public Org org; */
        Org org;
        QTransform transform() const {
            QTransform transform;
            transform.translate(org.x, org.y);
            transform.rotate(angle);
            return transform;
        }
    };
    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;
    // Описание компонентов на плате (инстанции компонентов)
    /* [XmlArray("Components")][XmlArrayItem("CompInstance")] public List<CompInstance> Components; */
    XmlArrayElem<CompInstance> Components;
    // Описание одиночных контактов.(инстанции компонентов)
    /* [XmlArray("FreePads")][XmlArrayItem("FreePad")] public List<FreePad> FreePads; */
    XmlArrayElem<FreePad> FreePads;
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
    QString AddComponent(QString name, units units, const QString& componentRef, const QString& footprintRef);
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
} // namespace TopoR
