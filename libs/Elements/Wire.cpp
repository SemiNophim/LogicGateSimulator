#include "Wire.h"
#include <QPainter>

#include "Element.h"

Wire::Wire(Pin* startPin, Pin* endPin, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_startPin(startPin), m_endPin(endPin) 
{
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
    
    updatePath();
}

void Wire::updatePath(QPointF manualEndPoint) {
    if (!m_startPin) return;
    
    QPointF p1 = m_startPin->globalPos();
    QPointF p2;

    if (m_endPin) {
        p2 = m_endPin->globalPos();
    } else {
        p2 = manualEndPoint;
    }

    QPainterPath path;
    path.moveTo(p1);

    qreal midX = p1.x() + (p2.x() - p1.x()) / 2.0;
    path.lineTo(midX, p1.y()); 
    path.lineTo(midX, p2.y()); 
    path.lineTo(p2);           

    setPath(path);
}

void Wire::setVoltage(float voltage) {
    m_voltage = voltage;
    update(); 
}

void Wire::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen currentPen = pen();

    if (m_voltage >= 3.5f) {
        currentPen.setColor(Qt::green); 
    } 
    else if (m_voltage <= 0.8f && m_voltage > -1.0f) {
        currentPen.setColor(Qt::red);    
    } 
    else {
        currentPen.setColor(Qt::darkGray); 
    }

    painter->setPen(currentPen);
    painter->drawPath(path());
}

