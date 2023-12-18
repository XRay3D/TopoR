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

class QGraphicsItemGroup;
namespace TopoR {
class TopoR_PCB_File;
// Раздел «Библиотечные элементы». (Обязательный раздел)
struct LocalLibrary {
    // Ссылка на слой или тип слоя.
    // <value>LayerTypeRef | LayerRef</value>
    // [XmlElement(LayerTypeRef), XmlElement(LayerRef)] public Object Reference_;
    using BasePadRef = XmlVariant<LayerTypeRef, LayerRef>;

    // Описание круглой контактной площадки.
    struct PadCircle {
        BasePadRef Reference;
        // Диаметр окружности, круга, овала.
        // [XmlAttribute("diameter", DataType = "float")] public float diameter_;
        XmlAttr<float> diameter;
        operator QPainterPath() const;
    };
    // Описание овальной контактной площадки.
    struct PadOval {
        BasePadRef Reference;
        // Диаметр окружности, круга, овала.
        // [XmlAttribute("diameter", DataType = "float")] public float diameter_;
        XmlAttr<float> diameter;
        // Параметр овальной контактной площадки: вытягивание по осям x и y.
        // [XmlElement("Stretch")] public Stretch stretch;
        Stretch stretch;
        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        // [XmlElement("Shift")] public Shift shift;
        Shift shift;
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
    struct PadRect {
        BasePadRef Reference;
        // Ширина прямоугольной контактной площадки.
        // [XmlAttribute("width", DataType = "float")] public float width_;
        XmlAttr<float> width;
        // Высота прямоугольной контактной площадки.
        // [XmlAttribute("height", DataType = "float")] public float height_;
        XmlAttr<float> height;
        // Тип обработки углов прямоугольной контактной площадки.
        // [XmlAttribute("handling")] public Handling handling_;
        XmlAttr<Handling> handling;
        /* public bool handlingSpecified_ */
        bool isHandlingSpecified() const { return handling != Handling::None; }
        // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.
        // [XmlAttribute("handlingValue", DataType = "float")] public float handlingValue_;
        XmlAttr<float> handlingValue;
        /* public bool handlingValueSpecified_ */
        bool isHandlingValueSpecified() const { return handlingValue != 0; }
        // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.
        // [XmlAttribute("custom")] public Bool custom_;
        XmlAttr<Bool> custom;
        /* public bool customSpecified_ */
        // Флаг обработки левого нижнего угла прямоугольной контактной площадки.
        // [XmlAttribute("cornerLB")] public Bool cornerLB_;
        XmlAttr<Bool> cornerLB;
        /* public bool cornerLBSpecified_ */
        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        // [XmlAttribute("cornerRB")] public Bool cornerRB_;
        XmlAttr<Bool> cornerRB;
        /* public bool cornerRBSpecified_ */
        // Флаг обработки правого нижнего угла прямоугольной контактной площадки.
        // [XmlAttribute("cornerRT")] public Bool cornerRT_;
        XmlAttr<Bool> cornerRT;
        /* public bool cornerRTSpecified_ */
        // Флаг обработки левого верхнего угла прямоугольной контактной площадки.
        // [XmlAttribute("cornerLT")] public Bool cornerLT_;
        XmlAttr<Bool> cornerLT;
        /* public bool cornerLTSpecified_ */
        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        // [XmlElement("Shift")] public Shift shift;
        Shift shift; // NOTE maybe optional
        operator QPainterPath() const;
    };
    // Описание полигональной контактной площадки.
    struct PadPoly {
        BasePadRef Reference;
        // Массив координат точек, вершин.
        /// \note !Минимум 3 элемента
        // [XmlElement("Dot")] public List<Dot> Dots;
        XmlArray<Dot> Dots;
        operator QPolygonF() const;
        operator QPainterPath() const;
    };
    // Описание стека контактных площадок.
    struct Padstack {
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Тип стека контактных площадок.
        // [XmlAttribute("type")] public type_padstack type_;
        XmlAttr<type_padstack> type;
        // Диаметр отверстия.
        // [XmlAttribute("holeDiameter", DataType = "float")] public float holeDiameter_;
        XmlAttr<float> holeDiameter;
        // Параметр стека контактной площадки: металлизация отверстия.
        // [XmlAttribute("metallized")] public Bool metallized_;
        XmlAttr<Bool> metallized;
        // Параметр стека контактной площадки: подключение к области металлизации (полигону).
        // [XmlAttribute("connectToCopper")] public ConnectToCopper connectToCopper_;
        XmlAttr<ConnectToCopper> connectToCopper;
        // Описание термобарьера.
        // [XmlElement("Thermal")] public Thermal thermal;
        Thermal thermal;
        // Контактные площадки стека.
        // <value>PadCircle,PadOval,PadRect,PadPoly</value>
        // [XmlArray("Pads")][XmlArrayItem(PadCircle), XmlArrayItem(PadOval), XmlArrayItem(PadRect), XmlArrayItem(PadPoly)] public List<Object> Pads;
        XmlArrayElem<XmlVariant<PadCircle, PadOval, PadRect, PadPoly>> Pads;

       static QString getReference(const XmlVariant<PadCircle, PadOval, PadRect, PadPoly>& padShape) ;
    };
    // Описание типа (стека) переходного отверстия.
    struct Viastack {
        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        struct LayerRange {
            // AllLayers - yстанавливает область действия правила: все слои. См. также LayerRefs_
            /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
            // [XmlElement(AllLayers)] public AllLayers allLayers;
            AllLayers allLayers;
            // Диапазон слоёв. См. также allLayers
            /// \note !При null необходимо смотреть наличие AllLayers.
            // [XmlElement(LayerRef)] public List<LayerRef> LayerRefs;
            XmlArray<LayerRef> LayerRefs; // FIXME maybe XmlArrayElem
        };
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Диаметр отверстия.
        // [XmlAttribute("holeDiameter", DataType = "float")] public float holeDiameter_;
        XmlAttr<float> holeDiameter;
        // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.
        // [XmlAttribute("viaOnPin")] public Bool viaOnPin_;
        XmlAttr<Bool> viaOnPin;
        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        // [XmlElement(LayerRange)] public LayerRange layerRange;
        LayerRange layerRange;
        // Описание площадок стека переходного отверстия.
        // [XmlArray("ViaPads")][XmlArrayItem(PadCircle)] public List<PadCircle> ViaPads;
        XmlArrayElem<PadCircle> ViaPads;
    };
    // Описание посадочного места.
    struct Footprint {
        // Описание области металлизации (полигона) в посадочном месте компонента.
        struct Copper /*_Footprint*/ {
            // Толщина линии.
            // [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_;
            XmlAttr<float> lineWidth;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Описание фигуры.
            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
            // [XmlElement(ArcCCW),
            //  XmlElement(ArcCW),
            //  XmlElement(ArcByAngle),
            //  XmlElement(ArcByMiddle),
            //  XmlElement(Line),
            //  XmlElement(Circle),
            //  XmlElement(Rect),
            //  XmlElement(FilledCircle),
            //  XmlElement(FilledRect),
            //  XmlElement(Polygon),
            //  XmlElement(FilledContour)] public Object Figure_;
            XmlVariant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };
        // Описание запрета в посадочном месте Footprint. Для запрета размещения должен быть указан слой с типом Assy.
        struct Keepout /*_Place_Trace*/ {
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Описание фигуры.
            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
            // [XmlElement(ArcCCW),
            //  XmlElement(ArcCW),
            //  XmlElement(ArcByAngle),
            //  XmlElement(ArcByMiddle),
            //  XmlElement(Line),
            //  XmlElement(Circle),
            //  XmlElement(Rect),
            //  XmlElement(FilledCircle),
            //  XmlElement(FilledRect),
            //  XmlElement(Polygon),
            //  XmlElement(FilledContour)] public Object Figure_;*/
            XmlVariant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };
        // Описание монтажного отверстия в посадочном месте.
        struct Mnthole {
            // Идентификатор неименованных объектов.
            // [XmlAttribute("id")] public string id_;
            XmlAttr<QString> id;
            // Ссылка на стек контактных площадок.
            // [XmlElement("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Точка привязки объекта.
            // [XmlElement("Org")] public Org org;
            Org org;
        };
        // Описание ярлыка в посадочном месте.
        struct Label /*_Footprint*/ {
            // Имя объекта или ссылка на именованный объект.
            XmlAttr<QString> name;
            // Параметр надписей (ярлыков): способ выравнивания текста.
            // [XmlAttribute("align")] public align align;
            XmlAttr<align> align_;
            // Задаёт угол в градусах c точностью до тысячных долей.
            // [XmlAttribute("angle", DataType = "float")] public float angle_;
            XmlAttr<float> angle;
            // Параметр надписей и ярлыков: зеркальность отображения.
            // [XmlAttribute("mirror")] public Bool mirror_;
            XmlAttr<Bool> mirror;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Ссылка на стиль надписей.
            // [XmlElement("TextStyleRef")] public TextStyleRef textStyleRef;
            TextStyleRef textStyleRef;
            // Точка привязки объекта.
            // [XmlElement("Org")] public Org org;
            Org org;
            QTransform transform() const {
                QTransform transform;
                transform.translate(org.x, org.y);
                transform.rotate(angle);
                return transform;
            }
        };
        // Описание контактной площадки (вывода) посадочного места.
        /// \note !В системе TopoR поддерживаются планарные контакты на внешних металлических слоях и не поддерживаются на внутренних.
        /// \note Т.е.у планарного контакта может быть только одна площадка или на верхней стороне, или на нижней.
        /// \note В описании планарного контакта используется только слой Top.
        /// \note Это означает, что контактная площадка будет находиться на одной стороне с компонентом.
        /// \note Если же площадка находится на противоположной стороне, то должен быть установлен флаг flipped.
        /// \note Этот флаг устанавливается в описании контакта посадочного места.
        struct Pad {
            // Номер контактной площадки (вывода) посадочного места.
            // [XmlAttribute("padNum", DataType = "int")] public int padNum_;
            XmlAttr<int> padNum;
            // Имя объекта или ссылка на именованный объект.
            XmlAttr<QString> name;
            // Задаёт угол в градусах c точностью до тысячных долей.
            // [XmlAttribute("angle", DataType = "float")] public float angle_;
            XmlAttr<float> angle;
            // Параметр контакта (вывода) посадочного места: перевёрнутость.
            // Если флаг не установлен, площадка планарного контакта будет находиться на одной стороне с компонентом,
            // иначе площадка будет расположена на противоположной стороне.
            // [XmlAttribute("flipped")] public Bool flipped_;
            XmlAttr<Bool> flipped;
            // Ссылка на стек контактных площадок.
            // [XmlElement("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Точка привязки объекта.
            // [XmlElement("Org")] public Org org;
            Org org;
            QTransform transform() const {
                QTransform transform;
                transform.translate(org.x, org.y);
                transform.rotate(angle);
                return transform;
            }
        };
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Описание контактных площадок посадочного места.
        // [XmlArray("Pads")][XmlArrayItem("Pad")] public List<Pad> Pads;
        XmlArrayElem<Pad> Pads;
        // Надписи.
        // [XmlArray("Texts")][XmlArrayItem("Text")] public List<Text> Texts;
        XmlArrayElem<Text> Texts;
        // Детали посадочного места.
        // [XmlArray("Details")][XmlArrayItem("Detail")] public List<Detail> Details;
        XmlArrayElem<Detail> Details;
        // Области металлизации (полигонов) в посадочных местах компонентов.
        // [XmlArray("Coppers")][XmlArrayItem("Copper")] public List<Copper_Footprint> Coppers;
        XmlArrayElem<Copper> Coppers;
        // Запреты размещения в посадочном месте.
        // [XmlArray("KeepoutsPlace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsPlace;
        XmlArrayElem<Keepout> KeepoutsPlace;
        // Запреты трассировки в посадочном месте.
        // [XmlArray("KeepoutsTrace")][XmlArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsTrace;
        XmlArrayElem<Keepout> KeepoutsTrace;
        // Монтажные отверстия.
        // [XmlArray("Mntholes")][XmlArrayItem("Mnthole")] public List<Mnthole> Mntholes;
        XmlArrayElem<Mnthole> Mntholes;
        // Ярлыки.
        // [XmlArray("Labels")][XmlArrayItem("Label")] public List<Label_Footprint> Labels;
        XmlArrayElem<Label> Labels;

        QGraphicsItem* graphicsItem(const TopoR_PCB_File& file) const;
    };
    // Описание схемного компонента.
    struct Component {
        // Описание контакта схемного компонента.
        struct Pin /*_Component*/ {
            // Номер контакта компонента.
            // [XmlAttribute("pinNum", DataType = "int")] public int pinNum_;
            XmlAttr<int> pinNum;
            // Имя объекта или ссылка на именованный объект.
            XmlAttr<QString> name;
            // Схемотехническое имя контакта компонента.
            // [XmlAttribute("pinSymName")] public string pinSymName_;
            XmlAttr<QString> pinSymName;
            // Параметр контакта компонента: эквивалентность.
            // [XmlAttribute("pinEqual", DataType = "int")] public int pinEqual_;
            XmlAttr<int> pinEqual;
            // Параметр контакта (вывода) компонента: номер вентиля контакта.
            // [XmlAttribute("gate", DataType = "int")] public int gate_;
            XmlAttr<int> gate;
            // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
            // [XmlAttribute("gateEqual", DataType = "int")] public int gateEqual_;
            XmlAttr<int> gateEqual;
        };
        // Описание атрибута схемного компонента.
        struct Attribute /*_Component*/ {
            // Имя объекта или ссылка на именованный объект.
            XmlAttr<QString> name;
            // Значение атрибута.
            // [XmlAttribute("value")] public string value_;
            XmlAttr<QString> value;
        };
        // Имя объекта или ссылка на именованный объект.
        XmlAttr<QString> name;
        // Контакты схемного компонента.
        // [XmlArray("Pins")][XmlArrayItem("Pin")] public List<Pin_Component> Pins;
        XmlArrayElem<Pin> Pins;
        // Атрибуты компонента.
        // [XmlArray("Attributes")][XmlArrayItem("Attribute")] public List<Attribute_Component> Attributes;
        XmlArrayElem<Attribute> Attributes;
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
            // [XmlAttribute("valueType")] public valueType valueType_;
            XmlAttr<valueType> valueType_;
            // Параметр контакта компонента в посадочном месте: задержка сигнала в посадочном месте.
            XmlAttr<float> delay;
        };
        // Ссылка на схемный компонент.
        // [XmlElement("ComponentRef")] public ComponentRef componentRef;
        ComponentRef componentRef;
        // Ссылка на посадочное место.
        // [XmlElement("FootprintRef")] public FootprintRef footprintRef;
        FootprintRef footprintRef;
        // Соответствие контакта схемного компонента и вывода посадочного места.
        // [XmlElement("Pinpack")] public List<Pinpack> Pinpacks;
        XmlArray<Pinpack> Pinpacks;
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Стеки контактных площадок.
    // [XmlArray("Padstacks")][XmlArrayItem("Padstack")] public List<Padstack> Padstacks;
    XmlArrayElem<Padstack> Padstacks;
    //  Типы (стеки) переходных отверстий.
    // [XmlArray("Viastacks")][XmlArrayItem("Viastack")] public List<Viastack> Viastacks;
    XmlArrayElem<Viastack> Viastacks;
    // Посадочные места.
    // [XmlArray("Footprints")][XmlArrayItem("Footprint")] public List<Footprint> Footprints;
    XmlArrayElem<Footprint> Footprints;
    // Схемные компоненты.
    // [XmlArray("Components")][XmlArrayItem("Component")] public List<Component> Components;
    XmlArrayElem<Component> Components;
    // Упаковки.
    // [XmlArray("Packages")][XmlArrayItem("Package")] public List<Package> Packages;
    XmlArrayElem<Package> Packages;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    static inline std::map<QString, QGraphicsItemGroup*> footprints;
    const Padstack* getPadstack(const QString& name) const;
    const Footprint* getFootprint(const QString& name) const;
    const Component* getComponent(const QString& name) const;
    const Viastack* getViastack(const QString& name) const;
    /************************************************************************/
};
} // namespace TopoR
