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
            // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
            XmlAttr<double> lineWidth;
            // Незалитая фигура.
            // [XmlElement(ArcCCW),
            //  XmlElement(ArcCW),
            //  XmlElement(ArcByAngle),
            //  XmlElement(ArcByMiddle),
            //  XmlElement(Circle),
            //  XmlElement(Line),
            //  XmlElement(Polyline),
            //  XmlElement(Rect),
            //  XmlElement(Contour)] public Object NonfilledFigure_;
            XmlVariant<
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
            // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
            XmlAttr<double> lineWidth;
            // Описание залитой фигуры.
            // [XmlElement(FilledCircle),
            //  XmlElement(FilledRect),
            //  XmlElement(Polygon),
            //  XmlElement(FilledContour)] public Object FilledFigure_;
            XmlVariant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/

            //    void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };
        // Описание контура платы.
        // [XmlArray("Contour")][XmlArrayItem("Shape")] public List<Shape_Contour> Contours_;
        XmlArrayElem<ShapeContour> Contours;
        // Вырезы в плате.
        // [XmlArray("Voids")][XmlArrayItem("Shape")] public List<Shape_Voids> Voids_;
        XmlArrayElem<ShapeVoids> Voids;
#else
        struct Shape {
            // Толщина линии.
            // [XmlAttribute("lineWidth", DataType = "double")] public double lineWidth_;
            XmlAttr<double> lineWidth;
            // Незалитая фигура.
            XmlVariant<
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
            XmlVariant<
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
        // [XmlArray("Contour")][XmlArrayItem("Shape")] public List<Shape_Contour> Contours_;
        XmlArrayElem<Shape> Contour_;
        // Вырезы в плате.
        // [XmlArray("Voids")][XmlArrayItem("Shape")] public List<Shape_Voids> Voids_;
        XmlArrayElem<Shape> Voids;
#endif
    };
    // Описание монтажного отверстия на плате.
    struct MntholeInstance {
        // Задаёт угол в градусах c точностью до тысячных долей.
        // [XmlAttribute("angle", DataType = "double")] public double angle_;
        XmlAttr<double> angle;
        // Признак фиксации.
        // [XmlAttribute("fixed")] public Bool fixed_;
        XmlAttr<Bool> fixed;
        /* public bool fixedSpecified_ */
        // Ссылка на стек контактных площадок.
        // [XmlElement("PadstackRef")] public PadstackRef padstackRef;
        PadstackRef padstackRef;
        // ссылка на цепь.
        // [XmlElement("NetRef")] public NetRef netRef;
        NetRef netRef;
        // Точка привязки объекта.
        // [XmlElement("Org")] public Org org;
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
                // [XmlAttribute("role")] public role role_;
                XmlAttr<role> role_;
                // Ссылка на слои. См. также LayersRefs_
                /// \note !При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef.
                // [XmlElement(AllLayers),
                //  XmlElement(AllLayersInner),
                //  XmlElement(AllLayersInnerSignal),
                //  XmlElement(AllLayersSignal),
                //  XmlElement(AllLayersOuter),
                //  XmlElement(LayerGroupRef)] public Object LayersRef_;
                XmlVariant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef_;
                // Ссылка на слои. См. также LayersRef_
                /// \note !При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов.
                // [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_;
                XmlArrayElem<LayerRef> LayersRefs;
            };
            // Тип запрета: запрет размещения.
            struct Place {
                // Сторона объекта.
                // [XmlAttribute("side")] public side side_;
                XmlAttr<side> side_;
            };
            // Тип запрета: запрет трассировки.
            // [XmlElement(Trace)] public Trace trace;
            Trace trace;
            // [XmlElement(Place)] public Place place;
            Place place;
        };
        // [XmlElement(Role)] public Role role;
        Role role_;
        // Описание фигуры.
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
        //  XmlElement(Contour),
        //  XmlElement(FilledContour),
        //  XmlElement(Polyline)] public Object FigureContPolyline_;
        XmlVariant<ArcCCW,
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
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Контур платы и вырезы в плате.
    // [XmlElement("BoardOutline")] public BoardOutline boardOutline;
    BoardOutline boardOutline;
    // Монтажные отверстия на плате.
    // [XmlArray("Mntholes"), DefaultValue(null)][XmlArrayItem("MntholeInstance")] public List<MntholeInstance> Mntholes_;
    XmlArrayElem<MntholeInstance> Mntholes;
    // Детали на механических слоях.
    // [XmlArray("MechLayerObjects"), DefaultValue(null)][XmlArrayItem("Detail")] public List<Detail> MechLayerObjects_;
    XmlArrayElem<Detail> MechLayerObjects;
    // Описание надписей.
    // [XmlArray("Texts"), DefaultValue(null)][XmlArrayItem("Text")] public List<Text> Texts_;
    XmlArrayElem<Text> Texts;
    // Описание запретов.
    // [XmlArray("Keepouts"), DefaultValue(null)][XmlArrayItem("Keepout")] public List<Keepout_Сonstructive> Keepouts_;
    XmlArrayElem<Keepout> Keepouts;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Сonstructive. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    //    void UnitsConvert(dist in_units, dist out_units);
    //    void Add(Constructive a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts);
    /************************************************************************/
};
} // namespace TopoR
