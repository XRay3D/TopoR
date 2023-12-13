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
        struct ShapeContour {
            // Толщина линии.
            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;
            float lineWidth_ = 0.0F;
            // Незалитая фигура.
            /* [XmlElement("ArcCCW", typeof(ArcCCW)),
                XmlElement("ArcCW", typeof(ArcCW)),
                XmlElement("ArcByAngle", typeof(ArcByAngle)),
                XmlElement("ArcByMiddle", typeof(ArcByMiddle)),
                XmlElement("Circle", typeof(Circle)),
                XmlElement("Line", typeof(Line)),
                XmlElement("Polyline", typeof(Polyline)),
                XmlElement("Rect", typeof(Rect)),
                XmlElement("Contour", typeof(Contour))] public Object NonfilledFigure_; */
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
            //    void Shift(float x, float y);
            //    void UnitsConvert(dist in_units, dist out_units);
            /*************************************************************************/
        };
        struct ShapeVoids {
            // Толщина линии.
            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;
            float lineWidth_ = 0.0F;
            // Описание залитой фигуры.
            /* [XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object FilledFigure_; */
            XmlVariant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;
            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/
            //    void Shift(float x, float y);
            //    void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };
        // Описание контура платы.
        /* [XmlArray("Contour")][XmlArrayItem("Shape")] public List<Shape_Contour> Contours_; */
        XmlArrayElem<ShapeContour> Contours;
        // Вырезы в плате.
        /* [XmlArray("Voids")][XmlArrayItem("Shape")] public List<Shape_Voids> Voids_; */
        XmlArrayElem<ShapeVoids> Voids;
    };
    // Описание монтажного отверстия на плате.
    struct MntholeInstance {
        // Задаёт угол в градусах c точностью до тысячных долей.
        /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
        XmlAttr<float> angle;
        float angle_ = 0.0F;
        // Признак фиксации.
        /* [XmlAttribute("fixed")] public Bool fixed_; */
        Bool fixed_{};
        /* public bool fixedSpecified_ */
        // Ссылка на стек контактных площадок.
        /* [XmlElement("PadstackRef")] public PadstackRef padstackRef; */
        PadstackRef padstackRef;
        // ссылка на цепь.
        /* [XmlElement("NetRef")] public NetRef netRef; */
        NetRef netRef;
        // Точка привязки объекта.
        /* [XmlElement("Org")] public Org org; */
        Org org;
        //    void Shift(float x, float y);
        //    void UnitsConvert(dist in_units, dist out_units);
    };
    // Описание запрета.
    struct Keepout {
        // Тип запрета.
        struct Role {
            // Тип запрета: запрет трассировки.
            struct Trace {
                // Тип запрета трассировки.
                /* [XmlAttribute("role")] public role role_; */
                role role_{};
                // Ссылка на слои. См. также LayersRefs_
                // <remarks>! При null необходимо смотреть LayersRefs_ - там описан список ссылок типа LayerRef. </remarks>
                /* [XmlElement("AllLayers", typeof(AllLayers)),
                    XmlElement("AllLayersInner", typeof(AllLayersInner)),
                    XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
                    XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
                    XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
                    XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
                XmlVariant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef_;
                // Ссылка на слои. См. также LayersRef_
                // <remarks>! При null необходимо смотреть LayersRef_ - там описаны ссылки остальных типов. </remarks>
                /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
                XmlArrayElem<LayerRef> LayersRefs;
            };
            // Тип запрета: запрет размещения.
            struct Place {
                // Сторона объекта.
                /* [XmlAttribute("side")] public side side_; */
                side side_{};
            };
            // Тип запрета: запрет трассировки.
            /* [XmlElement("Trace", typeof(Trace))] public Trace trace; */
            Trace trace;
            /* [XmlElement("Place", typeof(Place))] public Place place; */
            Place place;
        };
        /* [XmlElement("Role", typeof(Role))] public Role role; */
        Role role_;
        // Описание фигуры.
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
            XmlElement("Contour", typeof(Contour)),
            XmlElement("FilledContour", typeof(FilledContour)),
            XmlElement("Polyline", typeof(Polyline))] public Object FigureContPolyline_; */
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
        //    void Shift(float x, float y);
        //    void UnitsConvert(dist in_units, dist out_units);
        /********************************************************************************/
    };
    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;
    // Контур платы и вырезы в плате.
    /* [XmlElement("BoardOutline")] public BoardOutline boardOutline; */
    BoardOutline boardOutline;
    // Монтажные отверстия на плате.
    /* [XmlArray("Mntholes"), DefaultValue(null)][XmlArrayItem("MntholeInstance")] public List<MntholeInstance> Mntholes_; */
    XmlArrayElem<MntholeInstance> Mntholes;
    // Детали на механических слоях.
    /* [XmlArray("MechLayerObjects"), DefaultValue(null)][XmlArrayItem("Detail")] public List<Detail> MechLayerObjects_; */
    XmlArrayElem<Detail> MechLayerObjects;
    // Описание надписей.
    /* [XmlArray("Texts"), DefaultValue(null)][XmlArrayItem("Text")] public List<Text> Texts_; */
    XmlArrayElem<Text> Texts;
    // Описание запретов.
    /* [XmlArray("Keepouts"), DefaultValue(null)][XmlArrayItem("Keepout")] public List<Keepout_Сonstructive> Keepouts_; */
    XmlArrayElem<Keepout> Keepouts;
    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Сonstructive. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/
    //    void Shift(float x, float y);
    //    void UnitsConvert(dist in_units, dist out_units);
    //    void Add(Constructive a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts);
    /************************************************************************/
};
} // namespace TopoR
