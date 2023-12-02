#include "Commons.h"

namespace TopoR_PCB_Classes {

void base_coordinat::Shift(float x, float y) {
    this->x += x;
    this->y += y;
}

void base_coordinat::UnitsConvert(dist in_units, dist out_units) {
    x = Ut::UnitsConvert(x, in_units, out_units);
    y = Ut::UnitsConvert(y, in_units, out_units);
}

void SegmentLine::Shift(float x, float y) {
    /* if (_End) End_.value().Shift(x, y);*/
}

void SegmentLine::UnitsConvert(dist in_units, dist out_units) {
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void SegmentArcCCW::Shift(float x, float y) {
    /* if (_Center) Center_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void SegmentArcCCW::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Center) Center_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void SegmentArcByMiddle::Shift(float x, float y) {
    /* if (_Middle) Middle_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void SegmentArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Middle) Middle_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void ArcCCW::Shift(float x, float y) {
    /* if (_Start) Start_.value().Shift(x, y);*/
    /* if (_Center) Center_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void ArcCCW::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Start) Start_.value().UnitsConvert(in_units, out_units);*/
    /* if (_Center) Center_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void ArcByAngle::Shift(float x, float y) {
    /* if (_Start) Start_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void ArcByAngle::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Start) Start_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void ArcByMiddle::Shift(float x, float y) {
    /* if (_Start) Start_.value().Shift(x, y);*/
    /* if (_Middle) Middle_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void ArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Start) Start_.value().UnitsConvert(in_units, out_units);*/
    /* if (_Middle) Middle_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void Circle::Shift(float x, float y) {
    /* if (_Center) Center_.value().Shift(x, y);*/
}

void Circle::UnitsConvert(dist in_units, dist out_units) {
    diameter = Ut::UnitsConvert(diameter, in_units, out_units);
    /* if (_Center) Center_.value().UnitsConvert(in_units, out_units);*/
}

bool Line::ShouldSerialize_Dots() {
    return Dots_.size();
}

void Line::Shift(float x, float y) {
    /* if (_Dots.size())
    for (int i = 0; i < Dots_.size(); i++)
        _Dots[i].value().Shift(x, y);*/
}

void Line::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Dots.size())
    for (int i = 0; i < Dots_.size(); i++)
        _Dots[i].value().UnitsConvert(in_units, out_units);*/
}

bool Polyline::ShouldSerialize_Segments() {
    return {}; //_Segments.size();
}

void Polyline::Shift(float x, float y) {
    /* if (_Start) Start_.value().Shift(x, y);*/

    /*  if(_Segments.size())          for(int i = 0; i < Segments_.size(); i++)
              (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().Shift(x, y);*/
}

void Polyline::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Start) Start_.value().UnitsConvert(in_units, out_units);*/

    /*  if(_Segments.size())          for(int i = 0; i < Segments_.size(); i++)
              (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().UnitsConvert(in_units, out_units);*/
}

void TrackArcCW::Shift(float x, float y) {
    /* if (_Center) Center_.value().Shift(x, y);*/
    /* if (_End) End_.value().Shift(x, y);*/
}

void TrackArcCW::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Center) Center_.value().UnitsConvert(in_units, out_units);*/
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void TrackLine::Shift(float x, float y) {
    /* if (_End) End_.value().Shift(x, y);*/
}

void TrackLine::UnitsConvert(dist in_units, dist out_units) {
    /* if (_End) End_.value().UnitsConvert(in_units, out_units);*/
}

void Thermal::UnitsConvert(dist in_units, dist out_units) {
    spokeWidth = Ut::UnitsConvert(spokeWidth, in_units, out_units);
}

void Detail::Shift(float x, float y) {
    /*if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)        (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().Shift(x, y);*/
}

void Detail::UnitsConvert(dist in_units, dist out_units) {
    lineWidth = Ut::UnitsConvert(lineWidth, in_units, out_units);
    /*  if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)          (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().UnitsConvert(in_units, out_units);*/
}

bool Text::getMirrorSpecified() const {
    return _mirror != Bool::off;
}

void Text::Shift(float x, float y) {
    /* if (_Org) Org_.value().Shift(x, y);*/
}

void Text::UnitsConvert(dist in_units, dist out_units) {
    /* if (_Org) Org_.value().UnitsConvert(in_units, out_units);*/
}

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

} // namespace TopoR_PCB_Classes
