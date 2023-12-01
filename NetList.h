#pragma once

#include "Commons.h"

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Текущий список соединений».
struct NetList {

    // Раздел «Текущий список соединени
    struct Net {

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Ссылка на контакт или вывод посадочного места (объект класса PinRef или PadRef).
        /* [XmlElement("PinRef", typeof(PinRef)),
XmlElement("PadRef", typeof(PadRef))] public List<Object> _refs; */
        std::vector<std::variant<PinRef, PadRef>> _refs;
        bool ShouldSerialize_refs();
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string _version; */
    QString _version;

    // Описания цепей.
    /* [XmlElement("Net")] public List<Net> _Nets; */
    std::vector<Net> _Nets;
    bool ShouldSerialize_Nets();

    /*******************************************************************
     * Здесь находятся функции для работы с элементами класса NetList. *
     * Они не являются частью формата TopoR PCB.                       *
     * *****************************************************************/

    // Переименование ссылок на компонент, если его имя изменилось

    // <param name="oldname">старое имя компонента</param>
    // <param name="newname">новое имя компонента</param>
    void Rename_compName(const QString& oldname, const QString& newname);
    /*******************************************************************/
};

} // namespace TopoR_PCB_Classes
