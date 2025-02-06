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
    // [Xml::Element(LayerTypeRef), Xml::Element(LayerRef)] public Object Reference_;
    using BasePadRef = Xml::Variant<LayerTypeRef, LayerRef>;

    // Описание круглой контактной площадки.
    struct PadCircle {
        BasePadRef Reference;
        Xml::Attr<double> diameter; // Диаметр окружности, круга, овала.

        operator QPainterPath() const;
    };
    // Описание овальной контактной площадки.
    struct PadOval {
        BasePadRef Reference;
        Xml::Attr<double> diameter; // Диаметр окружности, круга, овала.

        // Параметр овальной контактной площадки: вытягивание по осям x и y.
        // [Xml::Element("Stretch")] public Stretch stretch;
        Stretch stretch;
        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        // [Xml::Element("Shift")] public Shift shift;
        Xml::Optional<Shift> shift;
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
        Xml::Attr<double> width; // Ширина прямоугольной контактной площадки.

        Xml::Attr<double> height; // Высота прямоугольной контактной площадки.

        Xml::Attr<Handling> handling; // Тип обработки углов прямоугольной контактной площадки.

        Xml::Attr<double> handlingValue; // Величина обработки углов прямоугольной контактной площадки. Значение зависит от типа обработки. Для скругления это радиус. Для среза это высота среза.

        Xml::Attr<Bool> custom; // Флаг выборочной обработки углов прямоугольной контактной площадки. Если не установлен, то все углы обрабатываются одинаковым образом.

        Xml::Attr<Bool> cornerLB; // Флаг обработки левого нижнего угла прямоугольной контактной площадки.

        Xml::Attr<Bool> cornerRB; // Флаг обработки правого нижнего угла прямоугольной контактной площадки.

        Xml::Attr<Bool> cornerRT; // Флаг обработки правого нижнего угла прямоугольной контактной площадки.

        Xml::Attr<Bool> cornerLT; // Флаг обработки левого верхнего угла прямоугольной контактной площадки.

        // Параметр контактной площадки: смещение точки привязки по осям x и y.
        // [Xml::Element("Shift")] public Shift shift;
        Xml::Optional<Shift> shift;
        operator QPainterPath() const;
    };
    // Описание полигональной контактной площадки.
    struct PadPoly {
        BasePadRef Reference;
        // Массив координат точек, вершин.
        /// \note !Минимум 3 элемента
        // [Xml::Element("Dot")] public List<Dot> Dots;
        Xml::Array<Dot> Dots;
        operator QPolygonF() const;
        operator QPainterPath() const;
    };
    // Описание стека контактных площадок.
    struct Padstack {
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        Xml::Attr<type_padstack> type; // Тип стека контактных площадок.

        Xml::Attr<double> holeDiameter; // Диаметр отверстия.

        Xml::Attr<Bool> metallized; // Параметр стека контактной площадки: металлизация отверстия.

        Xml::Attr<ConnectToCopper> connectToCopper; // Параметр стека контактной площадки: подключение к области металлизации (полигону).

        // Описание термобарьера.
        // [Xml::Element("Thermal")] public Thermal thermal;
        Thermal thermal;
        // Контактные площадки стека.
        // <value>PadCircle,PadOval,PadRect,PadPoly</value>
        // [Xml::Array("Pads")][Xml::ArrayItem(PadCircle), Xml::ArrayItem(PadOval), Xml::ArrayItem(PadRect), Xml::ArrayItem(PadPoly)] public List<Object> Pads;
        Xml::ArrayElem<Xml::Variant<PadCircle, PadOval, PadRect, PadPoly>> Pads;

        static QString getReference(const Xml::Variant<PadCircle, PadOval, PadRect, PadPoly>& padShape);
    };
    // Описание типа (стека) переходного отверстия.
    struct Viastack {
        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        struct LayerRange {
            // AllLayers - yстанавливает область действия правила: все слои. См. также LayerRefs_
            /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
            // [Xml::Element(AllLayers)] public AllLayers allLayers;
            AllLayers allLayers;
            // Диапазон слоёв. См. также allLayers
            /// \note !При null необходимо смотреть наличие AllLayers.
            // [Xml::Element(LayerRef)] public List<LayerRef> LayerRefs;
            Xml::Array<LayerRef> LayerRefs; // FIXME maybe Xml::ArrayElem
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        Xml::Attr<double> holeDiameter; // Диаметр отверстия.

        Xml::Attr<Bool> viaOnPin; // Параметр типа переходного отверстия: возможность установить переходное отверстие на контактной площадке.

        // Диапазон слоев.
        // <value>AllLayers | [LayerRef]</value>
        // [Xml::Element(LayerRange)] public LayerRange layerRange;
        LayerRange layerRange;
        // Описание площадок стека переходного отверстия.
        // [Xml::Array("ViaPads")][Xml::ArrayItem(PadCircle)] public List<PadCircle> ViaPads;
        Xml::ArrayElem<PadCircle> ViaPads;
    };
    // Описание посадочного места.
    struct Footprint {
        // Описание области металлизации (полигона) в посадочном месте компонента.
        struct Copper /*_Footprint*/ {
            Xml::Attr<double> lineWidth; // Толщина линии.

            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Описание фигуры.
            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
            // [Xml::Element(ArcCCW),
            //  Xml::Element(ArcCW),
            //  Xml::Element(ArcByAngle),
            //  Xml::Element(ArcByMiddle),
            //  Xml::Element(Line),
            //  Xml::Element(Circle),
            //  Xml::Element(Rect),
            //  Xml::Element(FilledCircle),
            //  Xml::Element(FilledRect),
            //  Xml::Element(Polygon),
            //  Xml::Element(FilledContour)] public Object Figure_;
            Xml::Variant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };
        // Описание запрета в посадочном месте Footprint. Для запрета размещения должен быть указан слой с типом Assy.
        struct Keepout /*_Place_Trace*/ {
            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Описание фигуры.
            // <value>ArcCCW,ArcCW,ArcByAngle,ArcByMiddle,Line,Circle,Rect,FilledCircle,FilledRect,Polygon</value>
            // [Xml::Element(ArcCCW),
            //  Xml::Element(ArcCW),
            //  Xml::Element(ArcByAngle),
            //  Xml::Element(ArcByMiddle),
            //  Xml::Element(Line),
            //  Xml::Element(Circle),
            //  Xml::Element(Rect),
            //  Xml::Element(FilledCircle),
            //  Xml::Element(FilledRect),
            //  Xml::Element(Polygon),
            //  Xml::Element(FilledContour)] public Object Figure_;*/
            Xml::Variant<ArcCW, ArcCCW, ArcByAngle, ArcByMiddle, FilledRect, Rect, Polygon, Line, FilledCircle, Circle, FilledContour> Figure_;
        };
        // Описание монтажного отверстия в посадочном месте.
        struct Mnthole {
            Xml::Attr<QString> id; // Идентификатор неименованных объектов.

            // Ссылка на стек контактных площадок.
            // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Точка привязки объекта.
            // [Xml::Element("Org")] public Org org;
            Org org;
        };
        // Описание ярлыка в посадочном месте.
        struct Label /*_Footprint*/ {
            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            Xml::Attr<align> align_; // Параметр надписей (ярлыков): способ выравнивания текста.
            Xml::Attr<double> angle; // Задаёт угол в градусах c точностью до тысячных долей.
            Xml::Attr<Bool> mirror;  // Параметр надписей и ярлыков: зеркальность отображения.

            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Ссылка на стиль надписей.
            // [Xml::Element("TextStyleRef")] public TextStyleRef textStyleRef;
            TextStyleRef textStyleRef;
            // Точка привязки объекта.
            // [Xml::Element("Org")] public Org org;
            Xml::Optional<Org> org;
            QTransform transform() const {
                QTransform transform;
                if(org)
                    transform.translate(org.value().x, org.value().y);
                if(angle)
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
            Xml::Attr<int> padNum; // Номер контактной площадки (вывода) посадочного места.

            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            Xml::Attr<double> angle; // Задаёт угол в градусах c точностью до тысячных долей.

            // Параметр контакта (вывода) посадочного места: перевёрнутость.
            // Если флаг не установлен, площадка планарного контакта будет находиться на одной стороне с компонентом,
            Xml::Attr<Bool> flipped; // иначе площадка будет расположена на противоположной стороне.

            // Ссылка на стек контактных площадок.
            // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
            PadstackRef padstackRef;
            // Точка привязки объекта.
            // [Xml::Element("Org")] public Org org;
            Org org;
            QTransform transform() const {
                QTransform transform;
                transform.translate(org.x, org.y);
                if(angle) transform.rotate(angle);
                return transform;
            }
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Описание контактных площадок посадочного места.
        // [Xml::Array("Pads")][Xml::ArrayItem("Pad")] public List<Pad> Pads;
        Xml::ArrayElem<Pad> Pads;
        // Надписи.
        // [Xml::Array("Texts")][Xml::ArrayItem("Text")] public List<Text> Texts;
        Xml::ArrayElem<Text> Texts;
        // Детали посадочного места.
        // [Xml::Array("Details")][Xml::ArrayItem("Detail")] public List<Detail> Details;
        Xml::ArrayElem<Detail> Details;
        // Области металлизации (полигонов) в посадочных местах компонентов.
        // [Xml::Array("Coppers")][Xml::ArrayItem("Copper")] public List<Copper_Footprint> Coppers;
        Xml::ArrayElem<Copper> Coppers;
        // Запреты размещения в посадочном месте.
        // [Xml::Array("KeepoutsPlace")][Xml::ArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsPlace;
        Xml::ArrayElem<Keepout> KeepoutsPlace;
        // Запреты трассировки в посадочном месте.
        // [Xml::Array("KeepoutsTrace")][Xml::ArrayItem("Keepout")] public List<Keepout_Place_Trace> KeepoutsTrace;
        Xml::ArrayElem<Keepout> KeepoutsTrace;
        // Монтажные отверстия.
        // [Xml::Array("Mntholes")][Xml::ArrayItem("Mnthole")] public List<Mnthole> Mntholes;
        Xml::ArrayElem<Mnthole> Mntholes;
        // Ярлыки.
        // [Xml::Array("Labels")][Xml::ArrayItem("Label")] public List<Label_Footprint> Labels;
        Xml::ArrayElem<Label> Labels;

        QGraphicsItem* graphicsItem(const TopoR_PCB_File& file) const;
    };
    // Описание схемного компонента.
    struct Component {
        // Описание контакта схемного компонента.
        struct Pin /*_Component*/ {
            Xml::Attr<int> pinNum; // Номер контакта компонента.

            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            Xml::Attr<QString> pinSymName; // Схемотехническое имя контакта компонента.

            Xml::Attr<int, NoOpt> pinEqual; // Параметр контакта компонента: эквивалентность.

            Xml::Attr<int, NoOpt> gate; // Параметр контакта (вывода) компонента: номер вентиля контакта.

            Xml::Attr<int, NoOpt> gateEqual; // Параметр контакта (вывода) компонента: эквивалентность вентиля контакта.
        };
        // Описание атрибута схемного компонента.
        struct Attribute /*_Component*/ {
            // Имя объекта или ссылка на именованный объект.
            Xml::Attr<QString> name;
            Xml::Attr<QString> value; // Значение атрибута.
        };
        // Имя объекта или ссылка на именованный объект.
        Xml::Attr<QString> name;
        // Контакты схемного компонента.
        // [Xml::Array("Pins")][Xml::ArrayItem("Pin")] public List<Pin_Component> Pins;
        Xml::ArrayElem<Pin> Pins;
        // Атрибуты компонента.
        // [Xml::Array("Attributes")][Xml::ArrayItem("Attribute")] public List<Attribute_Component> Attributes;
        Xml::ArrayElem<Attribute> Attributes;
        QString ToString() { return name; }
    };
    // Описание упаковки (соответствие контактов компонента и выводов посадочного места).
    struct Package {
        // Соответствие контакта схемного компонента и вывода посадочного места.
        struct Pinpack {
            // Номер контакта компонента.
            Xml::Attr<int> pinNum;
            // Номер контактной площадки (вывода) посадочного места.
            Xml::Attr<int> padNum;
            Xml::Attr<valueType> valueType_; // Параметр правил выравнивания задержек: тип значений констант и допусков.

            // Параметр контакта компонента в посадочном месте: задержка сигнала в посадочном месте.
            Xml::Attr<double> delay;
        };
        // Ссылка на схемный компонент.
        // [Xml::Element("ComponentRef")] public ComponentRef componentRef;
        ComponentRef componentRef;
        // Ссылка на посадочное место.
        // [Xml::Element("FootprintRef")] public FootprintRef footprintRef;
        FootprintRef footprintRef;
        // Соответствие контакта схемного компонента и вывода посадочного места.
        // [Xml::Element("Pinpack")] public List<Pinpack> Pinpacks;
        Xml::Array<Pinpack> Pinpacks;
    };
    Xml::Attr<QString> version; // Версия раздела.

    // Стеки контактных площадок.
    // [Xml::Array("Padstacks")][Xml::ArrayItem("Padstack")] public List<Padstack> Padstacks;
    Xml::ArrayElem<Padstack> Padstacks;
    //  Типы (стеки) переходных отверстий.
    // [Xml::Array("Viastacks")][Xml::ArrayItem("Viastack")] public List<Viastack> Viastacks;
    Xml::ArrayElem<Viastack> Viastacks;
    // Посадочные места.
    // [Xml::Array("Footprints")][Xml::ArrayItem("Footprint")] public List<Footprint> Footprints;
    Xml::ArrayElem<Footprint> Footprints;
    // Схемные компоненты.
    // [Xml::Array("Components")][Xml::ArrayItem("Component")] public List<Component> Components;
    Xml::ArrayElem<Component> Components;
    // Упаковки.
    // [Xml::Array("Packages")][Xml::ArrayItem("Package")] public List<Package> Packages;
    Xml::ArrayElem<Package> Packages;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса LocalLibrary. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    mutable Xml::Skip<std::map<QString, QGraphicsItemGroup*>> footprints;
    const Padstack* getPadstack(const QString& name) const;
    const Footprint* getFootprint(const QString& name) const;
    const Component* getComponent(const QString& name) const;
    const Viastack* getViastack(const QString& name) const;
    /************************************************************************/
};
} // namespace TopoR
