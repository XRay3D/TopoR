#include "LocalLibrary.h"
#include "TopoR_PCB_File.h"
#include <QGraphicsItemGroup>
#include <QPen>

namespace TopoR {

LocalLibrary::PadCircle::operator QPainterPath() const {
    QPainterPath path;
    path.addEllipse(QPointF{}, diameter * 0.5, diameter * 0.5);
    return path;
}

LocalLibrary::PadOval::operator QPainterPath() const {
    QPainterPath path;

    const QLineF line{stretch * -0.5, stretch * +0.5};
    const auto angle = line.angle();
    const QRectF capRect{-diameter * 0.5, -diameter * 0.5, diameter, diameter};
    const auto start = QLineF::fromPolar(diameter * 0.5, angle + 90).translated(line.p1()).p2();

    path.moveTo(start);
    path.arcTo(capRect.translated(line.p1()), angle + 90, 180);
    path.arcTo(capRect.translated(line.p2()), angle + 275, 180);
    path.lineTo(start);
    path.translate(shift);

    return path;
}

LocalLibrary::PadRect::operator QPainterPath() const { // FIXME addRoundedRect
    QPainterPath path;
    const QRectF rect{-width * .5, -height * .5, width, height};
    if(handlingValue > 0 && custom == Bool::off && handling == Handling::Rounding) {
        path.addRoundedRect(rect, handlingValue, handlingValue);
    } else if(handlingValue == 0 && custom == Bool::off) {
        path.addRect(rect);
    } else {
#define LB topLeft
#define LT bottomLeft
#define RB topRight
#define RT bottomRight
        const QRectF rectInner = rect - QMarginsF{handlingValue, handlingValue, handlingValue, handlingValue};
        const QRectF cornerRect{-handlingValue, -handlingValue, handlingValue * 2, handlingValue * 2};
        if(+cornerLB) {
            path.moveTo(rect.LB() + QPointF{0, handlingValue});
            if(handling == Handling::Rounding) {
                path.arcTo(cornerRect.translated(rectInner.LB()), 180, -90);
            } else {
                path.lineTo(rect.LB() + QPointF{handlingValue, 0});
            }
        } else path.moveTo(rect.LB());
        if(+cornerRB) {
            if(handling == Handling::Rounding) {
                path.arcTo(cornerRect.translated(rectInner.RB()), 90, -90);
            } else {
                path.lineTo(rect.RB() - QPointF{handlingValue, 0});
                path.lineTo(rect.RB() + QPointF{0, handlingValue});
            }
        } else path.lineTo(rect.RB());
        if(+cornerRT) {
            if(handling == Handling::Rounding) {
                path.arcTo(cornerRect.translated(rectInner.RT()), 0, -90);
            } else {
                path.lineTo(rect.RT() - QPointF{0, handlingValue});
                path.lineTo(rect.RT() - QPointF{handlingValue, 0});
            }
        } else path.lineTo(rect.RT());
        if(+cornerLT) {
            if(handling == Handling::Rounding) {
                path.arcTo(cornerRect.translated(rectInner.LT()), 270, -90);
            } else {
                path.lineTo(rect.LT() + QPointF{handlingValue, 0});
                path.lineTo(rect.LT() - QPointF{0, handlingValue});
            }
        } else path.lineTo(rect.LT());
        if(+cornerLB) {
            path.lineTo(rect.LB() + QPointF{0, handlingValue});
        } else path.lineTo(rect.LB());
#undef LB
#undef RB
#undef RT
#undef LT
    }
    path.translate(shift);
    return path;
}

LocalLibrary::PadPoly::operator QPolygonF() const {
    assert(Dots.size() > 2);
    QPolygonF poly;
    poly.reserve(Dots.size() + 1);
    for(const auto& dot: Dots) poly.append(dot);
    if(Dots.front() != Dots.back()) poly.append(Dots.front());
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

const LocalLibrary::Component* LocalLibrary::getComponent(const QString& name) const {
    for(auto&& component: Components)
        if(name == component.name)
            return &component;
    return {};
}

const LocalLibrary::Viastack* LocalLibrary::getViastack(const QString& name) const {
    for(auto&& viastack: Viastacks)
        if(name == viastack.name)
            return &viastack;
    return {};
}

QGraphicsItem* LocalLibrary::Footprint::graphicsItem(const TopoR_PCB_File& file) const {
    auto group = new QGraphicsItemGroup;
    LocalLibrary::footprints.emplace(name, group);
    for(auto&& pad: Pads) {
        if(auto padstack = file.localLibrary.getPadstack(pad.padstackRef.name); padstack)
            for(int hue{}; auto&& padShape: padstack->Pads) {
                if(auto item = padShape.visit([](auto&& pad) { return new QGraphicsPathItem{pad}; }); item) {
                    int color = 240 / padstack->Pads.size() * hue++;
                    item->setPen({QColor::fromHsv(color, 255, 255),
                        0.0});
                    item->setTransform(pad.transform());
                    group->addToGroup(item);
                }
            }
    }

    for(auto&& label: Labels) {
        if(auto textStyle = file.textStyles.getTextStyle(label.textStyleRef); textStyle) {
        }
    }
    for(auto&& label: Labels) {
        if(auto textStyle = file.textStyles.getTextStyle(label.textStyleRef); textStyle) {
        }
    }
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    return group;
}

QString LocalLibrary::Padstack::getReference(const XmlVariant<PadCircle, PadOval, PadRect, PadPoly>& padShape) {
    return padShape.visit([](auto&& pad) { return pad.Reference.visit([](auto&& ref) -> QString { return ref; }); });
}

} // namespace TopoR
