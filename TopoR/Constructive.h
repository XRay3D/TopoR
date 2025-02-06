#pragma once
#include "Commons.h"
#include <any>
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
// Описание конструктива платы.
struct Constructive {
    // Описание контура платы и вырезов в плате.
    struct BoardOutline {
#if 0
        struct ShapeContour {
            // Толщина линии.
            // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
            Xml::Attr<double> lineWidth;
            // Незалитая фигура.
            // [Xml::Element(ArcCCW),
            //  Xml::Element(ArcCW),
            //  Xml::Element(ArcByAngle),
            //  Xml::Element(ArcByMiddle),
            //  Xml::Element(Circle),
            //  Xml::Element(Line),
            //  Xml::Element(Polyline),
            //  Xml::Element(Rect),
            //  Xml::Element(Contour)] public Object NonfilledFigure_;
            Xml::Variant<
                ArcCCW,
                ArcCW,
                ArcByAngle,
                ArcByMiddle,
                Circle,
                Line,
                Polyline,
                Rect,
                Contour>
                NonfilledFigure_;
            /*************************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Contour. *
             * Они не являются частью формата TopoR PCB.                             *
             * ***********************************************************************/

            //    void UnitsConvert(dist in_units, dist out_units);
            /*************************************************************************/
        };
        struct ShapeVoids {
            // Толщина линии.
            // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
            Xml::Attr<double> lineWidth;
            // Описание залитой фигуры.
            // [Xml::Element(FilledCircle),
            //  Xml::Element(FilledRect),
            //  Xml::Element(Polygon),
            //  Xml::Element(FilledContour)] public Object FilledFigure_;
            Xml::Variant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/

            //    void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };
        // Описание контура платы.
        // [Xml::Array("Contour")][Xml::ArrayItem("Shape")] public List<Shape_Contour> Contours_;
        Xml::ArrayElem<ShapeContour> Contours;
        // Вырезы в плате.
        // [Xml::Array("Voids")][Xml::ArrayItem("Shape")] public List<Shape_Voids> Voids_;
        Xml::ArrayElem<ShapeVoids> Voids;
#else
        struct Shape {
            // Толщина линии.
            // [Xml::Attribute("lineWidth", DataType = "double")] public double lineWidth_;
            Xml::Attr<double> lineWidth;
            // Незалитая фигура.
            Xml::Variant<
                ArcCCW,      // Contour
                ArcCW,       // Contour
                ArcByAngle,  // Contour
                ArcByMiddle, // Contour
                Circle,      // Contour
                Line,        // Contour
                Polyline,    // Contour
                Rect,        // Contour
                Contour      // Contour
                >
                NonfilledFigure;
            // Описание залитой фигуры.
            Xml::Variant<
                FilledCircle, // Voids
                FilledRect,   // Voids
                Polygon,      // Voids
                FilledContour // Voids
                >
                FilledFigure;
            /*************************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Contour. *
             * Они не являются частью формата TopoR PCB.                             *
             * ***********************************************************************/

            //    void UnitsConvert(dist in_units, dist out_units);
            /*************************************************************************/
        };
        // Описание контура платы.
        // [Xml::Array("Contour")][Xml::ArrayItem("Shape")] public List<Shape_Contour> Contours_;
        Xml::ArrayElem<Shape> Contour_;
        // Вырезы в плате.
        // [Xml::Array("Voids")][Xml::ArrayItem("Shape")] public List<Shape_Voids> Voids_;
        Xml::ArrayElem<Shape> Voids;
#endif
    };
    // Описание монтажного отверстия на плате.
    struct MntholeInstance {
        // Задаёт угол в градусах c точностью до тысячных долей.
        // [Xml::Attribute("angle", DataType = "double")] public double angle_;
        Xml::Attr<double> angle;
        // Признак фиксации.
        // [Xml::Attribute("fixed")] public Bool fixed_;
        Xml::Attr<Bool> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на стек контактных площадок.
        // [Xml::Element("PadstackRef")] public PadstackRef padstackRef;
        PadstackRef padstackRef;
        // ссылка на цепь.
        // [Xml::Element("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Точка привязки объекта.
        // [Xml::Element("Org")] public Org org;
        Org org;

        //    void UnitsConvert(dist in_units, dist out_units);
    };
    // Описание запрета.
    struct Keepout {
        // Тип запрета.
        struct Role {
            // Тип запрета: запрет трассировки.
            struct Trace {
                // Тип запрета трассировки.
                // [Xml::Attribute("role")] public role role_;
                Xml::Attr<role> role_;
                // Ссылка на слои. См. также LayersRefs_
                /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
                // [Xml::Element(AllLayers),
                //  Xml::Element(AllLayersInner),
                //  Xml::Element(AllLayersInnerSignal),
                //  Xml::Element(AllLayersSignal),
                //  Xml::Element(AllLayersOuter),
                //  Xml::Element(LayerGroupRef)] public Object LayersRef_;
                Xml::Variant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef;
                // Ссылка на слои. См. также LayersRef_
                /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
                // [Xml::Element("LayerRef")] public List<LayerRef> LayersRefs_;
                Xml::Array<LayerRef> LayersRefs;
            };
            // Тип запрета: запрет размещения.
            struct Place {
                // Сторона объекта.
                // [Xml::Attribute("side")] public side side_;
                Xml::Attr<side> side_;
            };
            // Тип запрета: запрет трассировки.
            // [Xml::Element(Trace)] public Trace trace;
            Trace trace;
            // [Xml::Element(Place)] public Place place;
            // Place place;
            Xml::Attr<side> Place;
        };
        // [Xml::Element(Role)] public Role role;
        Role role;
        // Описание фигуры.
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
        //  Xml::Element(Contour),
        //  Xml::Element(FilledContour),
        //  Xml::Element(Polyline)] public Object FigureContPolyline_;
        Xml::Variant<ArcCCW,
            ArcCW,
            ArcByAngle,
            ArcByMiddle,
            Line,
            Circle,
            Rect,
            FilledCircle,
            FilledRect,
            Polygon,
            Contour,
            FilledContour,
            Polyline>
            FigureContPolyline_;
        /********************************************************************************
         * Здесь находятся функции для работы с элементами класса Keepout_Сonstructive. *
         * Они не являются частью формата TopoR PCB.                                    *
         * ******************************************************************************/

        //    void UnitsConvert(dist in_units, dist out_units);
        /********************************************************************************/
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Контур платы и вырезы в плате.
    // [Xml::Element("BoardOutline")] public BoardOutline boardOutline;
    BoardOutline boardOutline;
    // Монтажные отверстия на плате.
    // [Xml::Array("Mntholes"), DefaultValue(null)][Xml::ArrayItem("MntholeInstance")] public List<MntholeInstance> Mntholes_;
    Xml::ArrayElem<MntholeInstance> Mntholes;
    // Детали на механических слоях.
    // [Xml::Array("MechLayerObjects"), DefaultValue(null)][Xml::ArrayItem("Detail")] public List<Detail> MechLayerObjects_;
    Xml::ArrayElem<Detail> MechLayerObjects;
    // Описание надписей.
    // [Xml::Array("Texts"), DefaultValue(null)][Xml::ArrayItem("Text")] public List<Text> Texts_;
    Xml::ArrayElem<Text> Texts;
    // Описание запретов.
    // [Xml::Array("Keepouts"), DefaultValue(null)][Xml::ArrayItem("Keepout")] public List<Keepout_Сonstructive> Keepouts_;
    Xml::ArrayElem<Keepout> Keepouts;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Сonstructive. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    //    void UnitsConvert(dist in_units, dist out_units);
    //    void Add(Constructive a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts);
    /************************************************************************/
};
} // namespace TopoR
