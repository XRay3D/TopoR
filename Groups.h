﻿#pragma once

#include <QString>
#include <any>
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

// Раздел «Группировка объектов».

struct Groups {

    // Описание групп слоёв.

    struct LayerGroup {

        // Имя объекта или ссылка на именованный объект.

        //[XmlAttribute("name")] public string _name;
        QString _name;

        // Ссылка на слой или ссылка на группу слоёв.

        //[XmlElement("LayerRef", typeof(LayerRef)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public List<Object> _LayerRefs;
        std::vector<std::any> _LayerRefs;
        bool ShouldSerialize_LayerRefs();
        /**********************************************************************
         * Здесь находятся функции для работы с элементами класса LayerGroup. *
         * Они не являются частью формата TopoR PCB.                          *
         * *******************************************************************/
        QString ToString();
        /*********************************************************************/
    };

    // Описание группы цепей.

    struct NetGroup {

        // Имя объекта или ссылка на именованный объект.

        //[XmlAttribute("name")] public string _name;
        QString _name;

        // Ссылка на цепь или ссылка на группу цепей.

        //[XmlElement("NetRef", typeof(NetRef)), XmlElement("NetGroupRef", typeof(NetGroupRef))] public List<Object> _NetRefs;
        std::vector<std::any> _NetRefs;
        bool ShouldSerialize_NetRefs();
    };

    // Описание группы компонентов.

    struct CompGroup {

        // Имя объекта или ссылка на именованный объект.

        //[XmlAttribute("name")] public string _name;
        QString _name;

        // Ссылка на компонент на плате или ссылка на группу компонентов.

        //[XmlElement("CompInstanceRef", typeof(CompInstanceRef)), XmlElement("CompGroupRef", typeof(CompGroupRef))] public List<Object> _CompRefs;
        std::vector<std::any> _CompRefs;
        bool ShouldSerialize_CompRefs();
    };

    // Версия раздела.

    //[XmlAttribute("version")] public string _version;
    QString _version;

    // Группы слоёв.

    //[XmlArray("LayerGroups")][XmlArrayItem("LayerGroup")] public List<LayerGroup> _LayerGroups;
    std::vector<LayerGroup> _LayerGroups;
    bool ShouldSerialize_LayerGroups();

    // Группы цепей.

    //[XmlArray("NetGroups")][XmlArrayItem("NetGroup")] public List<NetGroup> _NetGroups;
    std::vector<NetGroup> _NetGroups;
    bool ShouldSerialize_NetGroups();

    // Группы компонентов.

    //[XmlArray("CompGroups")][XmlArrayItem("CompGroup")] public List<CompGroup> _CompGroups;
    std::vector<CompGroup> _CompGroups;
    bool ShouldSerialize_CompGroups();

    /******************************************************************
     * Здесь находятся функции для работы с элементами класса Groups. *
     * Они не являются частью формата TopoR PCB.                      *
     * ****************************************************************/

    // Переименование ссылок на компонент, если его имя изменилось

    // <param name="oldname">старое имя компонента</param>
    // <param name="newname">новое имя компонента</param>
    void Rename_compName(const QString& oldname, const QString& newname);
    /******************************************************************/
};

} // namespace TopoR_PCB_Classes
