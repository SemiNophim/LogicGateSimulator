#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QGraphicsScene>
#include <qtpreprocessorsupport.h>

#include "LED.h"

LED::LED(QGraphicsItem *parent) : LoadElement(parent) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    qreal r = getGridSize();
    
    Pin inPin;
    inPin.id = Pin::generateUniqueId(); 
    inPin.parentElement = this;
    inPin.localPos = QPointF(-r, 0);
    inPin.type = PinType::Input;
    m_pins.push_back(inPin);

    Pin outPin;
    outPin.id = Pin::generateUniqueId(); 
    outPin.parentElement = this;
    outPin.localPos = QPointF(r, 0);
    outPin.type = PinType::Output; 
    m_pins.push_back(outPin);
}

void LED::setInputValue(int pinId, float voltage) {
    Q_UNUSED(pinId);

    currentVoltage = voltage;
    update(); 
}

float LED::getOutputValue(int pinId) const {
    Q_UNUSED(pinId);

    if(currentVoltage >= thresholdVoltage){
        return currentVoltage;
    }
    return 0.0f;
}

QRectF LED::boundingRect() const {
    qreal r = getGridSize();

    return QRectF(-r - 5, -r - 5, 2 * r + 10, 2 * r + 10);
}

void LED::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal r = getGridSize();
    prepareGeometryChange(); 

    painter->setPen(QPen(Qt::black, 2));
    if (currentVoltage >= 4.8f) { 
        painter->setBrush(QBrush(Qt::yellow)); 
    } else {
        painter->setBrush(QBrush(Qt::darkGray));
    }

    qreal radius = r * 0.75; 
    painter->drawEllipse(QPointF(0, 0), radius, radius);
    
    qreal plusSize = radius * 0.3;
    painter->drawLine(-plusSize, 0, plusSize, 0);
    painter->drawLine(0, -plusSize, 0, plusSize);

    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(QPointF(-radius, 0), QPointF(-r, 0));
    
    painter->setBrush(QBrush(Qt::black));
    painter->setPen(Qt::NoPen); 
    painter->drawEllipse(QPointF(-r, 0), 3, 3); 

    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(QPointF(radius, 0), QPointF(r, 0)); 
    
    painter->setBrush(QBrush(Qt::black));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QPointF(r, 0), 3, 3); 
}

