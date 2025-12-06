#pragma once
#include "Commons.h"
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Описание конструктива платы.
struct Constructive {
    // Описание контура платы и вырезов в плате.
    struct BoardOutline {
        struct Shape {
            // Толщина линии.
            [[= XML::Attr]] float lineWidth{};
            // Незалитая фигура.
            // public Object NonfilledFigure;
            [[= XML::Elem]] std::variant<ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Circle, Line, Polyline, Rect, Contour> NonfilledFigure;
            /*************************************************************************
             * Здесь находятся функции для работы с элементами класса Shape. *
             * Они не являются частью формата TopoR PCB.                             *
             * ***********************************************************************/
            void Shift(float x, float y);
            void UnitsConvert(dist in_units, dist out_units);
            /*************************************************************************/
        };
        struct Shape_Voids {
            // Толщина линии.
            [[= XML::Attr]] float lineWidth{};
            // Описание залитой фигуры.
            // public Object FilledFigure;
            [[= XML::Elem]] std::variant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure;
            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/
            void Shift(float x, float y);
            void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };
        // Описание контура платы.
        //[XmlArrayItem("Shape")] public List<Shape> Contours;
        [[= XML::Array]] std::vector<Shape> Contour;
        bool ShouldSerialize_Contours();
        // Вырезы в плате.
        //[XmlArrayItem("Shape")] public List<Shape_Voids> Voids;
        [[= XML::Array]] std::vector<Shape_Voids> Voids;
        bool ShouldSerialize_Voids();
    };
    // Описание монтажного отверстия на плате.
    struct MntholeInstance {
        // Задаёт угол в градусах c точностью до тысячных долей.
        [[= XML::Attr]] float angle{};
        // Признак фиксации.
        [[= XML::Attr]] Bool fixed{};
        // public bool fixedSpecified
        bool getFixedSpecified() const;
        // Ссылка на стек контактных площадок.
        [[= XML::Elem("PadstackRef")]] PadstackRef PadstackRef;
        // ссылка на цепь.
        [[= XML::Elem("NetRef")]] NetRef NetRef;
        // Точка привязки объекта.
        [[= XML::Elem("Org")]] Org Org;
        void Shift(float x, float y);
        void UnitsConvert(dist in_units, dist out_units);
    };
    // Описание запрета.
    struct Keepout_Сonstructive {
        // Тип запрета.
        struct Role {
            // <summary>           // Тип запрета: запрет трассировки.
            struct Trace {
                // Тип запрета трассировки.
                [[= XML::Attr("role")]] role role{};
                // Ссылка на слои. См. также LayersRefs
                // ! При null необходимо смотреть LayersRefs - там описан список ссылок типа LayerRef.
                // public Object LayersRef;
                [[= XML::Elem]] std::variant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef;
                // Ссылка на слои. См. также LayersRef
                // ! При null необходимо смотреть LayersRef - там описаны ссылки остальных типов.
                //[[= XML::Elem("LayerRef")]] // public List<LayerRef> LayersRefs;
                [[= XML::Elem("LayerRef")]] std::vector<LayerRef> LayersRefs;
                bool ShouldSerialize_LayersRefs();
            };
            // Тип запрета: запрет размещения.
            struct Place {
                // Сторона объекта.
                [[= XML::Attr("side")]] side side{};
            };
            // Тип запрета: запрет трассировки.
            // ORIGINAL LINE XmlElement: [Trace] public Trace Trace;
            Trace Trace;
            // ORIGINAL LINE XmlElement: [Place] public Place Place;
            Place Place;
        };
        // ORIGINAL LINE XmlElement: [Role] public Role Role;
        Role Role;
        // Описание фигуры.
        // public Object FigureContPolyline;
        [[= XML::Elem]] std::variant<ArcCCW, ArcCW, ArcByAngle, ArcByMiddle, Line, Circle, Rect, FilledCircle, FilledRect, Polygon, Contour, FilledContour, Polyline> FigureContPolyline;
        /********************************************************************************
         * Здесь находятся функции для работы с элементами класса Keepout_Сonstructive. *
         * Они не являются частью формата TopoR PCB.                                    *
         * ******************************************************************************/
        void Shift(float x, float y);
        void UnitsConvert(dist in_units, dist out_units);
        /********************************************************************************/
    };
    // Версия раздела.
    [[= XML::Attr]] std::string version;
    // Контур платы и вырезы в плате.
    [[= XML::Elem("BoardOutline")]] BoardOutline BoardOutline;
    // Монтажные отверстия на плате.
    // ORIGINAL LINE: ("Mntholes"), DefaultValue(null)][XmlArrayItem("MntholeInstance")] public List<MntholeInstance> Mntholes;
    [[= XML::Array]] std::vector<MntholeInstance> Mntholes;
    bool ShouldSerialize_Mntholes();
    // Детали на механических слоях.
    // ORIGINAL LINE: ("MechLayerObjects"), DefaultValue(null)][XmlArrayItem("Detail")] public List<Detail> MechLayerObjects;
    [[= XML::Array]] std::vector<Detail> MechLayerObjects;
    bool ShouldSerialize_MechLayerObjects();
    // Описание надписей.
    // ORIGINAL LINE: ("Texts"), DefaultValue(null)][XmlArrayItem("Text")] public List<Text> Texts;
    [[= XML::Array]] std::vector<Text> Texts;
    bool ShouldSerialize_Texts();
    // Описание запретов.
    // ORIGINAL LINE: ("Keepouts"), DefaultValue(null)][XmlArrayItem("Keepout")] public List<Keepout_Сonstructive> Keepouts;
    [[= XML::Array]] std::vector<Keepout_Сonstructive> Keepouts;
    bool ShouldSerialize_Keepouts();
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Сonstructive. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    void Shift(float x, float y);
    void UnitsConvert(dist in_units, dist out_units);
    void Add(Constructive a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts);
    /************************************************************************/
};
} // namespace TopoR
