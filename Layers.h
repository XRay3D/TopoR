#pragma once

#include "Commons.h"
#include <string>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

// namespace TopoR_PCB_Classes {

/// <summary>
/// Описание слоя.
/// </summary>

class Layer : public QSerializer {
    Q_GADGET
    QS_META_OBJECT_METHOD

    /// <summary>
    /// Имя объекта или ссылка на именованный объект.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("name")] public string _name;
    QS_ATTR(QString, name)

    /// <summary>
    /// Тип слоя. Значение по умолчанию – Signal.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("type")] public layer_type _type;
    QS_ATTR(layer_type, type); // = static_cast<layer_type>(0);

    /// <summary>
    /// Параметр слоя: слой содержит очертания компонентов.
    /// </summary>
    /// <remarks>! Для сигнальных, опорных, диэлектрических и документирующих слоёв параметр compsOutline отсутствует.</remarks>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("compsOutline")] public Bool _compsOutline;
    //    QS_ATTR(Bool, compsOutline) // = static_cast<Bool>(0);

    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlIgnore] public bool _compsOutlineSpecified
    bool getCompsOutlineSpecified() const;

    /// <summary>
    /// Параметр слоя: толщина.
    /// </summary>
    /// <remarks>! Для документирующих слоёв и слоёв с типом Assy параметр thickness отсутствует.</remarks>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("thickness", DataType = "float")] public float _thickness;
    QS_ATTR(float, thickness) // = 0.0F;

public:
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlIgnore] public bool _thicknessSpecified
    bool getThicknessSpecified() const;

    /*****************************************************************
     * Здесь находятся функции для работы с элементами класса Layer. *
     * Они не являются частью формата TopoR PCB.                     *
     * ***************************************************************/
    Layer();

    Layer(const QString& name, layer_type type, Bool compsOutline, float thickness);

    QString ToString();
    /*****************************************************************/
};

Q_DECLARE_METATYPE(Layer)

/// <summary>
/// Раздел «Слои». (Обязательный раздел)
/// </summary>
class Layers_ : public QSerializer {

    Q_GADGET
    QS_META_OBJECT_METHOD

    /// <summary>
    /// Версия раздела.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlAttribute("version")] public string _version;
    QS_ATTR(QString, version)

    /// <summary>
    /// Описание слоёв в стеке. Порядок описания должен соответствовать порядку слоёв в стеке.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlArray("StackUpLayers")][XmlArrayItem("Layer")] public List<Layer> _StackUpLayers;
    QS_COLLECTION_OBJECTS(std::vector, Layer, StackUpLayers)
    bool ShouldSerialize_StackUpLayers();
    /// <summary>
    /// Описание слоёв вне стека.
    /// </summary>
    // C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
    // ORIGINAL LINE: [XmlArray("UnStackLayers")][XmlArrayItem("Layer")] public List<Layer> _UnStackLayers;
    QS_COLLECTION_OBJECTS(std::vector, Layer, UnStackLayers);
    bool ShouldSerialize_UnStackLayers();

    /******************************************************************
     * Здесь находятся функции для работы с элементами класса Layers. *
     * Они не являются частью формата TopoR PCB.                      *
     * ****************************************************************/
    /// <summary>
    /// Проверяет существование слоя, на который ссылается ссылка
    /// </summary>
    /// <param name="lref">Ссылка на слой</param>
    /// <returns>true, если слой существует</returns>
    bool LayerStackUpContains(LayerRef& lref);
    /// <summary>
    /// Проверяет существование слоя, на который ссылается ссылка
    /// </summary>
    /// <param name="lref">Ссылка на слой</param>
    /// <returns>true, если слой существует</returns>
    bool LayerUnStackContain(LayerRef& lref);
    /******************************************************************/
};
// } // namespace TopoR_PCB_Classes
