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
namespace TopoR {
// Раздел «Слои». (Обязательный раздел)
struct Layers {
    // Описание слоя.
    struct Layer {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Тип слоя. Значение по умолчанию – Signal.
        // [XmlAttribute("type")] public LayerType type_;
        XmlAttr<LayerType> type;
        // Параметр слоя: слой содержит очертания компонентов.
        /// \note !Для сигнальных, опорных, диэлектрических и документирующих слоёв параметр compsOutline отсутствует.
        // [XmlAttribute("compsOutline")] public Bool compsOutline_;
        std::optional<XmlAttr<Bool>> compsOutline;
        // Параметр слоя: толщина.
        /// \note !Для документирующих слоёв и слоёв с типом Assy параметр thickness отсутствует.
        // [XmlAttribute("thickness", DataType = "float")] public float thickness_;
        std::optional<XmlAttr<float>> thickness;
        /* public bool compsOutlineSpecified_ */
        /* public bool thicknessSpecified_ */
        /*****************************************************************
         * Здесь находятся функции для работы с элементами класса Layer. *
         * Они не являются частью формата TopoR PCB.                     *
         * ***************************************************************/
        // Layer() { }
        // Layer(const QString& name, LayerType type, Bool compsOutline, float thickness) {
        //     name_ = name;
        //     type_ = type;
        //     compsOutline_ = compsOutline;
        //     thickness_ = thickness;
        // }
        QString ToString() { return name; }

        bool isCompsOutline() const { return type == LayerType::Assy; }
        bool hasThickness() const { return type != LayerType::Assy; }
        /*****************************************************************/
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Описание слоёв в стеке. Порядок описания должен соответствовать порядку слоёв в стеке.
    // [XmlArray("StackUpLayers")][XmlArrayItem("Layer")] public List<Layer> StackUpLayers_;
    XmlArrayElem<Layer> StackUpLayers;
    // Описание слоёв вне стека.
    // [XmlArray("UnStackLayers")][XmlArrayItem("Layer")] public List<Layer> UnStackLayers_;
    XmlArrayElem<Layer> UnStackLayers;
    /******************************************************************
     * Здесь находятся функции для работы с элементами класса Layers. *
     * Они не являются частью формата TopoR PCB.                      *
     * ****************************************************************/
    // Проверяет существование слоя, на который ссылается ссылка
    /// \param '1 \brief Ссылка на слой
    /// \return  true, если слой существует
    bool LayerStackUpContains(LayerRef lref) const;
    // Проверяет существование слоя, на который ссылается ссылка
    /// \param '1 \brief Ссылка на слой
    /// \return  true, если слой существует
    bool LayerUnStackContain(LayerRef lref) const;
    /******************************************************************/
};
} // namespace TopoR
