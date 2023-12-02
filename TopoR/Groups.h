#pragma once

#include "Commons.h"

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

        /* [XmlAttribute("name")] public string name_; */
        QString name_;

        // Ссылка на слой или ссылка на группу слоёв.

        /* [XmlElement("LayerRef", typeof(LayerRef)),
            XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public List<Object> LayerRefs_; */
        std::vector<std::variant<LayerRef, LayerGroupRef>> LayerRefs_;
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

        /* [XmlAttribute("name")] public string name_; */
        QString name_;

        // Ссылка на цепь или ссылка на группу цепей.

        /* [XmlElement("NetRef", typeof(NetRef)),
            XmlElement("NetGroupRef", typeof(NetGroupRef))] public List<Object> NetRefs_; */
        std::vector<std::variant<NetRef, NetGroupRef>> NetRefs_;
        bool ShouldSerialize_NetRefs();
    };

    // Описание группы компонентов.

    struct CompGroup {

        // Имя объекта или ссылка на именованный объект.

        /* [XmlAttribute("name")] public string name_; */
        QString name_;

        // Ссылка на компонент на плате или ссылка на группу компонентов.

        /* [XmlElement("CompInstanceRef", typeof(CompInstanceRef)),
            XmlElement("CompGroupRef", typeof(CompGroupRef))] public List<Object> CompRefs_; */
        std::vector<std::variant<CompInstanceRef, CompGroupRef>> CompRefs_;
        bool ShouldSerialize_CompRefs();
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string version_; */
    QString version_;

    // Группы слоёв.

    /* [XmlArray("LayerGroups")][XmlArrayItem("LayerGroup")] public List<LayerGroup> LayerGroups_; */
    std::vector<LayerGroup> LayerGroups_;
    bool ShouldSerialize_LayerGroups();

    // Группы цепей.

    /* [XmlArray("NetGroups")][XmlArrayItem("NetGroup")] public List<NetGroup> NetGroups_; */
    std::vector<NetGroup> NetGroups_;
    bool ShouldSerialize_NetGroups();

    // Группы компонентов.

    /* [XmlArray("CompGroups")][XmlArrayItem("CompGroup")] public List<CompGroup> CompGroups_; */
    std::vector<CompGroup> CompGroups_;
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
