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
        std::variant<LayerTypeRef, LayerRef> Reference;
    };

    // Описание круглой контактной площадки.
    struct PadCircle /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> Reference;
        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float _diameter; */
        XmlAttr<float> diameter;
        float _diameter = 0.0F;
    };

    // Описание овальной контактной площадки.

    struct PadOval /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> Reference;

        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float _diameter; */
        XmlAttr<float> diameter;
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
        std::variant<LayerTypeRef, LayerRef> Reference;

        // Ширина прямоугольной контактной площадки.
        /* [XmlAttribute("width", DataType = "float")] public float _width; */
        XmlAttr<float> width;
        float _width = 0.0F;

        // Высота прямоугольной контактной площадки.
        /* [XmlAttribute("height", DataType = "float")] public float _height; */
        XmlAttr<float> height;
        float _height = 0.0F;

        // Тип обработки углов прямоугольной контактной площадки.
        /* [XmlAttribute("handling")] public type_handling _handling; */
        XmlAttr<type_handling> handling{};
        /* public bool _handlingSpecified */
        bool getHandlingSpecified() const { return handling != type_handling::None; }

        // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.
        /* [XmlAttribute("handlingValue", DataType = "float")] public float _handlingValue; */
        XmlAttr<float> handlingValue;
        float _handlingValue = 0.0F;
        /* public bool _handlingValueSpecified */
        bool getHandlingValueSpecified() const { return handlingValue != 0; }

        // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.
        /* [XmlAttribute("custom")] public Bool _custom; */
        XmlAttr<Bool> custom{};
        /* public bool _customSpecified */
        bool getCustomSpecified() const { return custom != Bool::off; }

        // Флаг обработки левого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLB")] public Bool _cornerLB; */
        XmlAttr<Bool> cornerLB{};
        /* public bool _cornerLBSpecified */
        bool getCornerLBSpecified() const { return cornerLB != Bool::off; }

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRB")] public Bool _cornerRB; */
        XmlAttr<Bool> cornerRB{};
        /* public bool _cornerRBSpecified */
        bool getCornerRBSpecified() const { return cornerRB != Bool::off; }

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRT")] public Bool _cornerRT; */
        XmlAttr<Bool> cornerRT{};
        /* public bool _cornerRTSpecified */
        bool getCornerRTSpecified() const { return cornerRT != Bool::off; }

        // Флаг обработки левого верхнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLT")] public Bool _cornerLT; */
        XmlAttr<Bool> cornerLT{};
        /* public bool _cornerLTSpecified */
        bool getCornerLTSpecified() const { return cornerLT != Bool::off; }

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift _Shift; */
        Shift _Shift;
    };

    // Описание полигональной контактной площадки.

    struct PadPoly /*: public BasePad {*/ {
        std::variant<LayerTypeRef, LayerRef> Reference;

        // Массив координат точек, вершин.
        // <remarks>! Минимум 3 элемента</remarks>
        /* [XmlElement("Dot")] public List<Dot> Dots; */
        std::vector<Dot> Dots;
        bool ShouldSerialize_Dots() { return Dots.size(); }
    };

    // Описание стека контактных площадок.

    struct Padstack {

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        XmlAttr<QString> name;

        // Тип стека контактных площадок.
        /* [XmlAttribute("type")] public type_padstack _type; */
        XmlAttr<type_padstack> type{};

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float _holeDiameter; */
        XmlAttr<float> holeDiameter;

        // Параметр стека контактной площадки: металлизация отверстия.
        /* [XmlAttribute("metallized")] public Bool _metallized; */
        XmlAttr<Bool> metallized{};
        /* public bool _metallizedSpecified */
        bool getMetallizedSpecified() const { return metallized != Bool::off; }

        // Параметр стека контактной площадки: подключение к области металлизации (полигону).
        /* [XmlAttribute("connectToCopper")] public type_connectToCopper _connectToCopper; */
        XmlAttr<type_connectToCopper> connectToCopper{};

        // Описание термобарьера.
        /* [XmlElement("Thermal")] public Thermal _Thermal; */
        Thermal _Thermal;

#if 0
        // Контактные площадки стека.
        // <value>PadCircle, PadOval, PadRect, PadPoly</value>
        /* [XmlArray("Pads")][XmlArrayItem("PadCircle", typeof(PadCircle)), XmlArrayItem("PadOval", typeof(PadOval)), XmlArrayItem("PadRect", typeof(PadRect)), XmlArrayItem("PadPoly", typeof(PadPoly))] public List<Object> Pads; */
        std::vector<std::variant<PadCircle, PadOval, PadRect, PadPoly>> Pads;
        bool ShouldSerialize_Pads() { return Pads.size(); }
#endif
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
            /* [XmlElement("LayerRef", typeof(LayerRef))] public List<LayerRef> LayerRefs; */
            std::vector<LayerRef> LayerRefs;
            bool ShouldSerialize_LayerRefs() { return LayerRefs.size(); }
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        XmlAttr<QString> name;

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float _holeDiameter; */
        XmlAttr<float> holeDiameter;
        float _holeDiameter = 0.0F;

        // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.
        /* [XmlAttribute("viaOnPin")] public Bool _viaOnPin; */
        XmlAttr<Bool> viaOnPin{};
        /* public bool _viaOnPinSpecified */
        bool getViaOnPinSpecified() const { return viaOnPin != Bool::off; }

        // Диапазон слоев.

        // <value>AllLayers | [LayerRef]</value>
        /* [XmlElement("LayerRange", typeof(LayerRange))] public LayerRange _LayerRange; */
        LayerRange _LayerRange;

        // Описание площадок стека переходного отверстия.
        /* [XmlArray("ViaPads")][XmlArrayItem("PadCircle", typeof(PadCircle))] public List<PadCircle> ViaPads; */
        std::vector<PadCircle> ViaPads;
        bool ShouldSerialize_ViaPads() { return ViaPads.size(); }
    };

    // Описание посадочного места.

    struct Footprint {

        // Описание области металлизации (полигона) в посадочном месте компонента.
        struct Copper_Footprint {

            // Толщина линии.
            /* [XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth; */
            XmlAttr<float> lineWidth;
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
            XmlAttr<QString> id;

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
            XmlAttr<QString> name;

            // Параметр надписей (ярлыков): способ выравнивания текста.
            /* [XmlAttribute("align")] public align _align; */
            XmlAttr<align> _align;

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
            XmlAttr<float> angle;

            // Параметр надписей и ярлыков: зеркальность отображения.
            /* [XmlAttribute("mirror")] public Bool _mirror; */
            XmlAttr<Bool> mirror;
            /* public bool _mirrorSpecified */
            bool getMirrorSpecified() const { return mirror != Bool::off; }

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
            XmlAttr<int> padNum;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            XmlAttr<QString> name;

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float _angle; */
            XmlAttr<float> angle;

            // Параметр контакта (вывода) посадочного места: перевёрнутость.
            // Если флаг не установлен, площадка планарного контакта будет находиться на одной стороне с компонентом,
            // иначе площадка будет расположена на противоположной стороне.
            /* [XmlAttribute("flipped")] public Bool _flipped; */
            XmlAttr<Bool> flipped{};
            /* public bool _flippedSpecified */
            bool getFlippedSpecified() const { return flipped != Bool::off; }

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef _PadstackRef; */
            PadstackRef _PadstackRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org _Org; */
            Org _Org;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        XmlAttr<QString> name;

        // Описание контактных площадок посадочного места.
        /* [XmlArray("Pads")][XmlArrayItem("Pad")] public List<Pad> Pads; */
        std::vector<Pad> Pads;
        bool ShouldSerialize_Pads() { return Pads.size(); }

        // Надписи.
        /* [XmlArray("Texts")][XmlArrayItem("Text")] public List<Text> Texts; */
        std::vector<Text> Texts;
        bool ShouldSerialize_Texts() { return Texts.size(); }

        // Детали посадочного места.
        /* [XmlArray("Details")][XmlArrayItem("Detail")] public List<Detail> Details; */
        std::vector<Detail> Details;
        bool ShouldSerialize_Details() { return Details.size(); }

        // Области металлизации (полигонов) в посадочных местах компонентов.
        /* [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Footprint> Coppers; */
        std::vector<Copper_Footprint> Coppers;
        bool ShouldSerialize_Coppers() { return Coppers.size(); }

        // Запреты размещения в посадочном месте.
        /* [XmlArray("KeepoutsPlace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsPlace; */
        std::vector<Keepout_Place_Trace> KeepoutsPlace;
        bool ShouldSerialize_KeepoutsPlace() { return KeepoutsPlace.size(); }

        // Запреты трассировки в посадочном месте.
        /* [XmlArray("KeepoutsTrace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsTrace; */
        std::vector<Keepout_Place_Trace> KeepoutsTrace;
        bool ShouldSerialize_KeepoutsTrace() { return KeepoutsTrace.size(); }

        // Монтажные отверстия.
        /* [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<Mnthole> Mntholes; */
        std::vector<Mnthole> Mntholes;
        bool ShouldSerialize_Mntholes() { return Mntholes.size(); }

        // Ярлыки.
        /* [XmlArray("Labels")][XmlArrayItem("Label")] public List<Label_Footprint> Labels; */
        std::vector<Label_Footprint> Labels;
        bool ShouldSerialize_Labels() { return Labels.size(); }

        QString ToString() { return name; }
    };

    // Описание схемного компонента.
    struct Component {

        // Описание контакта схемного компонента.
        struct Pin_Component {

            // Номер контакта компонента.
            /* [XmlAttribute("pinNum", DataType = "int")] public int _pinNum; */
            XmlAttr<int> pinNum;
            int _pinNum = 0;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            XmlAttr<QString> name;

            // Схемотехническое имя контакта компонента.
            /* [XmlAttribute("pinSymName")] public string _pinSymName; */
            XmlAttr<QString> pinSymName;

            // Параметр контакта компонента: эквивалентность.
            /* [XmlAttribute("pinEqual", DataType = "int")] public int _pinEqual; */
            XmlAttr<int> pinEqual;
            int _pinEqual = 0;

            // Параметр контакта (вывода) компонента: номер вентиля контакта.
            /* [XmlAttribute("gate", DataType = "int")] public int _gate; */
            XmlAttr<int> gate;
            int _gate = 0;

            // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
            /* [XmlAttribute("gateEqual", DataType = "int")] public int _gateEqual; */
            XmlAttr<int> gateEqual;
            int _gateEqual = 0;
        };

        // Описание атрибута схемного компонента.
        struct Attribute_Component {

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string _name; */
            XmlAttr<QString> name;

            // Значение атрибута.
            /* [XmlAttribute("value")] public string _value; */
            XmlAttr<QString> value;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string _name; */
        XmlAttr<QString> name;

        // Контакты схемного компонента.
        /* [XmlArray("Pins")][XmlArrayItem("Pin")] public List<Pin_Component> Pins; */
        std::vector<Pin_Component> Pins;
        bool ShouldSerialize_Pins() { return Pins.size(); }

        // Атрибуты компонента.
        /* [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<Attribute_Component> Attributes; */
        std::vector<Attribute_Component> Attributes;
        bool ShouldSerialize_Attributes() { return Attributes.size(); }

        QString ToString() { return name; }
    };

    // Описание упаковки (соответствие контактов компонента и выводов посадочного места).
    struct Package {

        // Соответствие контакта схемного компонента и вывода посадочного места.
        struct Pinpack {
            // Номер контакта компонента.
            /* [XmlAttribute("pinNum", DataType = "int")] public int _pinNum; */
            XmlAttr<int> pinNum; // int _pinNum = 0;

            // Номер контактной площадки (вывода) посадочного места.
            /* [XmlAttribute("padNum", DataType = "int")] public int _padNum; */
            XmlAttr<int> padNum; // int _padNum = 0;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            /* [XmlAttribute("valueType")] public valueType _valueType; */
            XmlAttr<valueType> _valueType;

            // Параметр контакта компонента в посадочном месте: задержка сигнала в посадочном месте.
            /* [XmlAttribute("delay", DataType = "float")] public float _delay; */
            XmlAttr<float> delay; // float _delay = 0.0F;
        };

        // Ссылка на схемный компонент.
        /* [XmlElement("ComponentRef")] public ComponentRef _ComponentRef; */
        ComponentRef _ComponentRef;

        // Ссылка на посадочное место.
        /* [XmlElement("FootprintRef")] public FootprintRef _FootprintRef; */
        FootprintRef _FootprintRef;

        // Соответствие контакта схемного компонента и вывода посадочного места.
        /* [XmlElement("Pinpack")] public List<Pinpack> Pinpacks; */
        std::vector<Pinpack> Pinpacks;
        bool ShouldSerialize_Pinpacks() { return Pinpacks.size(); }
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string _version; */
    XmlAttr<QString> version;

    // Стеки контактных площадок.
    /* [XmlArray("Padstacks")][XmlArrayItem("Padstack")] public List<Padstack> Padstacks; */
    std::vector<Padstack> Padstacks;
    bool ShouldSerialize_Padstacks() { return Padstacks.size(); }
#if 0

    // Типы (стеки) переходных отверстий.
    /* [XmlArray("Viastacks")][XmlArrayItem("Viastack")] public List<Viastack> Viastacks; */
    std::vector<Viastack> Viastacks;
    bool ShouldSerialize_Viastacks() { return Viastacks.size(); }

    // Посадочные места.
    /* [XmlArray("Footprints")][XmlArrayItem("Footprint")] public List<Footprint> Footprints; */
    std::vector<Footprint> Footprints;
    bool ShouldSerialize_Footprints() { return Footprints.size(); }

    // Схемные компоненты.
    /* [XmlArray("Components")][XmlArrayItem("Component")] public List<Component> Components; */
    std::vector<Component> Components;
    bool ShouldSerialize_Components() { return Components.size(); }

    // Упаковки.
    /* [XmlArray("Packages")][XmlArrayItem("Package")] public List<Package> Packages; */
    std::vector<Package> Packages;
    bool ShouldSerialize_Packages() { return Packages.size(); }
#endif
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
