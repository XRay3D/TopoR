﻿#pragma once

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

class QGraphicsItemGroup;
namespace TopoR_PCB_Classes {

class TopoR_PCB_File;

// Раздел «Библиотечные элементы». (Обязательный раздел)
struct LocalLibrary {

    // struct BasePad {
    //     // Ссылка на слой или тип слоя.
    //     // <value>LayerTypeRef | LayerRef</value>
    //     /* [XmlElement("LayerTypeRef", typeof(LayerTypeRef)),
    //         XmlElement("LayerRef", typeof(LayerRef))] public Object Reference_; */
    //     XmlVariant<LayerTypeRef, LayerRef> Reference;
    // };

    // Описание круглой контактной площадки.
    struct PadCircle /*: BasePad */ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;
        // Диаметр окружности, круга, овала.
        /* [XmlAttribute("diameter", DataType = "float")] public float diameter_; */
        XmlAttr<float> diameter;
        operator QPainterPath() const;
    };

    // Описание овальной контактной площадки.
    struct PadOval /*: BasePad */ {
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
        operator QPainterPath() const;
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
    struct PadRect /*: BasePad */ {
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
        /* public bool handlingSpecified_ */
        bool isHandlingSpecified() const { return handling != type_handling::None; }

        // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.
        /* [XmlAttribute("handlingValue", DataType = "float")] public float handlingValue_; */
        XmlAttr<float> handlingValue;
        /* public bool handlingValueSpecified_ */
        bool isHandlingValueSpecified() const { return handlingValue != 0; }

        // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.
        /* [XmlAttribute("custom")] public Bool custom_; */
        XmlAttr<Bool> custom{};
        /* public bool customSpecified_ */

        // Флаг обработки левого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLB")] public Bool cornerLB_; */
        XmlAttr<Bool> cornerLB{};
        /* public bool cornerLBSpecified_ */

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRB")] public Bool cornerRB_; */
        XmlAttr<Bool> cornerRB{};
        /* public bool cornerRBSpecified_ */

        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerRT")] public Bool cornerRT_; */
        XmlAttr<Bool> cornerRT{};
        /* public bool cornerRTSpecified_ */

        // Флаг обработки левого верхнего угла прямоугольной контактной площадки.
        /* [XmlAttribute("cornerLT")] public Bool cornerLT_; */
        XmlAttr<Bool> cornerLT{};
        /* public bool cornerLTSpecified_ */

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        /* [XmlElement("Shift")] public Shift Shift_; */
        Shift Shift_;
        operator QPainterPath() const;
    };

    // Описание полигональной контактной площадки.
    struct PadPoly /*: BasePad */ {
        XmlVariant<LayerTypeRef, LayerRef> Reference;

        // Массив координат точек, вершин.
        // <remarks>! Минимум 3 элемента</remarks>
        /* [XmlElement("Dot")] public List<Dot> Dots; */
        std::vector<Dot> Dots;

        operator QPolygonF() const;
        operator QPainterPath() const;
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

        // Параметр стека контактной площадки: подключение к области металлизации (полигону).
        /* [XmlAttribute("connectToCopper")] public type_connectToCopper connectToCopper_; */
        XmlAttr<type_connectToCopper> connectToCopper{};

        // Описание термобарьера.
        /* [XmlElement("Thermal")] public Thermal thermal; */
        Thermal thermal;

        // Контактные площадки стека.
        // <value>PadCircle,PadOval,PadRect,PadPoly</value>
        /* [XmlArray("Pads")][XmlArrayItem("PadCircle", typeof(PadCircle)), XmlArrayItem("PadOval", typeof(PadOval)), XmlArrayItem("PadRect", typeof(PadRect)), XmlArrayItem("PadPoly", typeof(PadPoly))] public List<Object> Pads; */
        std::vector<XmlVariant<PadCircle, PadOval, PadRect, PadPoly>> Pads;
    };

    // Описание типа (стека) переходного отверстия.
    struct Viastack {
        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        struct LayerRange {
            // AllLayers - yстанавливает область действия правила: все слои. См. также LayerRefs_
            // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
            /* [XmlElement("AllLayers", typeof(AllLayers))] public AllLayers AllLayers_; */
            AllLayers AllLayers_;

            // Диапазон слоёв. См. также AllLayers_
            // <remarks>! При null необходимо смотреть наличие AllLayers. </remarks>
            /* [XmlElement("LayerRef", typeof(LayerRef))] public List<LayerRef> LayerRefs; */
            std::vector<LayerRef> LayerRefs;
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;

        // Диаметр отверстия.
        /* [XmlAttribute("holeDiameter", DataType = "float")] public float holeDiameter_; */
        XmlAttr<float> holeDiameter;

        // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.
        /* [XmlAttribute("viaOnPin")] public Bool viaOnPin_; */
        XmlAttr<Bool> viaOnPin;

        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        /* [XmlElement("LayerRange", typeof(LayerRange))] public LayerRange LayerRange_; */
        LayerRange LayerRange_;

        // Описание площадок стека переходного отверстия.
        /* [XmlArray("ViaPads")][XmlArrayItem("PadCircle", typeof(PadCircle))] public List<PadCircle> ViaPads; */
        std::vector<PadCircle> ViaPads;
    };

    // Описание посадочного места.

    struct Footprint {

        // Описание области металлизации (полигона) в посадочном месте компонента.
        struct Copper /*_Footprint*/ {
            // Толщина линии.
            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;

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
            XmlVariant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };

        // Описание запрета в посадочном месте Footprint. Для запрета размещения должен быть указан слой с типом Assy.
        struct Keepout /*_Place_Trace*/ {
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
                XmlElement("FilledContour", typeof(FilledContour))] public Object Figure_;*/
            XmlVariant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };

        // Описание монтажного отверстия в посадочном месте.
        struct Mnthole {
            // Идентификатор неименованных объектов.
            /* [XmlAttribute("id")] public string id_; */
            XmlAttr<QString> id;

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
            PadstackRef padstackRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org org; */
            Org org;
        };

        // Описание ярлыка в посадочном месте.
        struct Label /*_Footprint*/ {
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

            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Ссылка на стиль надписей.
            /* [XmlElement("TextStyleRef")] public TextStyleRef TextStyleRef_; */
            TextStyleRef TextStyleRef_;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org org; */
            Org org;

            QTransform transform() const {
                QTransform transform;
                transform.translate(org.x, org.y);
                transform.rotate(angle);
                return transform;
            }
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

            // Ссылка на стек контактных площадок.
            /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
            PadstackRef padstackRef;

            // Точка привязки объекта.
            /* [XmlElement("Org")] public Org org; */
            Org org;

            QTransform transform() const {
                QTransform transform;
                transform.translate(org.x, org.y);
                transform.rotate(angle);
                return transform;
            }
        };

        // Имя объекта или ссылка на именованный объект.
        /* [XmlAttribute("name")] public string name_; */
        XmlAttr<QString> name;

        // Описание контактных площадок посадочного места.
        /* [XmlArray("Pads")][XmlArrayItem("Pad")] public List<Pad> Pads; */
        std::vector<Pad> Pads;

        // Надписи.
        /* [XmlArray("Texts")][XmlArrayItem("Text")] public List<Text> Texts; */
        std::vector<Text> Texts;

        // Детали посадочного места.
        /* [XmlArray("Details")][XmlArrayItem("Detail")] public List<Detail> Details; */
        std::vector<Detail> Details;

        // Области металлизации (полигонов) в посадочных местах компонентов.
        /* [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Footprint> Coppers; */
        std::vector<Copper> Coppers;

        // Запреты размещения в посадочном месте.
        /* [XmlArray("KeepoutsPlace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsPlace; */
        std::vector<Keepout> KeepoutsPlace;

        // Запреты трассировки в посадочном месте.
        /* [XmlArray("KeepoutsTrace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsTrace; */
        std::vector<Keepout> KeepoutsTrace;

        // Монтажные отверстия.
        /* [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<Mnthole> Mntholes; */
        std::vector<Mnthole> Mntholes;

        // Ярлыки.
        /* [XmlArray("Labels")][XmlArrayItem("Label")] public List<Label_Footprint> Labels; */
        std::vector<Label> Labels;

        QString ToString() { return name; }

        QGraphicsItem* graphicsItem(const TopoR_PCB_File& lib) const;
    };

    // Описание схемного компонента.
    struct Component {

        // Описание контакта схемного компонента.
        struct Pin /*_Component*/ {

            // Номер контакта компонента.
            /* [XmlAttribute("pinNum", DataType = "int")] public int pinNum_; */
            XmlAttr<int> pinNum;

            // Имя объекта или ссылка на именованный объект.
            /* [XmlAttribute("name")] public string name_; */
            XmlAttr<QString> name;

            // Схемотехническое имя контакта компонента.
            /* [XmlAttribute("pinSymName")] public string pinSymName_; */
            XmlAttr<QString> pinSymName;

            // Параметр контакта компонента: эквивалентность.
            /* [XmlAttribute("pinEqual", DataType = "int")] public int pinEqual_; */
            XmlAttr<int> pinEqual;

            // Параметр контакта (вывода) компонента: номер вентиля контакта.
            /* [XmlAttribute("gate", DataType = "int")] public int gate_; */
            XmlAttr<int> gate;

            // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
            /* [XmlAttribute("gateEqual", DataType = "int")] public int gateEqual_; */
            XmlAttr<int> gateEqual;
        };

        // Описание атрибута схемного компонента.
        struct Attribute /*_Component*/ {

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
        std::vector<Pin> Pins;

        // Атрибуты компонента.
        /* [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<Attribute_Component> Attributes; */
        std::vector<Attribute> Attributes;

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
        XmlAarray<Pinpack> Pinpacks;
    };

    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;

    // Стеки контактных площадок.
    /* [XmlArray("Padstacks")][XmlArrayItem("Padstack")] public List<Padstack> Padstacks; */
    std::vector<Padstack> Padstacks;

    // Типы (стеки) переходных отверстий.
    /* [XmlArray("Viastacks")][XmlArrayItem("Viastack")] public List<Viastack> Viastacks; */
    std::vector<Viastack> Viastacks;

    // Посадочные места.
    /* [XmlArray("Footprints")][XmlArrayItem("Footprint")] public List<Footprint> Footprints; */
    std::vector<Footprint> Footprints;

    // Схемные компоненты.
    /* [XmlArray("Components")][XmlArrayItem("Component")] public List<Component> Components; */
    std::vector<Component> Components;

    // Упаковки.
    /* [XmlArray("Packages")][XmlArrayItem("Package")] public List<Package> Packages; */
    std::vector<Package> Packages;

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    static inline std::map<QString, QGraphicsItemGroup*> footprints;

    const Padstack* getPadstack(const QString& name) const;
    const Footprint* getFootprint(const QString& name) const;

    /************************************************************************/
};

} // namespace TopoR_PCB_Classes
