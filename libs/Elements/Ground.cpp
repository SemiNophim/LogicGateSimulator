#include "Ground.h"
#include <QPainter>

Ground::Ground(QGraphicsItem *parent) : Element(parent) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    qreal r = getGridSize();
    
    Pin inPin;
    inPin.id = Pin::generateUniqueId(); 
    inPin.parentElement = this;
    inPin.localPos = QPointF(0, -r); 
    inPin.type = PinType::Input;
    m_pins.push_back(inPin);
}

QRectF Ground::boundingRect() const {
    qreal r = getGridSize();
    return QRectF(-r - 5, -r - 5, 2 * r + 10, 2 * r + 10);
}

void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal r = getGridSize();
    prepareGeometryChange(); 

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(Qt::NoBrush);

    painter->drawLine(QPointF(0, -r), QPointF(0, r * 0.2));

    painter->drawLine(QPointF(-r * 0.6, r * 0.2), QPointF(r * 0.6, r * 0.2));
    painter->drawLine(QPointF(-r * 0.4, r * 0.5), QPointF(r * 0.4, r * 0.5));
    painter->drawLine(QPointF(-r * 0.2, r * 0.8), QPointF(r * 0.2, r * 0.8));

    painter->setBrush(QBrush(Qt::black));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QPointF(0, -r), 3, 3); 
}

