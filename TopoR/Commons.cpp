#include "Commons.h"
#include <QPainterPath>

namespace TopoR {

void arc(ArcDir dir, QPainterPath& path, const std::optional<QPointF>& startOpt, const QPointF& center, const QPointF& stop) {
    QPointF start;
    if (startOpt.has_value()) {
        start = startOpt.value();
        path.moveTo(start);
    } else
        start = path.currentPosition();

    const auto a1 = QLineF{center, start}.angle();
    const auto a2 = QLineF{center, stop}.angle();
    const auto radius = QLineF{center, start}.length();

    auto aSpan = a2 - a1;

    if (dir == CCW) {
        if (aSpan > 0.0) aSpan -= 360.0;
    } else {
        if (aSpan < 0.0) aSpan += 360.0;
    }

    path.arcTo(
        -radius + center.x(),
        -radius + center.y(),
        radius * 2,
        radius * 2,
        a1, aSpan);
}

QPainterPath SegmentLine::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void SegmentLine::drawTo(QPainterPath& path) const {
    path.lineTo(end);
}

QPainterPath SegmentArcCCW::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void SegmentArcCCW::drawTo(QPainterPath& path) const {
    arc(CCW, path, {}, center, end);
}

QPainterPath SegmentArcCW::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void SegmentArcCW::drawTo(QPainterPath& path) const {
    arc(CW, path, {}, center, end);
}

QPainterPath SegmentArcByAngle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void SegmentArcByAngle::drawTo(QPainterPath& path) const {
    // FIXME path.lineTo(end);
}

QPainterPath SegmentArcByMiddle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void SegmentArcByMiddle::drawTo(QPainterPath& path) const {
    // FIXME path.lineTo(end);
}

QPainterPath ArcCCW::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void ArcCCW::drawTo(QPainterPath& path) const {
    arc(CCW, path, start, center, end);
}

QPainterPath ArcCW::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void ArcCW::drawTo(QPainterPath& path) const {
    arc(CW, path, start, center, end);
}

QPainterPath ArcByAngle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void ArcByAngle::drawTo(QPainterPath& path) const {
    // FIXME path.lineTo(end);
}

QPainterPath ArcByMiddle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void ArcByMiddle::drawTo(QPainterPath& path) const {
    // FIXME path.lineTo(end);
}

QPainterPath Circle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Circle::drawTo(QPainterPath& path) const {
    path.addEllipse(center, diameter * 0.5, diameter * 0.5);
}

QPainterPath Line::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Line::drawTo(QPainterPath& path) const {
    for (int fl{}; auto&& pt: Dots)
        if (!fl++) path.moveTo(pt);
        else [[likely]] path.lineTo(pt);
}

QPainterPath Polyline::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Polyline::drawTo(QPainterPath& path) const {
    path.moveTo(start);
    for (auto&& segment: Segments)
        segment.visit([&path](auto&& segment) { segment.drawTo(path); });
}

QPainterPath Contour::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Contour::drawTo(QPainterPath& path) const {
    path.moveTo(start);
    for (auto&& segment: Segments)
        segment.visit([&path](auto&& segment) { segment.drawTo(path); });
    if (path.currentPosition() != start)
        path.lineTo(start);
}

QPainterPath Rect::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Rect::drawTo(QPainterPath& path) const {
    QRectF rect;
    rect.setTopLeft(Dots.front());
    rect.setBottomRight(Dots.back());
    path.addRect(rect);
}

QPainterPath FilledContour::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void FilledContour::drawTo(QPainterPath& path) const {
    path.moveTo(start);
    for (auto&& segment: Segments)
        segment.visit([&path](auto&& segment) { segment.drawTo(path); });
    if (path.currentPosition() != start)
        path.lineTo(start);
}

QPainterPath FilledCircle::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void FilledCircle::drawTo(QPainterPath& path) const {
    path.addEllipse(center, diameter * 0.5, diameter * 0.5);
}

QPainterPath FilledRect::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void FilledRect::drawTo(QPainterPath& path) const {
    QRectF rect;
    rect.setTopLeft(Dots.front());
    rect.setBottomLeft(Dots.back());
    path.addRect(rect);
}

QPainterPath Polygon::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void Polygon::drawTo(QPainterPath& path) const {
    for (auto&& pt: Dots)
        path.lineTo(pt);
}

QPainterPath TrackArcCW::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void TrackArcCW::drawTo(QPainterPath& path) const {
    arc(CW, path, {}, center, end);
}

QPainterPath TrackArc::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void TrackArc::drawTo(QPainterPath& path) const {
    arc(CCW, path, {}, center, end);
}

QPainterPath TrackLine::toPainterPath() const {
    QPainterPath path;
    return drawTo(path), path;
}
void TrackLine::drawTo(QPainterPath& path) const {
    path.lineTo(end);
}

// void base_coordinat::Shift(float x, float y) {
//     this->x += x;
//     this->y += y;
// }
// void base_coordinat::UnitsConvert(dist in_units, dist out_units) {
//     x = Ut::UnitsConvert(x, in_units, out_units);
//     y = Ut::UnitsConvert(y, in_units, out_units);
// }
// void SegmentLine::Shift(float x, float y) {
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void SegmentLine::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void SegmentArcCCW::Shift(float x, float y) {
//     /* if (_Center) Center.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void SegmentArcCCW::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Center) Center.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void SegmentArcByMiddle::Shift(float x, float y) {
//     /* if (_Middle) Middle.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void SegmentArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Middle) Middle.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void ArcCCW::Shift(float x, float y) {
//     /* if (_Start) Start.value().Shift(x, y);*/
//     /* if (_Center) Center.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void ArcCCW::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Start) Start.value().UnitsConvert(in_units, out_units);*/
//     /* if (_Center) Center.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void ArcByAngle::Shift(float x, float y) {
//     /* if (_Start) Start.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void ArcByAngle::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Start) Start.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void ArcByMiddle::Shift(float x, float y) {
//     /* if (_Start) Start.value().Shift(x, y);*/
//     /* if (_Middle) Middle.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void ArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Start) Start.value().UnitsConvert(in_units, out_units);*/
//     /* if (_Middle) Middle.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void Circle::Shift(float x, float y) {
//     /* if (_Center) Center.value().Shift(x, y);*/
// }
// void Circle::UnitsConvert(dist in_units, dist out_units) {
//     diameter = Ut::UnitsConvert(diameter, in_units, out_units);
//     /* if (_Center) Center.value().UnitsConvert(in_units, out_units);*/
// }
// void Line::Shift(float x, float y) {
//     /* if (_Dots.size())
//     for (int i = 0; i < Dots.size(); i++)
//         Dots_[i].value().Shift(x, y);*/
// }
// void Line::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Dots.size())
//     for (int i = 0; i < Dots.size(); i++)
//         Dots_[i].value().UnitsConvert(in_units, out_units);*/
// }
// void Polyline::Shift(float x, float y) {
//     /* if (_Start) Start.value().Shift(x, y);*/
//     /*  if(_Segments.size())          for(int i = 0; i < Segments.size(); i++)
//               (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().Shift(x, y);*/
// }
// void Polyline::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Start) Start.value().UnitsConvert(in_units, out_units);*/
//     /*  if(_Segments.size())          for(int i = 0; i < Segments.size(); i++)
//               (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().UnitsConvert(in_units, out_units);*/
// }
// void TrackArcCW::Shift(float x, float y) {
//     /* if (_Center) Center.value().Shift(x, y);*/
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void TrackArcCW::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Center) Center.value().UnitsConvert(in_units, out_units);*/
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void TrackLine::Shift(float x, float y) {
//     /* if (_End) End.value().Shift(x, y);*/
// }
// void TrackLine::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_End) End.value().UnitsConvert(in_units, out_units);*/
// }
// void Thermal::UnitsConvert(dist in_units, dist out_units) {
//     spokeWidth = Ut::UnitsConvert(spokeWidth, in_units, out_units);
// }
// void Detail::Shift(float x, float y) {
//     /*if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)        (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().Shift(x, y);*/
// }
// void Detail::UnitsConvert(dist in_units, dist out_units) {
//     lineWidth = Ut::UnitsConvert(lineWidth, in_units, out_units);
//     /*  if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)          (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().UnitsConvert(in_units, out_units);*/
// }
// void Text::Shift(float x, float y) {
//     /* if (_Org) Org.value().Shift(x, y);*/
// }
// void Text::UnitsConvert(dist in_units, dist out_units) {
//     /* if (_Org) Org.value().UnitsConvert(in_units, out_units);*/
// }
float Ut::UnitsConvert(float value, dist in_units, dist out_units) {
    // clang-format off
    auto k = [](dist in_units) {
        switch (in_units) {
        case dist::mkm:  return 0.001;
        case dist::cm:   return 10.0;
        case dist::dm:   return 100.0;
        case dist::m:    return 1000.0;
        case dist::mil:  return 0.0254;
        case dist::inch: return 25.4;
        case dist::mm:
        default:         return 1.0;
        }
    };
    switch (out_units) {
    case dist::mkm:  return static_cast<float>(value * k(in_units) * 1000);
    case dist::cm:   return static_cast<float>(value * k(in_units) * 0.1);
    case dist::dm:   return static_cast<float>(value * k(in_units) * 0.01);
    case dist::m:    return static_cast<float>(value * k(in_units) * 0.001);
    case dist::mil:  return static_cast<float>(value * k(in_units) * 39.37007874015748);
    case dist::inch: return static_cast<float>(value * k(in_units) * 0.03937007874015748);
    case dist::mm:   return static_cast<float>(value * k(in_units));
    default:         return value;
    }
    // clang-format on
}
} // namespace TopoR
