#include "Commons.h"

namespace TopoR_PCB_Classes {

void base_coordinat::Shift(float x, float y) {
    _x += x;
    _y += y;
}

void base_coordinat::UnitsConvert(dist in_units, dist out_units) {
    _x = Ut::UnitsConvert(_x, in_units, out_units);
    _y = Ut::UnitsConvert(_y, in_units, out_units);
}

void SegmentLine::Shift(float x, float y) {
    if(_End)
        _End.value().Shift(x, y);
}

void SegmentLine::UnitsConvert(dist in_units, dist out_units) {
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void SegmentArcCCW::Shift(float x, float y) {
    if(_Center)
        _Center.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void SegmentArcCCW::UnitsConvert(dist in_units, dist out_units) {
    if(_Center)
        _Center.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void SegmentArcByMiddle::Shift(float x, float y) {
    if(_Middle)
        _Middle.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void SegmentArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
    if(_Middle)
        _Middle.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void ArcCCW::Shift(float x, float y) {
    if(_Start)
        _Start.value().Shift(x, y);
    if(_Center)
        _Center.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void ArcCCW::UnitsConvert(dist in_units, dist out_units) {
    if(_Start)
        _Start.value().UnitsConvert(in_units, out_units);
    if(_Center)
        _Center.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void ArcByAngle::Shift(float x, float y) {
    if(_Start)
        _Start.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void ArcByAngle::UnitsConvert(dist in_units, dist out_units) {
    if(_Start)
        _Start.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void ArcByMiddle::Shift(float x, float y) {
    if(_Start)
        _Start.value().Shift(x, y);
    if(_Middle)
        _Middle.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void ArcByMiddle::UnitsConvert(dist in_units, dist out_units) {
    if(_Start)
        _Start.value().UnitsConvert(in_units, out_units);
    if(_Middle)
        _Middle.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void Circle::Shift(float x, float y) {
    if(_Center)
        _Center.value().Shift(x, y);
}

void Circle::UnitsConvert(dist in_units, dist out_units) {
    _diameter = Ut::UnitsConvert(_diameter, in_units, out_units);
    if(_Center)
        _Center.value().UnitsConvert(in_units, out_units);
}

bool Line::ShouldSerialize_Dots() {
    return _Dots.size();
}

void Line::Shift(float x, float y) {
    if(_Dots.size())
        for(int i = 0; i < _Dots.size(); i++)
            _Dots[i].value().Shift(x, y);
}

void Line::UnitsConvert(dist in_units, dist out_units) {
    if(_Dots.size())
        for(int i = 0; i < _Dots.size(); i++)
            _Dots[i].value().UnitsConvert(in_units, out_units);
}

bool Polyline::ShouldSerialize_Segments() {
    return _Segments.size();
}

void Polyline::Shift(float x, float y) {
    if(_Start)
        _Start.value().Shift(x, y);

    /*  if(_Segments.size())
          for(int i = 0; i < _Segments.size(); i++)
              (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().Shift(x, y);*/
}

void Polyline::UnitsConvert(dist in_units, dist out_units) {
    if(_Start)
        _Start.value().UnitsConvert(in_units, out_units);

    /*  if(_Segments.size())
          for(int i = 0; i < _Segments.size(); i++)
              (std::dynamic_pointer_cast<IBaseSegment>(_Segments[i])).value().UnitsConvert(in_units, out_units);*/
}

void TrackArcCW::Shift(float x, float y) {
    if(_Center)
        _Center.value().Shift(x, y);
    if(_End)
        _End.value().Shift(x, y);
}

void TrackArcCW::UnitsConvert(dist in_units, dist out_units) {
    if(_Center)
        _Center.value().UnitsConvert(in_units, out_units);
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void TrackLine::Shift(float x, float y) {
    if(_End)
        _End.value().Shift(x, y);
}

void TrackLine::UnitsConvert(dist in_units, dist out_units) {
    if(_End)
        _End.value().UnitsConvert(in_units, out_units);
}

void Thermal::UnitsConvert(dist in_units, dist out_units) {
    _spokeWidth = Ut::UnitsConvert(_spokeWidth, in_units, out_units);
}

void Detail::Shift(float x, float y) {
    /*if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)
        (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().Shift(x, y);*/
}

void Detail::UnitsConvert(dist in_units, dist out_units) {
    _lineWidth = Ut::UnitsConvert(_lineWidth, in_units, out_units);
    /*  if((std::dynamic_pointer_cast<IBaseFigure>(_Figure)) != nullptr)
          (std::dynamic_pointer_cast<IBaseFigure>(_Figure)).value().UnitsConvert(in_units, out_units);*/
}

bool Text::getMirrorSpecified() const {
    return _mirror != Bool::off;
}

void Text::Shift(float x, float y) {
    if(_Org)
        _Org.value().Shift(x, y);
}

void Text::UnitsConvert(dist in_units, dist out_units) {
    if(_Org)
        _Org.value().UnitsConvert(in_units, out_units);
}

float Ut::UnitsConvert(float value, dist in_units, dist out_units) {
    double k;
    switch(in_units) {
    case dist::mkm:
        k = 0.001;
        break;
    case dist::cm:
        k = 10;
        break;
    case dist::dm:
        k = 100;
        break;
    case dist::m:
        k = 1000;
        break;
    case dist::mil:
        k = 0.0254000000000000002032;
        break;
    case dist::inch:
        k = 25.4000000000000002032;
        break;
    case dist::mm:
    default:
        k = 1;
        break;
    }
    switch(out_units) {
    case dist::mkm:
        return static_cast<float>(value * k * 1000);
    case dist::cm:
        return static_cast<float>(value * k * 0.1);
    case dist::dm:
        return static_cast<float>(value * k * 0.01);
    case dist::m:
        return static_cast<float>(value * k * 0.001);
    case dist::mil:
        return static_cast<float>(value * k * 39.37007874015748);
    case dist::inch:
        return static_cast<float>(value * k * 0.03937007874015748);
    case dist::mm:
        return static_cast<float>(value * k);
    default:
        return value;
    }
}
} // namespace TopoR_PCB_Classes
