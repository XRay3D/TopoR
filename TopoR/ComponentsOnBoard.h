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
    /// \note !Если компонент расположен на нижней стороне платы, его посадочное место отображается зеркально относительно вертикальной оси посадочного места, описанного в библиотеке(т.е.без угла поворота). Стеки контактных площадок переворачиваются.
    struct CompInstance {
        // Описание контакта компонента на плате.
        /// \note !Если PadstackRef не указан, то стек контактных площадок берётся из посадочного места.
        struct Pin {
            // Номер контакта компонента.
            // [Xml::Attribute("padNum", DataType = "int")] public int padNum_;
            Xml::Attr<int> padNum;
            // Ссылка на стек контактных площадок.
            // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Точка привязки объекта.
            // [Xml::Element("Org")] public Org org;
            Org org;
        };
        // Описание монтажного отверстия в компоненте на плате.
        struct Mnthole {
            // Ссылка на монтажное отверстие в посадочном месте.
            // [Xml::Attribute("mntholeRef")] public string mntholeRef_;
            Xml::Attr<QString> mntholeRef;
            // Задаёт угол в градусах c точностью до тысячных долей.
            // [Xml::Attribute("angle", DataType = "double")] public double angle_;
            Xml::Attr<double> angle;
            // Ссылка на стек контактных площадок.
            // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Cсылка на цепь.
            // [Xml::Element("NetRef")] public NetRef netRef;
            NetRef netRef;
        };
        // Описание атрибута компонента на плате.
        struct Attribute {
            // Описание ярлыка компонента на плате.
            struct Label {
                // Задаёт угол в градусах c точностью до тысячных долей.
                // [Xml::Attribute("angle", DataType = "double")] public double angle_;
                Xml::Attr<double> angle;
                // Параметр надписей и ярлыков: зеркальность отображения.
                // [Xml::Attribute("mirror")] public Bool mirror_;
                Xml::Attr<Bool> mirror;
                // Параметр надписей (ярлыков): способ выравнивания текста.
                // [Xml::Attribute("align")] public align align;
                Xml::Attr<align> align_;
                // Флаг видимости.
                // [Xml::Attribute("visible")] public Bool visible_;
                Xml::Attr<Bool> visible;
                // [Xml::Ignore] public bool visibleSpecified_ */
                bool getVisibleSpecified() const;
                // Ссылка на слой.
                // [Xml::Element("LayerRef")] public LayerRef layerRef;
                LayerRef layerRef;
                // Ссылка на стиль надписей.
                // [Xml::Element("TextStyleRef")] public TextStyleRef textStyleRef;
                TextStyleRef textStyleRef;
                // Точка привязки объекта.
                // [Xml::Element("Org")] public Org org;
                Org org;
                QTransform transform() const {
                    QTransform transform;
                    transform.translate(org.x, org.y);
                    transform.rotate(angle);
                    return transform;
                }
            };
            // Тип предопределённого атрибута компонента.
            // [Xml::Attribute("type")] public type type_;
           Xml::Optional<Xml::Attr<type, NoOpt>> type_;
            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            // Значение атрибута.
            // [Xml::Attribute("value")] public string value_;
           Xml::Optional<Xml::Attr<QString, NoOpt>> value;
            // Ярлыки.
            // [Xml::Element("Label")] public List<Label> Labels;
            Xml::Array<Label> Labels;
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Уникальный идентификатор компонента. Используется при синхронизации. Необязательный атрибут.
        // Если не задан, то будет создан при импорте файла.
        // [Xml::Attribute("uniqueId")] public string uniqueId_;
        Xml::Attr<QString> uniqueId;
        // Сторона объекта.
        /// \note !Значение Both возможно только при описании запретов размещения.
        // [Xml::Attribute("side")] public side side_;
        Xml::Attr<side, NoOpt> side_;
        // Задаёт угол в градусах c точностью до тысячных долей.
        // [Xml::Attribute("angle", DataType = "double")] public double angle_;
        Xml::Attr<double> angle;
        // Признак фиксации.
        // [Xml::Attribute("fixed")] public Bool fixed_;
        Xml::Attr<Bool> fixed;
        // Ссылка на схемный компонент.
        // [Xml::Element("ComponentRef")] public ComponentRef componentRef;
        ComponentRef componentRef;
        // Ссылка на посадочное место.
        // [Xml::Element("FootprintRef")] public FootprintRef footprintRef;
        FootprintRef footprintRef;
        // Точка привязки объекта.
        // [Xml::Element("Org")] public Org org;
        Org org;
        // Контакты компонента на плате.
        // [Xml::Array("Pins")][Xml::ArrayItem("Pin")] public List<Pin> Pins;
        Xml::ArrayElem<Pin> Pins;
        // Монтажные отверстия.
        // [Xml::Array("Mntholes")][Xml::ArrayItem("Mnthole")] public List<Mnthole> Mntholes;
        Xml::ArrayElem<Mnthole> Mntholes;
        // Атрибуты компонента.
        // [Xml::Array("Attributes")][Xml::ArrayItem("Attribute")] public List<Attribute> Attributes;
        Xml::ArrayElem<Attribute> Attributes;
        /************************************************************************
         * Здесь находятся функции для работы с элементами класса CompInstance. *
         * Они не являются частью формата TopoR PCB.                            *
         * **********************************************************************/
        // Для отображения имени компонента
        // <returns></returns>
        operator QString() const { return name; }
        QTransform transform() const;
        /***********************************************************************/
    };
    // Описание одиночного контакта..
    struct FreePad {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Сторона объекта.
        // [Xml::Attribute("side")] public side side_;
        Xml::Attr<side, NoOpt> side_;
        // Задаёт угол в градусах c точностью до тысячных долей.
        // [Xml::Attribute("angle", DataType = "double")] public double angle_;
        Xml::Attr<double> angle;
        // Признак фиксации.
        // [Xml::Attribute("fixed")] public Bool fixed_;
        Xml::Attr<Bool> fixed;

        // [Xml::Ignore] public bool fixedSpecified_ */
        bool getFixedSpecified() const;
        // Ссылка на стек контактных площадок.
        // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
        PadstackRef padstackRef;
        // Cсылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
       Xml::Optional<NetRef> netRef;
        // Точка привязки объекта.
        // [Xml::Element("Org")] public Org org;
        Org org;
        QTransform transform() const {
            QTransform transform;
            transform.translate(org.x, org.y);
            transform.rotate(angle);
            return transform;
        }
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Описание компонентов на плате (инстанции компонентов)
    // [Xml::Array("Components")][Xml::ArrayItem("CompInstance")] public List<CompInstance> Components;
    Xml::ArrayElem<CompInstance> Components;
    // Описание одиночных контактов.(инстанции компонентов)
    // [Xml::Array("FreePads")][Xml::ArrayItem("FreePad")] public List<FreePad> FreePads;
    Xml::ArrayElem<FreePad> FreePads;

    /*****************************************************************************
     * Здесь находятся функции для работы с элементами класса ComponentsOnBoard. *
     * Они не являются частью формата TopoR PCB.                                 *
     * ***************************************************************************/
    // Добавление компонента
    /// \param name \brief Имя нового компонента. Если имя неуникально, будет добавлен префикс _
    /// \param units \brief текущие единицы измерения
    /// \param componentRef \brief ссылка на библиотеку компонентов
    /// \param footprintRef \brief ссылка на библиотеку посадочных мест
    /// \return  Имя нового компонента
    QString AddComponent(QString name, units units, const QString& componentRef, const QString& footprintRef);
    // Удаление компонента по имени
    /// \param name \brief уникальный имя компонента
    /// \return  true - если было произведено удаление, иначе (компонент не найден) - false
    bool RemoveComponent(const QString& name);
    // Индекс компонента
    /// \param name \brief уникальное имя компонента
    /// \return  индекс компонента или -1, если компонент отсутствует
    int ComponentIndexOf(const QString& name);
    // Переименование компонента
    /// \param oldname \brief старое имя компонента
    /// \param newname \brief новое имя компонента
    /// \return  индекс компонента, если было произведено переименование, -1, если компонент не найден
    int RenameComponent(const QString& oldname, const QString& newname);
    // Генерация уникального идентификатора
    /// \return  string like "ABCDEFGH"
    QString UniqueId();
    /*************************************************************************************/
};
} // namespace TopoR
