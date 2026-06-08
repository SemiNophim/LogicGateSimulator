#include <QPen>
#include <QBrush>
#include <QPainter>

#include "DCPower.h"

DCPower::DCPower(QGraphicsItem *parent) : Element(parent) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    qreal r = getGridSize();

    Pin outPin;
    outPin.id = Pin::generateUniqueId(); 
    outPin.parentElement = this;
    outPin.localPos = QPointF(r, 0); 
    outPin.type = PinType::Output;
    
    m_pins.push_back(outPin);
}

float DCPower::getOutput() {
    return m_outputValue;
}

void DCPower::setValue(float value) {
    m_outputValue = value;
    update(); 
}

QRectF DCPower::boundingRect() const {
    qreal r = getGridSize(); 
    qreal paddingRight = r / 12; 
    
    return QRectF(-r, -r, (r * 2) + paddingRight, r * 2); 
}

void DCPower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal r = getGridSize();

    prepareGeometryChange(); 

    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QBrush(Qt::yellow)); 

    qreal radius = r * 0.75;
    painter->drawEllipse(QPointF(0, 0), radius, radius);
    
    qreal plusSize = radius * 0.3;
    painter->drawLine(-plusSize, 0, plusSize, 0);
    painter->drawLine(0, -plusSize, 0, plusSize);

    painter->drawLine(radius, 0, r, 0);    
    
    painter->setBrush(QBrush(Qt::black));
    painter->drawEllipse(r - 2, -2, 4, 4);
}

