#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Группировка объектов».
struct Groups {
    // Описание групп слоёв.
    struct LayerGroup {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Ссылка на слой или ссылка на группу слоёв.
        // [XmlElement(LayerRef, LayerGroupRef)] public List<Object> LayerRefs_;
        XmlArray<XmlVariant<LayerRef, LayerGroupRef>> LayerRefs;
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
        XmlAttr<QString> name;
        // Ссылка на цепь или ссылка на группу цепей.
        // [XmlElement(NetRef),
        //  XmlElement(NetGroupRef)] public List<Object> NetRefs_;
        XmlArray<XmlVariant<NetRef, NetGroupRef>> NetRefs;
    };
    // Описание группы компонентов.
    struct CompGroup {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Ссылка на компонент на плате или ссылка на группу компонентов.
        // [XmlElement(CompInstanceRef),
        //  XmlElement(CompGroupRef)] public List<Object> CompRefs_;
        XmlArray<XmlVariant<CompInstanceRef, CompGroupRef>> CompRefs;
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Группы слоёв.
    // [XmlArray("LayerGroups")][XmlArrayItem("LayerGroup")] public List<LayerGroup> LayerGroups_;
    XmlArrayElem<LayerGroup> LayerGroups;
    // Группы цепей.
    // [XmlArray("NetGroups")][XmlArrayItem("NetGroup")] public List<NetGroup> NetGroups_;
    XmlArrayElem<NetGroup> NetGroups;
    // Группы компонентов.
    // [XmlArray("CompGroups")][XmlArrayItem("CompGroup")] public List<CompGroup> CompGroups_;
    XmlArrayElem<CompGroup> CompGroups;
    /******************************************************************
     * Здесь находятся функции для работы с элементами класса Groups. *
     * Они не являются частью формата TopoR PCB.                      *
     * ****************************************************************/
    // Переименование ссылок на компонент, если его имя изменилось
    /// \param '1 \brief старое имя компонента
    /// \param '1 \brief новое имя компонента
    void Rename_compName(const QString& oldname, const QString& newname);
    /******************************************************************/
};
} // namespace TopoR
