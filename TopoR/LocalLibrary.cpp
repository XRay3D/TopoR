﻿#include "LocalLibrary.h"
#include "TopoR_PCB_File.h"

#include <QGraphicsItemGroup>
#include <QPen>

namespace TopoR_PCB_Classes {

LocalLibrary::PadCircle::operator QPainterPath() const {
    QPainterPath path;
    path.addEllipse(QPointF{}, diameter * 0.5, diameter * 0.5);
    return path;
}

LocalLibrary::PadOval::operator QPainterPath() const {
    QPainterPath path;
    QLineF line{{}, Stretch_};
    line = line.translated(Shift_);
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    path.translate(Shift_);
    path.addEllipse(line.p1(), diameter * 0.5, diameter * 0.5);
    path.addEllipse(line.p2(), diameter * 0.5, diameter * 0.5);
    return path;
}

LocalLibrary::PadRect::operator QPainterPath() const { // FIXME addRoundedRect
    QPainterPath path;
    path.addRoundedRect(-width * .5, -height * .5, width, height, handlingValue, handlingValue);
    return path;
}

LocalLibrary::PadPoly::operator QPolygonF() const {
    assert(Dots.size() > 2);
    QPolygonF poly;
    poly.reserve(Dots.size());
    for(const auto& dot: Dots) poly.append(dot);
    return poly;
}

LocalLibrary::PadPoly::operator QPainterPath() const {
    QPainterPath path;
    // path.moveTo(Dots.front());
    path.addPolygon(*this);
    return path;
}

const LocalLibrary::Padstack* LocalLibrary::getPadstack(const QString& name) const {
    for(auto&& padstack: Padstacks)
        if(name == padstack.name)
            return &padstack;
    return {};
}

const LocalLibrary::Footprint* LocalLibrary::getFootprint(const QString& name) const {
    for(auto&& footprint: Footprints)
        if(name == footprint.name)
            return &footprint;
    return {};
}

QGraphicsItem* LocalLibrary::Footprint::graphicsItem(const TopoR_PCB_File& file) const {
    auto group = new QGraphicsItemGroup;
    LocalLibrary::footprints.emplace(name, group);
    for(auto&& pad: Pads) {
        if(auto padstack = file.localLibrary.getPadstack(pad.padstackRef.name); padstack)
            for(int hue{}; auto&& padShape: padstack->Pads) {
                if(auto item = padShape.visit([](auto&& pad) {
                       return new QGraphicsPathItem{pad};
                   });
                    item) {
                    int color = 240 / padstack->Pads.size() * hue++;
                    item->setPen({QColor::fromHsv(color, 255, 255),
                        0.0});
                    item->setTransform(pad.transform());
                    group->addToGroup(item);
                }
            }
    }
    for(auto&& label: Labels) {
        // if(auto padstack = lib.getPadstack(label.); padstack)
        //     for(int hue{}; auto&& padShape: padstack->Pads) {
        //         if(auto item = padShape.visit([](auto&& pad) {
        //                return new QGraphicsPathItem{pad};
        //            });
        //             item) {
        //             int color = 240 / padstack->Pads.size() * hue++;
        //             item->setPen({QColor::fromHsv(color, 255, 255),
        //                 0.0});
        //             item->setTransform(label.transform());
        //             group->addToGroup(item);
        //         }
        //     }
    }

    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    return group;
}

} // namespace TopoR_PCB_Classes
