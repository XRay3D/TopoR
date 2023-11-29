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

            //[XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
            float _lineWidth = 0.0F;

            // Незалитая фигура.

            //[XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Circle", typeof(Circle)), XmlElement("Line", typeof(Line)), XmlElement("Polyline", typeof(Polyline)), XmlElement("Rect", typeof(Rect)), XmlElement("Contour", typeof(Contour))] public Object _NonfilledFigure;
            std::any _NonfilledFigure;

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

            //[XmlAttribute("lineWidth", DataType = "float")] public float _lineWidth;
            float _lineWidth = 0.0F;

            // Описание залитой фигуры.

            //[XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("FilledContour", typeof(FilledContour))] public Object _FilledFigure;
            std::any _FilledFigure;

            /**********************************************************************
             * Здесь находятся функции для работы с элементами класса Shape_Voids. *
             * Они не являются частью формата TopoR PCB.                           *
             * *********************************************************************/
            void Shift(float x, float y);
            void UnitsConvert(dist in_units, dist out_units);
            /***********************************************************************/
        };

        // Описание контура платы.

        //[XmlArray("Contour")][XmlArrayItem("Shape")] public List<Shape_Contour> _Contours;
        std::vector<std::optional<Shape_Contour>> _Contours;
        bool ShouldSerialize_Contours();

        // Вырезы в плате.

        //[XmlArray("Voids")][XmlArrayItem("Shape")] public List<Shape_Voids> _Voids;
        std::vector<std::optional<Shape_Voids>> _Voids;
        bool ShouldSerialize_Voids();
    };

    // Описание монтажного отверстия на плате.

    struct MntholeInstance {

        // Задаёт угол в градусах c точностью до тысячных долей.

        //[XmlAttribute("angle", DataType = "float")] public float _angle;
        float _angle = 0.0F;

        // Признак фиксации.

        //[XmlAttribute("fixed")] public Bool _fixed;
        Bool _fixed{};

        //[XmlIgnore] public bool _fixedSpecified
        bool getFixedSpecified() const;

        // Ссылка на стек контактных площадок.

        //[XmlElement("PadstackRef")] public PadstackRef _PadstackRef;
        std::optional<PadstackRef> _PadstackRef;

        // ссылка на цепь.

        //[XmlElement("NetRef")] public NetRef _NetRef;
        std::optional<NetRef> _NetRef;

        // Точка привязки объекта.

        //[XmlElement("Org")] public Org _Org;
        std::optional<Org> _Org;

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

                //[XmlAttribute("role")] public role _role;
                role _role{};

                // Ссылка на слои. См. также _LayersRefs

                // <remarks>! При null необходимо смотреть _LayersRefs - там описан список ссылок типа LayerRef. </remarks>

                //[XmlElement("AllLayers", typeof(AllLayers)), XmlElement("AllLayersInner", typeof(AllLayersInner)), XmlElement("AllLayersInnerSignal", typeof(AllLayersInnerSignal)), XmlElement("AllLayersSignal", typeof(AllLayersSignal)), XmlElement("AllLayersOuter", typeof(AllLayersOuter)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public Object _LayersRef;
                std::any _LayersRef;

                // Ссылка на слои. См. также _LayersRef

                // <remarks>! При null необходимо смотреть _LayersRef - там описаны ссылки остальных типов. </remarks>

                //[XmlElement("LayerRef")] public List<LayerRef> _LayersRefs;
                std::vector<std::optional<LayerRef>> _LayersRefs;
                bool ShouldSerialize_LayersRefs();
            };

            // Тип запрета: запрет размещения.

            struct Place {

                // Сторона объекта.

                //[XmlAttribute("side")] public side _side;
                side _side{};
            };

            // Тип запрета: запрет трассировки.

            //[XmlElement("Trace", typeof(Trace))] public Trace _Trace;
            std::optional<Trace> _Trace;

            //[XmlElement("Place", typeof(Place))] public Place _Place;
            std::optional<Place> _Place;
        };

        //[XmlElement("Role", typeof(Role))] public Role _Role;
        std::optional<Role> _Role;

        // Описание фигуры.

        //[XmlElement("ArcCCW", typeof(ArcCCW)), XmlElement("ArcCW", typeof(ArcCW)), XmlElement("ArcByAngle", typeof(ArcByAngle)), XmlElement("ArcByMiddle", typeof(ArcByMiddle)), XmlElement("Line", typeof(Line)), XmlElement("Circle", typeof(Circle)), XmlElement("Rect", typeof(Rect)), XmlElement("FilledCircle", typeof(FilledCircle)), XmlElement("FilledRect", typeof(FilledRect)), XmlElement("Polygon", typeof(Polygon)), XmlElement("Contour", typeof(Contour)), XmlElement("FilledContour", typeof(FilledContour)), XmlElement("Polyline", typeof(Polyline))] public Object _FigureContPolyline;
        std::any _FigureContPolyline;

        /********************************************************************************
         * Здесь находятся функции для работы с элементами класса Keepout_Сonstructive. *
         * Они не являются частью формата TopoR PCB.                                    *
         * ******************************************************************************/
        void Shift(float x, float y);
        void UnitsConvert(dist in_units, dist out_units);
        /********************************************************************************/
    };

    // Версия раздела.

    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Контур платы и вырезы в плате.

    //[XmlElement("BoardOutline")] public BoardOutline _BoardOutline;
    std::optional<BoardOutline> _BoardOutline;

    // Монтажные отверстия на плате.

    //[XmlArray("Mntholes"), DefaultValue(null)][XmlArrayItem("MntholeInstance")] public List<MntholeInstance> _Mntholes;
    std::vector<std::optional<MntholeInstance>> _Mntholes;
    bool ShouldSerialize_Mntholes();

    // Детали на механических слоях.

    //[XmlArray("MechLayerObjects"), DefaultValue(null)][XmlArrayItem("Detail")] public List<Detail> _MechLayerObjects;
    std::vector<std::optional<Detail>> _MechLayerObjects;
    bool ShouldSerialize_MechLayerObjects();

    // Описание надписей.

    //[XmlArray("Texts"), DefaultValue(null)][XmlArrayItem("Text")] public List<Text> _Texts;
    std::vector<std::optional<Text>> _Texts;
    bool ShouldSerialize_Texts();

    // Описание запретов.

    //[XmlArray("Keepouts"), DefaultValue(null)][XmlArrayItem("Keepout")] public List<Keepout_Сonstructive> _Keepouts;
    std::vector<std::optional<Keepout_Сonstructive>> _Keepouts;
    bool ShouldSerialize_Keepouts();

    /************************************************************************
     * Здесь находятся функции для работы с элементами класса Сonstructive. *
     * Они не являются частью формата TopoR PCB.                            *
     * **********************************************************************/

    void Shift(float x, float y);

    void UnitsConvert(dist in_units, dist out_units);

    void Add(std::optional<Constructive> a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts);
    /************************************************************************/
};
} // namespace TopoR_PCB_Classes
