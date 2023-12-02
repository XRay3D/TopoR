#include "Constructive.h"

namespace TopoR_PCB_Classes {

void Constructive::BoardOutline::Shape_Contour::Shift(float x, float y) {
    /*   if(_NonfilledFigure)
           (std::dynamic_pointer_cast<IBaseFigure>(_NonfilledFigure)).value().Shift(x, y);*/
}

void Constructive::BoardOutline::Shape_Contour::UnitsConvert(dist in_units, dist out_units) {
    /*   _lineWidth = Ut::UnitsConvert(_lineWidth, in_units, out_units);
       if(_NonfilledFigure)
           (std::dynamic_pointer_cast<IBaseFigure>(_NonfilledFigure)).value().UnitsConvert(in_units, out_units);*/
}

void Constructive::BoardOutline::Shape_Voids::Shift(float x, float y) {
    /*    if(_FilledFigure)
            (std::dynamic_pointer_cast<IBaseFigure>(_FilledFigure)).value().Shift(x, y);*/
}

void Constructive::BoardOutline::Shape_Voids::UnitsConvert(dist in_units, dist out_units) {
    /*   _lineWidth = Ut::UnitsConvert(_lineWidth, in_units, out_units);
       if(_FilledFigure)
           (std::dynamic_pointer_cast<IBaseFigure>(_FilledFigure)).value().UnitsConvert(in_units, out_units);*/
}

bool Constructive::BoardOutline::ShouldSerialize_Contours() {
    return Contours_.size();
}

bool Constructive::BoardOutline::ShouldSerialize_Voids() {
    return Voids_.size();
}

bool Constructive::MntholeInstance::getFixedSpecified() const {
    return _fixed != Bool::off;
}

void Constructive::MntholeInstance::Shift(float x, float y) {
    /**  if(_Org)
          Org_.value().Shift(x, y);*/
}

void Constructive::MntholeInstance::UnitsConvert(dist in_units, dist out_units) {
    /*  if(_Org)
          Org_.value().UnitsConvert(in_units, out_units);*/
}

bool Constructive::Keepout_Сonstructive::Role::Trace::ShouldSerialize_LayersRefs() {
    return LayersRefs_.size();
}

void Constructive::Keepout_Сonstructive::Shift(float x, float y) {
    /* if(_FigureContPolyline)
         (std::dynamic_pointer_cast<IBaseFigure>(_FigureContPolyline)).value().Shift(x, y);*/
}

void Constructive::Keepout_Сonstructive::UnitsConvert(dist in_units, dist out_units) {
    /*  if(_FigureContPolyline)
          (std::dynamic_pointer_cast<IBaseFigure>(_FigureContPolyline)).value().UnitsConvert(in_units, out_units);*/
}

bool Constructive::ShouldSerialize_Mntholes() {
    return Mntholes_.size();
}

bool Constructive::ShouldSerialize_MechLayerObjects() {
    return MechLayerObjects_.size();
}

bool Constructive::ShouldSerialize_Texts() {
    return Texts_.size();
}

bool Constructive::ShouldSerialize_Keepouts() {
    return Keepouts_.size();
}

void Constructive::Shift(float x, float y) {
    /*  if(_BoardOutline) {
           if(_BoardOutline.size())
               for(int i = 0; i < BoardOutline_.value()._Contours.size(); i++)
                   _BoardOutline->_Contours[i].value().Shift(x, y);
           if(_BoardOutline.size())
               for(int i = 0; i < BoardOutline_.value()._Voids.size(); i++)
                   _BoardOutline->_Voids[i].value().Shift(x, y);
       }

       if(_Mntholes.size())
           for(int i = 0; i < Mntholes_.size(); i++)
               _Mntholes[i].value().Shift(x, y);

       if(_MechLayerObjects.size())
           for(int i = 0; i < MechLayerObjects_.size(); i++)
               _MechLayerObjects[i].value().Shift(x, y);

       if(_Texts.size())
           for(int i = 0; i < Texts_.size(); i++)
               _Texts[i].value().Shift(x, y);

       if(_Keepouts.size())
           for(int i = 0; i < Keepouts_.size(); i++)
               _Keepouts[i].value().Shift(x, y);*/
}

void Constructive::UnitsConvert(dist in_units, dist out_units) {
    /*   if(_BoardOutline.size())
           for(int i = 0; i < BoardOutline_.value()._Contours.size(); i++)
               _BoardOutline->_Contours[i].value().UnitsConvert(in_units, out_units);
       if(_BoardOutline.size())
           for(int i = 0; i < BoardOutline_.value()._Voids.size(); i++)
               _BoardOutline->_Voids[i].value().UnitsConvert(in_units, out_units);

       if(_Mntholes.size())
           for(int i = 0; i < Mntholes_.size(); i++)
               _Mntholes[i].value().UnitsConvert(in_units, out_units);

       if(_MechLayerObjects.size())
           for(int i = 0; i < MechLayerObjects_.size(); i++)
               _MechLayerObjects[i].value().UnitsConvert(in_units, out_units);

       if(_Texts.size())
           for(int i = 0; i < Texts_.size(); i++)
               _Texts[i].value().UnitsConvert(in_units, out_units);

       if(_Keepouts.size())
           for(int i = 0; i < Keepouts_.size(); i++)
               _Keepouts[i].value().UnitsConvert(in_units, out_units);*/
}

void Constructive::Add(Constructive a, bool boardOutline, bool mntholeInstances, bool details, bool texts, bool keepouts) {
    /* int l;
     if (boardOutline)
     {
         if a.size())
         {
             if (_BoardOutline == null)
                 _BoardOutline = new BoardOutline();

             if (_BoardOutline._Contours == null)
                 BoardOutline_._Contours = (BoardOutline.Shape_Contour[])a._BoardOutline._Contours.Clone();
             else
             {
                 l = BoardOutline_._Contours.Count;
                 Array.Resize(ref BoardOutline_._Contours, l + a._BoardOutline._Contours.Count);
                 a._BoardOutline._Contours.CopyTo(_BoardOutline._Contours, l);
             }
         }

         if a.size())
         {
             if (_BoardOutline == null)
                 _BoardOutline = new BoardOutline();

             if (_BoardOutline._Voids == null)
                 BoardOutline_._Voids = (BoardOutline.Shape_Voids[])a._BoardOutline._Voids.Clone();
             else
             {
                 l = BoardOutline_._Voids.Count;
                 Array.Resize(ref BoardOutline_._Voids, l + a._BoardOutline._Voids.Count);
                 a._BoardOutline._Voids.CopyTo(_BoardOutline._Voids, l);
             }
         }
     }

     if (mntholeInstances)
     {
         if a.size())
         {
             if (_Mntholes == null)
                 _Mntholes = (MntholeInstance[])a._Mntholes.Clone();
             else
             {
                 l = Mntholes_.Count;
                 Array.Resize(ref _Mntholes, l + a._Mntholes.Count);
                 a._Mntholes.CopyTo(_Mntholes, l);
             }
         }
     }

     if (details)
     {
         if a.size())
         {
             if (_MechLayerObjects == null)
                 _MechLayerObjects = (Detail[])a._MechLayerObjects.Clone();
             else
             {
                 l = MechLayerObjects_.Count;
                 Array.Resize(ref _MechLayerObjects, l + a._MechLayerObjects.Count);
                 a._MechLayerObjects.CopyTo(_MechLayerObjects, l);
             }
         }
     }

     if (texts)
     {
         if a.size())
         {
             if (_Texts == null)
                 _Texts = (Text[])a._Texts.Clone();
             else
             {
                 l = Texts_.Count;
                 Array.Resize(ref _Texts, l + a._Texts.Count);
                 a._Texts.CopyTo(_Texts, l);
             }
         }
     }

     if (keepouts)
     {
         if a.size())
         {
             if (_Keepouts == null)
                 _Keepouts = (Keepout_Сonstructive[])a._Keepouts.Clone();
             else
             {
                 l = Keepouts_.Count;
                 Array.Resize(ref _Keepouts, l + a._Keepouts.Count);
                 a._Keepouts.CopyTo(_Keepouts, l);
             }
         }
     }*/
}

} // namespace TopoR_PCB_Classes
