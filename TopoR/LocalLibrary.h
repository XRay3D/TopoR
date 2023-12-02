#pragma once

#include "Commons.h"
#include <QPainterPath>
#include <QPolygonF>
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

/* Мною, Константином aka KilkennyCat,05 июля 2020 года создано сиё
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
            XmlElement("LayerRef", typeof(LayerRef))] public Object Reference_; */
        XmlVariant<LayerTypeRef, LayerRef> Reference;
    };

    // Описание круглой контактной площадки.
    struct PadCircle /*: public BasePad {*/ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;
        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float diameter_; */
        XmlAttr<float> diameter;
        operator QPainterPath() const {
            QPainterPath path;
            path.addEllipse(QPointF{}, diameter * 0.5, diameter * 0.5);
            return path;
        }
    };

    // Описание овальной контактной площадки.
    struct PadOval /*: public BasePad {*/ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;

        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float diameter_; */
        XmlAttr<float> diameter;

        // Параметр овальной контактной площадки: вытягивание по осям x и y.
        /* [XmlElement("Stretch")] public Stretch Stretch_; */
        Stretch Stretch_;

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift Shift_; */
        Shift Shift_;
        operator QPainterPath() const {
            QPainterPath path;
            QLineF line{{}, Stretch_};
            line = line.translated(Shift_);
            path.moveTo(line.p1());
            path.lineTo(line.p2());
            path.translate(Shift_);
            path.addEllipse(line.p1(), diameter * 0.5, diameter * 0.5);
            path.addEllipse(line.p2(), diameter * 0.5, diameter * 0.5);
            return path;
        }
    };

    // Описание прямоугольной контактной площадки.
    // Дополнительные атрибуты(handling и handlingValue) позволяют задавать тип и величину обработки углов.
    // В качестве типа обработки допускается скругление или срез.
    // Тип для всех углов должен быть одинаковым: нельзя скруглять один угол и срезать другой.
    // Если флаг custom не установлен, обрабатываются все углы, иначе будут обработаны только углы,
    // соответствующие установленным флагам - cornerLB,cornerRB,cornerRT,cornerLT.
    // Основные формы КП, которые данный формат позволяет описать:
    // прямоугольные КП;
    // прямоугольные КП со скруглёнными углами;
    // прямоугольные КП со срезанными углами;
    // Finger pads.
    struct PadRect /*: public BasePad {*/ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;

        // Ширина прямоугольной контактной площадки.
        /* [XmlAttribute("width", DataType = "float")] public float width_; */
        XmlAttr<float> width;

        // Высота прямоугольной контактной площадки.
        /* [XmlAttribute("height", DataType = "float")] public float height_; */
        XmlAttr<float> height;

        // Тип обработки углов прямоугольной контактной площадки.
        /* [XmlAttribute("handling")] public type_handling handling_; */
        XmlAttr<type_handling> handling{};
        /* public bool _handlingSpecified */
        bool isHandlingSpecified() const { return handling != type_handling::None; }

        // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.
        /* [XmlAttribute("handlingValue", DataType = "float")] public float handlingValue_; */
        XmlAttr<float> handlingValue;
        /* public bool _handlingValueSpecified */
        bool isHandlingValueSpecified() const { return handlingValue != 0; }

        // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.
        /* [XmlAttribute("custom")] public Bool custom_; */
        XmlAttr<Bool> custom{};
        /* public bool _customSpecified */
        bool isCustomSpecified() const { return custom != Bool::off; }

        // Флаг обработки левого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLB")] public Bool cornerLB_; */
        XmlAttr<Bool> cornerLB{};
        /* public bool _cornerLBSpecified */
        bool isCornerLBSpecified() const { return cornerLB != Bool::off; }

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRB")] public Bool cornerRB_; */
        XmlAttr<Bool> cornerRB{};
        /* public bool _cornerRBSpecified */
        bool isCornerRBSpecified() const { return cornerRB != Bool::off; }

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRT")] public Bool cornerRT_; */
        XmlAttr<Bool> cornerRT{};
        /* public bool _cornerRTSpecified */
        bool isCornerRTSpecified() const { return cornerRT != Bool::off; }

        // Флаг обработки левого верхнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLT")] public Bool cornerLT_; */
        XmlAttr<Bool> cornerLT{};
        /* public bool _cornerLTSpecified */
        bool isCornerLTSpecified() const { return cornerLT != Bool::off; }

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift Shift_; */
        Shift Shift_;
        operator QPainterPath() const { // FIXME addRoundedRect
            QPainterPath path;
            path.addRoundedRect(-width * .5, -height * .5, width, height, handlingValue, handlingValue);
            return path;
        }
    };

    // Описание полигональной контактной площадки.
    struct PadPoly /*: public BasePad {*/ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;

        // Массив координат точек, вершин.
        // <remarks>! Минимум 3 элемента</remarks>
        /* [XmlElement("Dot")] public List<Dot> Dots; */
        std::vector<Dot> Dots;
        operator QPolygonF() const {
            QPolygonF poly;
            poly.reserve(Dots.size());
            for(const auto& dot: Dots) poly.append(dot);
            return poly;
        }

        operator QPainterPath() const {
            QPainterPath path;
            // path.moveTo(Dots.front());
            path.addPolygon(*this);
            return path;
        }
    };

    // Описание стека контактных площадок.
    struct Padstack {
        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;

        // Тип стека контактных площадок.
        /* [XmlAttribute("type")] public type_padstack type_; */
        XmlAttr<type_padstack> type{};

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float holeDiameter_; */
        XmlAttr<float> holeDiameter;

        // Параметр стека контактной площадки: металлизация отверстия.
        /* [XmlAttribute("metallized")] public Bool metallized_; */
        XmlAttr<Bool> metallized{};
        /* public bool _metallizedSpecified */
        bool getMetallizedSpecified() const { return metallized != Bool::off; }

        // Параметр стека контактной площадки: подключение к области металлизации (полигону).
        /* [XmlAttribute("connectToCopper")] public type_connectToCopper connectToCopper_; */
        XmlAttr<type_connectToCopper> connectToCopper{};

        // Описание термобарьера.
        /* [XmlElement("Thermal")] public Thermal Thermal_; */
        Thermal Thermal_;

        // Контактные площадки стека.
        // <value>PadCircle,PadOval,PadRect,PadPoly</value>
        /* [XmlArray("Pads")][XmlArrayItem("PadCircle", typeof(PadCircle)), XmlArrayItem("PadOval", typeof(PadOval)), XmlArrayItem("PadRect", typeof(PadRect)), XmlArrayItem("PadPoly", typeof(PadPoly))] public List<Object> Pads; */
        std::vector<XmlVariant<PadCircle, PadOval, PadRect, PadPoly>> Pads;
        bool ShouldSerialize_Pads() { return Pads.size(); }
    };

    // Описание типа (стека) переходного отверстия.
    struct Viastack {

        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        struct LayerRange {

            // AllLayers - yстанавливает область действия правила: все слои. См. также _LayerRefs
            // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>
            /* [XmlElement("AllLayers", typeof(AllLayers))] public AllLayers AllLayers_; */
            AllLayers AllLayers_;

            // Диапазон слоёв. См. также _AllLayers
            // <remarks>! При null необходимо смотреть наличие AllLayers. </remarks>
            /* [XmlElement("LayerRef", typeof(LayerRef))] public List<LayerRef> LayerRefs; */
            std::vector<LayerRef> LayerRefs;
            bool ShouldSerialize_LayerRefs() { return LayerRefs.size(); }
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float holeDiameter_; */
        XmlAttr<float> holeDiameter;
        float _holeDiameter = 0.0F;

        // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.
        /* [XmlAttribute("viaOnPin")] public Bool viaOnPin_; */
        XmlAttr<Bool> viaOnPin{};
        /* public bool _viaOnPinSpecified */
        bool getViaOnPinSpecified() const { return viaOnPin != Bool::off; }

        // Диапазон слоев.

        // <value>AllLayers | [LayerRef]</value>
        /* [XmlElement("LayerRange", typeof(LayerRange))] public LayerRange LayerRange_; */
        LayerRange LayerRange_;

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
            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;
            float _lineWidth = 0.0F;

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Описание фигуры.
            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
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
                XmlElement("FilledContour", typeof(FilledContour))] public Object Figure_; */
            XmlVariant<ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon, FilledContour>
                Figure_;
        };

        // Описание запрета в посадочном месте Footprint. Для запрета размещения должен быть указан слой с типом Assy.
        struct Keepout_Place_Trace {

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Описание фигуры.

            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
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
                XmlElement("FilledContour", typeof(FilledContour))] public Object Figure_; */
            XmlVariant<ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon, FilledContour> Figure_;
        };

        // Описание монтажного отверстия в посадочном месте.
        struct Mnthole {

            // Идентификатор неименованных объектов.
            /* [XmlAttribute("id")] public string id_; */
            XmlAttr<QString> id;

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef PadstackRef_; */
            PadstackRef PadstackRef_;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org Org_; */
            Org Org_;
        };

        // Описание ярлыка в посадочном месте.
        struct Label_Footprint {

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;

            // Параметр надписей (ярлыков): способ выравнивания текста.
            /* [XmlAttribute("align")] public align align_; */
            XmlAttr<align> align_;

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
            XmlAttr<float> angle;

            // Параметр надписей и ярлыков: зеркальность отображения.
            /* [XmlAttribute("mirror")] public Bool mirror_; */
            XmlAttr<Bool> mirror;
            /* public bool _mirrorSpecified */
            bool getMirrorSpecified() const { return mirror != Bool::off; }

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Ссылка на стиль надписей.
            /* [XmlElement("TextStyleRef")] public TextStyleRef TextStyleRef_; */
            TextStyleRef TextStyleRef_;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org Org_; */
            Org Org_;
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
            /* [XmlAttribute("padNum", DataType = "int")] public int padNum_; */
            XmlAttr<int> padNum;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;

            // Задаёт угол в градусах c точностью до тысячных долей.
            /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
            XmlAttr<float> angle;

            // Параметр контакта (вывода) посадочного места: перевёрнутость.
            // Если флаг не установлен, площадка планарного контакта будет находиться на одной стороне с компонентом,
            // иначе площадка будет расположена на противоположной стороне.
            /* [XmlAttribute("flipped")] public Bool flipped_; */
            XmlAttr<Bool> flipped{};
            /* public bool _flippedSpecified */
            bool getFlippedSpecified() const { return flipped != Bool::off; }

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef PadstackRef_; */
            PadstackRef PadstackRef_;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org Org_; */
            Org Org_;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
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
            /* [XmlAttribute("pinNum", DataType = "int")] public int pinNum_; */
            XmlAttr<int> pinNum;
            int _pinNum = 0;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;

            // Схемотехническое имя контакта компонента.
            /* [XmlAttribute("pinSymName")] public string pinSymName_; */
            XmlAttr<QString> pinSymName;

            // Параметр контакта компонента: эквивалентность.
            /* [XmlAttribute("pinEqual", DataType = "int")] public int pinEqual_; */
            XmlAttr<int> pinEqual;
            int _pinEqual = 0;

            // Параметр контакта (вывода) компонента: номер вентиля контакта.
            /* [XmlAttribute("gate", DataType = "int")] public int gate_; */
            XmlAttr<int> gate;
            int _gate = 0;

            // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
            /* [XmlAttribute("gateEqual", DataType = "int")] public int gateEqual_; */
            XmlAttr<int> gateEqual;
            int _gateEqual = 0;
        };

        // Описание атрибута схемного компонента.
        struct Attribute_Component {

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;

            // Значение атрибута.
            /* [XmlAttribute("value")] public string value_; */
            XmlAttr<QString> value;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
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
            XmlAttr<int> pinNum;

            // Номер контактной площадки (вывода) посадочного места.
            XmlAttr<int> padNum;

            // Параметр правил выравнивания задержек: тип значений констант и допусков.
            /* [XmlAttribute("valueType")] public valueType valueType_; */
            XmlAttr<valueType> valueType_;

            // Параметр контакта компонента в посадочном месте: задержка сигнала в посадочном месте.
            XmlAttr<float> delay;
        };

        // Ссылка на схемный компонент.
        /* [XmlElement("ComponentRef")] public ComponentRef ComponentRef_; */
        ComponentRef ComponentRef_;

        // Ссылка на посадочное место.
        /* [XmlElement("FootprintRef")] public FootprintRef FootprintRef_; */
        FootprintRef FootprintRef_;

        // Соответствие контакта схемного компонента и вывода посадочного места.
        /* [XmlElement("Pinpack")] public List<Pinpack> Pinpacks; */
        std::vector<Pinpack> Pinpacks;
        bool ShouldSerialize_Pinpacks() { return Pinpacks.size(); }
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;

    // Стеки контактных площадок.
    /* [XmlArray("Padstacks")][XmlArrayItem("Padstack")] public List<Padstack> Padstacks; */
    std::vector<Padstack> Padstacks;
    bool ShouldSerialize_Padstacks() { return Padstacks.size(); }

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

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
