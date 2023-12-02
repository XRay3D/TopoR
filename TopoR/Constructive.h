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

namespace TopoR_PCB_Classes {

// Описание конструктива платы.

struct Constructive {

    // Описание контура платы и вырезов в плате.

    struct BoardOutline {

        struct Shape_Contour {

            // Толщина линии.

            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;
            float _lineWidth = 0.0F;

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
            std::variant<
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
            void Shift(float x, float y);
            void UnitsConvert(dist in_units, dist out_units);
            /*************************************************************************/
        };

        struct Shape_Voids {

            // Толщина линии.

            /* [XmlAttribute("lineWidth", DataType = "float")] public float lineWidth_; */
            XmlAttr<float> lineWidth;
            float _lineWidth = 0.0F;

            // Описание залитой фигуры.

            /* [XmlElement("FilledCircle", typeof(FilledCircle)),
                XmlElement("FilledRect", typeof(FilledRect)),
                XmlElement("Polygon", typeof(Polygon)),
                XmlElement("FilledContour", typeof(FilledContour))] public Object FilledFigure_; */
            std::variant<FilledCircle, FilledRect, Polygon, FilledContour> FilledFigure_;

            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/
            void Shift(float x, float y);
            void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };

        // Описание контура платы.

        /* [XmlArray("Contour")][XmlArrayItem("Shape")] public List<Shape_Contour> Contours_; */
        std::vector<Shape_Contour> Contours_;
        bool ShouldSerialize_Contours();

        // Вырезы в плате.

        /* [XmlArray("Voids")][XmlArrayItem("Shape")] public List<Shape_Voids> Voids_; */
        std::vector<Shape_Voids> Voids_;
        bool ShouldSerialize_Voids();
    };

    // Описание монтажного отверстия на плате.

    struct MntholeInstance {

        // Задаёт угол в градусах c точностью до тысячных долей.

        /* [XmlAttribute("angle", DataType = "float")] public float angle_; */
        XmlAttr<float> angle;
        float _angle = 0.0F;

        // Признак фиксации.

        /* [XmlAttribute("fixed")] public Bool fixed_; */
        Bool _fixed{};

        /* public bool _fixedSpecified */
        bool getFixedSpecified() const;

        // Ссылка на стек контактных площадок.

        /* [XmlElement("PadstackRef")] public PadstackRef PadstackRef_; */
        PadstackRef PadstackRef_;

        // ссылка на цепь.

        /* [XmlElement("NetRef")] public NetRef NetRef_; */
        NetRef NetRef_;

        // Точка привязки объекта.

        /* [XmlElement("Org")] public Org Org_; */
        Org Org_;

        void Shift(float x, float y);
        void UnitsConvert(dist in_units, dist out_units);
    };

    // Описание запрета.

    struct Keepout_Сonstructive {

        // Тип запрета.

        struct Role {

            // Тип запрета: запрет трассировки.

            struct Trace {

                // Тип запрета трассировки.

                /* [XmlAttribute("role")] public role role_; */
                role _role{};

                // Ссылка на слои. См. также _LayersRefs

                // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

                /* [XmlElement("AllLayers", typeof(AllLayers)),
                    XmlElement("AllLayersInner", typeof(AllLayersInner)),
                    XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)),
                    XmlElement("AllLayersSignal", typeof(AllLayersSignal)),
                    XmlElement("AllLayersOuter", typeof(AllLayersOuter)),
                    XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object LayersRef_; */
                std::variant<AllLayers, AllLayersInner, AllLayersInnerSignal, AllLayersSignal, AllLayersOuter, LayerGroupRef> LayersRef_;

                // Ссылка на слои. См. также _LayersRef

                // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

                /* [XmlElement("LayerRef")] public List<LayerRef> LayersRefs_; */
                std::vector<LayerRef> LayersRefs_;
                bool ShouldSerialize_LayersRefs();
            };

            // Тип запрета: запрет размещения.

            struct Place {

                // Сторона объекта.

                /* [XmlAttribute("side")] public side side_; */
                side _side{};
            };

            // Тип запрета: запрет трассировки.

            /* [XmlElement("Trace", typeof(Trace))] public Trace Trace_; */
            Trace Trace_;

            /* [XmlElement("Place", typeof(Place))] public Place Place_; */
            Place Place_;
        };

        /* [XmlElement("Role", typeof(Role))] public Role Role_; */
        Role Role_;

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
            Contour,
            FilledContour,
            Polyline>
            FigureContPolyline_;

        /********************************************************************************
         * Здесь находятся функции для работы с элементами класса Keepout_Сonstructive. *
         * Они не являются частью формата TopoR PCB.                                    *
         * ******************************************************************************/
        void Shift(float x, float y);
        void UnitsConvert(dist in_units, dist out_units);
        /********************************************************************************/
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string version_; */
    QString version_;

    // Контур платы и вырезы в плате.

    /* [XmlElement("BoardOutline")] public BoardOutline BoardOutline_; */
    BoardOutline BoardOutline_;

    // Монтажные отверстия на плате.

    /* [XmlArray("Mntholes"), DefaultValue(null)][XmlArrayItem("MntholeInstance")] public List<MntholeInstance> Mntholes_; */
    std::vector<MntholeInstance> Mntholes_;
    bool ShouldSerialize_Mntholes();

    // Детали на механических слоях.

    /* [XmlArray("MechLayerObjects"), DefaultValue(null)][XmlArrayItem("Detail")] public List<Detail> MechLayerObjects_; */
    std::vector<Detail> MechLayerObjects_;
    bool ShouldSerialize_MechLayerObjects();

    // Описание надписей.

    /* [XmlArray("Texts"), DefaultValue(null)][XmlArrayItem("Text")] public List<Text> Texts_; */
    std::vector<Text> Texts_;
    bool ShouldSerialize_Texts();

    // Описание запретов.

    /* [XmlArray("Keepouts"), DefaultValue(null)][XmlArrayItem("Keepout")] public List<Keepout_Сonstructive> Keepouts_; */
    std::vector<std::optional<Keepout_Сonstructive>> Keepouts_;
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

} // namespace TopoR_PCB_Classes
