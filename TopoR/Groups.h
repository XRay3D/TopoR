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
        Xml::Attr<QString> name;
        // Ссылка на слой или ссылка на группу слоёв.
        // [Xml::Element(LayerRef, LayerGroupRef)] public List<Object> LayerRefs_;
        Xml::Array<Xml::Variant<LayerRef, LayerGroupRef>> LayerRefs;
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
        Xml::Attr<QString> name;
        // Ссылка на цепь или ссылка на группу цепей.
        // [Xml::Element(NetRef),
        //  Xml::Element(NetGroupRef)] public List<Object> NetRefs_;
        Xml::Array<Xml::Variant<NetRef, NetGroupRef>> NetRefs;
    };
    // Описание группы компонентов.
    struct CompGroup {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Ссылка на компонент на плате или ссылка на группу компонентов.
        // [Xml::Element(CompInstanceRef),
        //  Xml::Element(CompGroupRef)] public List<Object> CompRefs_;
        Xml::Array<Xml::Variant<CompInstanceRef, CompGroupRef>> CompRefs;
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Группы слоёв.
    // [Xml::Array("LayerGroups")][Xml::ArrayItem("LayerGroup")] public List<LayerGroup> LayerGroups_;
    Xml::ArrayElem<LayerGroup> LayerGroups;
    // Группы цепей.
    // [Xml::Array("NetGroups")][Xml::ArrayItem("NetGroup")] public List<NetGroup> NetGroups_;
    Xml::ArrayElem<NetGroup> NetGroups;
    // Группы компонентов.
    // [Xml::Array("CompGroups")][Xml::ArrayItem("CompGroup")] public List<CompGroup> CompGroups_;
    Xml::ArrayElem<CompGroup> CompGroups;

    bool isEmpty() const { return LayerGroups.empty() && NetGroups.empty() && CompGroups.empty(); }
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
