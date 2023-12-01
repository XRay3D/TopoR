#pragma once

#include "Commons.h"
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */

namespace TopoR_PCB_Classes {

// Раздел «Библиотечные элементы». (Обязательный раздел)

struct LocalLibrary {

    struct BasePad {
        // Ссылка на слой или тип слоя.
        // <value>LayerTypeRef | LayerRef</value>
        /* [XmlElement("LayerTypeRef", typeof(LayerTypeRef)),
            XmlElement("LayerRef", typeof(LayerRef))] public Object _Reference; */
        std::variant<LayerTypeRef, LayerRef> _Reference;
    };

    // Описание круглой контактной площадки.

    struct PadCircle /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> _Reference;
        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float _diameter; */
        Attribute<float> diameter;
        float _diameter = 0.0F;
    };

    // Описание овальной контактной площадки.

    struct PadOval /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> _Reference;

        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float _diameter; */
        Attribute<float> diameter;
        float _diameter = 0.0F;

        // Параметр овальной контактной площадки: вытягивание по осям x и y.
        /* [XmlElement("Stretch")] public Stretch _Stretch; */
        Stretch _Stretch;

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift _Shift; */
        Shift _Shift;
    };

    // Описание прямоугольной контактной площадки.
    // Дополнительные атрибуты(handling и handlingValue) позволяют задавать тип и величину обработки углов.
    // В качестве типа обработки допускается скругление или срез.
    // Тип для всех углов должен быть одинаковым: нельзя скруглять один угол и срезать другой.
    // Если флаг custom не установлен, обрабатываются все углы, иначе будут обработаны только углы,
    // соответствующие установленным флагам - cornerLB, cornerRB, cornerRT, cornerLT.
    // Основные формы КП, которые данный формат позволяет описать:
    // прямоугольные КП;
    // прямоугольные КП со скруглёнными углами;
    // прямоугольные КП со срезанными углами;
    // Finger pads.

    struct PadRect /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> _Reference;

        // Ширина прямоугольной контактной площадки.
        /* [XmlAttribute("width", DataType = "float")] public float _width; */
        Attribute<float> width;
        float _width = 0.0F;

        // Высота прямоугольной контактной площадки.
        /* [XmlAttribute("height", DataType = "float")] public float _height; */
        Attribute<float> height;
        float _height = 0.0F;

        // Тип обработки углов прямоугольной контактной площадки.
        /* [XmlAttribute("handling")] public type_handling _handling; */
        type_handling _handling{};
        /* [XmlIgnore] public bool _handlingSpecified */
        bool getHandlingSpecified() const;

        // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.
        /* [XmlAttribute("handlingValue", DataType = "float")] public float _handlingValue; */
        Attribute<float> handlingValue;
        float _handlingValue = 0.0F;
        /* [XmlIgnore] public bool _handlingValueSpecified */
        bool getHandlingValueSpecified() const;

        // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.
        /* [XmlAttribute("custom")] public Bool _custom; */
        Bool _custom{};
        /* [XmlIgnore] public bool _customSpecified */
        bool getCustomSpecified() const;

        // Флаг обработки левого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLB")] public Bool _cornerLB; */
        Bool _cornerLB{};
        /* [XmlIgnore] public bool _cornerLBSpecified */
        bool getCornerLBSpecified() const;

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRB")] public Bool _cornerRB; */
        Bool _cornerRB{};
        /* [XmlIgnore] public bool _cornerRBSpecified */
        bool getCornerRBSpecified() const;

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRT")] public Bool _cornerRT; */
        Bool _cornerRT{};
        /* [XmlIgnore] public bool _cornerRTSpecified */
        bool getCornerRTSpecified() const;

        // Флаг обработки левого верхнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLT")] public Bool _cornerLT; */
        Bool _cornerLT{};
        /* [XmlIgnore] public bool _cornerLTSpecified */
        bool getCornerLTSpecified() const;

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift _Shift; */
        Shift _Shift;
    };

    // Описание полигональной контактной площадки.

    struct PadPoly /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> _Reference;

        // Массив координат точек, вершин.
        // <remarks>! Минимум 3 элемента</remarks>
        /* [XmlElement("Dot")] public List<Dot> _Dots; */
        std::vector<Dot> _Dots;
        bool ShouldSerialize_Dots();
    };

    // Описание стека контактных площадок.

    struct Padstack {

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Тип стека контактных площадок.
        /* [XmlAttribute("type")] public type_padstack _type; */
        type_padstack _type{};

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float _holeDiameter; */
        Attribute<float> holeDiameter;
        float _holeDiameter = 0.0F;

        // Параметр стека контактной площадки: металлизация отверстия.
        /* [XmlAttribute("metallized")] public Bool _metallized; */
        Bool _metallized{};
        /* [XmlIgnore] public bool _metallizedSpecified */
        bool getMetallizedSpecified() const;

        // Параметр стека контактной площадки: подключение к области металлизации (полигону).
        /* [XmlAttribute("connectToCopper")] public type_connectToCopper _connectToCopper; */
        type_connectToCopper _connectToCopper{};

        // Описание термобарьера.
        /* [XmlElement("Thermal")] public Thermal _Thermal; */
        Thermal _Thermal;

        // Контактные площадки стека.

        // <value>PadCircle, PadOval, PadRect, PadPoly</value>
        /* [XmlArray("Pads")][XmlArrayItem("PadCircle", typeof(PadCircle)), XmlArrayItem("PadOval", typeof(PadOval)), XmlArrayItem("PadRect", typeof(PadRect)), XmlArrayItem("PadPoly", typeof(PadPoly))] public List<Object> _Pads; */
        std::vector<std::variant<PadCircle, PadOval, PadRect, PadPoly>> _Pads;
        bool ShouldSerialize_Pads();
    };

    // Описание типа (стека) переходного отверстия.

    struct Viastack {

        // Диапазон слоев.

        // <value>AllLayers | [LayerRef]</value>

        struct LayerRange {

            // AllLayers - yстанавливает область действия правила: все слои. См. также _LayerRefs

            // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
            /* [XmlElement("AllLayers", typeof(AllLayers))] public AllLayers _AllLayers; */
            AllLayers _AllLayers;

            // Диапазон слоёв. См. также _AllLayers

            // <remarks>! При null необходимо смотреть наличие _AllLayers. </remarks>
            /* [XmlElement("LayerRef", typeof(LayerRef))] public List<LayerRef> _LayerRefs; */
            std::vector<LayerRef> _LayerRefs;
            bool ShouldSerialize_LayerRefs();
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float _holeDiameter; */
        Attribute<float> holeDiameter;
        float _holeDiameter = 0.0F;

        // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.
        /* [XmlAttribute("viaOnPin")] public Bool _viaOnPin; */
        Bool _viaOnPin{};
        /* [XmlIgnore] public bool _viaOnPinSpecified */
        bool getViaOnPinSpecified() const;

        // Диапазон слоев.

        // <value>AllLayers | [LayerRef]</value>
        /* [XmlElement("LayerRange", typeof(LayerRange))] public LayerRange _LayerRange; */
        LayerRange _LayerRange;

        // Описание площадок стека переходного отверстия.
        /* [XmlArray("ViaPads")][XmlArrayItem("PadCircle", typeof(PadCircle))] public List<PadCircle> _ViaPads; */
        std::vector<PadCircle> _ViaPads;
        bool ShouldSerialize_ViaPads();
    };

    // Описание посадочного места.

    struct Footprint {

        // Описание области металлизации (полигона) в посадочном месте компонента.

        struct Copper_Footprint {

            // Толщина линии.
            /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
            Attribute<float> lineWidth;
            float _lineWidth = 0.0F;

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
            LayerRef _LayerRef;

            // Описание фигуры.

            // <value>ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon</value>
            /* [XmlElement("ArcCCW", typeof(ArcCCW)),
                XmlElement("ArcCW", typeof(ArcCW)),
                XmlElement("ArcByAngle", typeof(ArcByAngle)),
                XmlElement("ArcByMiddle", typeof(ArcByMiddle)),
                XmlElement("Line", typeof(Line)),
                XmlElement("Circle", typeof(Circle)),
                XmlElement("Rect", typeof(Rect)),
                XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure; */
            std::variant<ArcCCW,
                ArcCW,
                ArcByAngle,
                ArcByMiddle,
                Line,
                Circle,
                Rect,
                FilledCircle,
                FilledRect,
                Polygon,
                FilledContour>
                _Figure;
        };

        // Описание запрета в посадочном месте Footprint. Для запрета размещения должен быть указан слой с типом Assy.

        struct Keepout_Place_Trace {

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
            LayerRef _LayerRef;

            // Описание фигуры.

            // <value>ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon</value>
            /* [XmlElement("ArcCCW", typeof(ArcCCW)),
                XmlElement("ArcCW", typeof(ArcCW)),
                XmlElement("ArcByAngle", typeof(ArcByAngle)),
                XmlElement("ArcByMiddle", typeof(ArcByMiddle)),
                XmlElement("Line", typeof(Line)),
                XmlElement("Circle", typeof(Circle)),
                XmlElement("Rect", typeof(Rect)),
                XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object _Figure; */
            std::variant<ArcCCW,
                ArcCW,
                ArcByAngle,
                ArcByMiddle,
                Line,
                Circle,
                Rect,
                FilledCircle,
                FilledRect,
                Polygon,
                FilledContour>
                _Figure;
        };

        // Описание монтажного отверстия в посадочном месте.

        struct Mnthole {

            // Идентификатор неименованных объектов.
            /* [XmlAttribute("id")] public string _id; */
            QString _id;

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
            PadstackRef _PadstackRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org _Org; */
            Org _Org;
        };

        // Описание ярлыка в посадочном месте.

        struct Label_Footprint {

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            QString _name;

            // Параметр надписей (ярлыков): способ выравнивания текста.
            /* [XmlAttribute("align")] public align _align; */
            align _align{};

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
            Attribute<float> angle;
            float _angle = 0.0F;

            // Параметр надписей и ярлыков: зеркальность отображения.
            /* [XmlAttribute("mirror")] public Bool _mirror; */
            Bool _mirror{};
            /* [XmlIgnore] public bool _mirrorSpecified */
            bool getMirrorSpecified() const;

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef _LayerRef; */
            LayerRef _LayerRef;

            // Ссылка на стиль надписей.
            /* [XmlElement("TextStyleRef")] public TextStyleRef _TextStyleRef; */
            TextStyleRef _TextStyleRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org _Org; */
            Org _Org;
        };

        // Описание контактной площадки (вывода) посадочного места.

        // <remarks>! В системе TopoR поддерживаются планарные контакты на внешних металлических слоях и не поддерживаются на внутренних.
        // Т.е.у планарного контакта может быть только одна площадка или на верхней стороне, или на нижней.
        // В описании планарного контакта используется только слой Top.
        // Это означает, что контактная площадка будет находиться на одной стороне с компонентом.
        // Если же площадка находится на противоположной стороне, то должен быть установлен флаг flipped.
        // Этот флаг устанавливается в описании контакта посадочного места.
        // </remarks>

        struct Pad {

            // Номер контактной площадки (вывода) посадочного места.
            /* [XmlAttribute("padNum", DataType = "int")] public int _padNum; */
            Attribute<int> padNum;
            int _padNum = 0;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            QString _name;

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
            Attribute<float> angle;
            float _angle = 0.0F;

            // Параметр контакта (вывода) посадочного места: перевёрнутость.
            // Если флаг не установлен, площадка планарного контакта будет находиться на одной стороне с компонентом,
            // иначе площадка будет расположена на противоположной стороне.
            /* [XmlAttribute("flipped")] public Bool _flipped; */
            Bool _flipped{};
            /* [XmlIgnore] public bool _flippedSpecified */
            bool getFlippedSpecified() const;

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
            PadstackRef _PadstackRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org _Org; */
            Org _Org;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Описание контактных площадок посадочного места.
        /* [XmlArray("Pads")][XmlArrayItem("Pad")] public List<Pad> _Pads; */
        std::vector<Pad> _Pads;
        bool ShouldSerialize_Pads();

        // Надписи.
        /* [XmlArray("Texts")][XmlArrayItem("Text")] public List<Text> _Texts; */
        std::vector<Text> _Texts;
        bool ShouldSerialize_Texts();

        // Детали посадочного места.
        /* [XmlArray("Details")][XmlArrayItem("Detail")] public List<Detail> _Details; */
        std::vector<Detail> _Details;
        bool ShouldSerialize_Details();

        // Области металлизации (полигонов) в посадочных местах компонентов.
        /* [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Footprint> _Coppers; */
        std::vector<Copper_Footprint> _Coppers;
        bool ShouldSerialize_Coppers();

        // Запреты размещения в посадочном месте.
        /* [XmlArray("KeepoutsPlace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> _KeepoutsPlace; */
        std::vector<Keepout_Place_Trace> _KeepoutsPlace;
        bool ShouldSerialize_KeepoutsPlace();

        // Запреты трассировки в посадочном месте.
        /* [XmlArray("KeepoutsTrace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> _KeepoutsTrace; */
        std::vector<Keepout_Place_Trace> _KeepoutsTrace;
        bool ShouldSerialize_KeepoutsTrace();

        // Монтажные отверстия.
        /* [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<Mnthole> _Mntholes; */
        std::vector<Mnthole> _Mntholes;
        bool ShouldSerialize_Mntholes();

        // Ярлыки.
        /* [XmlArray("Labels")][XmlArrayItem("Label")] public List<Label_Footprint> _Labels; */
        std::vector<Label_Footprint> _Labels;
        bool ShouldSerialize_Labels();

        QString ToString();
    };

    // Описание схемного компонента.

    struct Component {

        // Описание контакта схемного компонента.

        struct Pin_Component {

            // Номер контакта компонента.
            /* [XmlAttribute("pinNum", DataType = "int")] public int _pinNum; */
            Attribute<int> pinNum;
            int _pinNum = 0;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            QString _name;

            // Схемотехническое имя контакта компонента.
            /* [XmlAttribute("pinSymName")] public string _pinSymName; */
            QString _pinSymName;

            // Параметр контакта компонента: эквивалентность.
            /* [XmlAttribute("pinEqual", DataType = "int")] public int _pinEqual; */
            Attribute<int> pinEqual;
            int _pinEqual = 0;

            // Параметр контакта (вывода) компонента: номер вентиля контакта.
            /* [XmlAttribute("gate", DataType = "int")] public int _gate; */
            Attribute<int> gate;
            int _gate = 0;

            // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
            /* [XmlAttribute("gateEqual", DataType = "int")] public int _gateEqual; */
            Attribute<int> gateEqual;
            int _gateEqual = 0;
        };

        // Описание атрибута схемного компонента.

        struct Attribute_Component {

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            QString _name;

            // Значение атрибута.
            /* [XmlAttribute("value")] public string _value; */
            QString _value;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        QString _name;

        // Контакты схемного компонента.
        /* [XmlArray("Pins")][XmlArrayItem("Pin")] public List<Pin_Component> _Pins; */
        std::vector<Pin_Component> _Pins;
        bool ShouldSerialize_Pins();

        // Атрибуты компонента.
        /* [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<Attribute_Component> _Attributes; */
        std::vector<Attribute_Component> _Attributes;
        bool ShouldSerialize_Attributes();

        QString ToString();
    };

    // Описание упаковки (соответствие контактов компонента и выводов посадочного места).

    struct Package {

        // Соответствие контакта схемного компонента и вывода посадочного места.

        struct Pinpack {

            // Номер контакта компонента.
            /* [XmlAttribute("pinNum", DataType = "int")] public int _pinNum; */
            Attribute<int> pinNum;
            int _pinNum = 0;

            // Номер контактной площадки (вывода) посадочного места.
            /* [XmlAttribute("padNum", DataType = "int")] public int _padNum; */
            Attribute<int> padNum;
            int _padNum = 0;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            /* [XmlAttribute("valueType")] public valueType _valueType; */
            valueType _valueType{};

            // Параметр контакта компонента в посадочном месте: задержка сигнала в посадочном месте.
            /* [XmlAttribute("delay", DataType = "float")] public float _delay; */
            Attribute<float> delay;
            float _delay = 0.0F;
        };

        // Ссылка на схемный компонент.
        /* [XmlElement("ComponentRef")] public ComponentRef _ComponentRef; */
        ComponentRef _ComponentRef;

        // Ссылка на посадочное место.
        /* [XmlElement("FootprintRef")] public FootprintRef _FootprintRef; */
        FootprintRef _FootprintRef;

        // Соответствие контакта схемного компонента и вывода посадочного места.
        /* [XmlElement("Pinpack")] public List<Pinpack> _Pinpacks; */
        std::vector<Pinpack> _Pinpacks;
        bool ShouldSerialize_Pinpacks();
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string _version; */
    QString _version;

    // Стеки контактных площадок.
    /* [XmlArray("Padstacks")][XmlArrayItem("Padstack")] public List<Padstack> _Padstacks; */
    std::vector<Padstack> _Padstacks;
    bool ShouldSerialize_Padstacks();

    // Типы (стеки) переходных отверстий.
    /* [XmlArray("Viastacks")][XmlArrayItem("Viastack")] public List<Viastack> _Viastacks; */
    std::vector<Viastack> _Viastacks;
    bool ShouldSerialize_Viastacks();

    // Посадочные места.
    /* [XmlArray("Footprints")][XmlArrayItem("Footprint")] public List<Footprint> _Footprints; */
    std::vector<Footprint> _Footprints;
    bool ShouldSerialize_Footprints();

    // Схемные компоненты.
    /* [XmlArray("Components")][XmlArrayItem("Component")] public List<Component> _Components; */
    std::vector<Component> _Components;
    bool ShouldSerialize_Components();

    // Упаковки.
    /* [XmlArray("Packages")][XmlArrayItem("Package")] public List<Package> _Packages; */
    std::vector<Package> _Packages;
    bool ShouldSerialize_Packages();

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
