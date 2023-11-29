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

// Раздел «Слои». (Обязательный раздел)

struct Layers {

    // Описание слоя.

    struct Layer {

        // Имя объекта или ссылка на именованный объект.

        //[XmlAttribute("name")] public string _name;
        std::string _name;

        // Тип слоя. Значение по умолчанию – Signal.

        //[XmlAttribute("type")] public layer_type _type;
        layer_type _type{};

        // Параметр слоя: слой содержит очертания компонентов.

        // <remarks>! Для сигнальных, опорных, диэлектрических и документирующих слоёв параметр compsOutline отсутствует.</remarks>

        //[XmlAttribute("compsOutline")] public Bool _compsOutline;
        Bool _compsOutline{};

        //[XmlIgnore] public bool _compsOutlineSpecified
        bool getCompsOutlineSpecified() const;

        // Параметр слоя: толщина.

        // <remarks>! Для документирующих слоёв и слоёв с типом Assy параметр thickness отсутствует.</remarks>

        //[XmlAttribute("thickness", DataType = "float")] public float _thickness;
        float _thickness = 0.0F;

        //[XmlIgnore] public bool _thicknessSpecified
        bool getThicknessSpecified() const;

        /*****************************************************************
         * Здесь находятся функции для работы с элементами класса Layer. *
         * Они не являются частью формата TopoR PCB.                     *
         * ***************************************************************/
        Layer();

        Layer(const std::string& name, layer_type type, Bool compsOutline, float thickness);

        std::string ToString();
        /*****************************************************************/
    };

    // Версия раздела.

    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Описание слоёв в стеке. Порядок описания должен соответствовать порядку слоёв в стеке.

    //[XmlArray("StackUpLayers")][XmlArrayItem("Layer")] public List<Layer> _StackUpLayers;
    std::vector<std::optional<Layer>> _StackUpLayers;
    bool ShouldSerialize_StackUpLayers();

    // Описание слоёв вне стека.

    //[XmlArray("UnStackLayers")][XmlArrayItem("Layer")] public List<Layer> _UnStackLayers;
    std::vector<std::optional<Layer>> _UnStackLayers;
    bool ShouldSerialize_UnStackLayers();

    /******************************************************************
     * Здесь находятся функции для работы с элементами класса Layers. *
     * Они не являются частью формата TopoR PCB.                      *
     * ****************************************************************/

    // Проверяет существование слоя, на который ссылается ссылка

    // <param name="lref">Ссылка на слой</param>
    // <returns>true, если слой существует</returns>
    bool LayerStackUpContains(std::optional<LayerRef> lref);

    // Проверяет существование слоя, на который ссылается ссылка

    // <param name="lref">Ссылка на слой</param>
    // <returns>true, если слой существует</returns>
    bool LayerUnStackContain(std::optional<LayerRef> lref);
    /******************************************************************/
};
} // namespace TopoR_PCB_Classes
