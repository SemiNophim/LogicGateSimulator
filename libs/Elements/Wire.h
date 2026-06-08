#pragma once
#include <QGraphicsPathItem>
#include <QPen>
#include "Pin.h"

class Wire : public QGraphicsPathItem {
public:
    Wire(Pin* startPin, Pin* endPin, QGraphicsItem* parent = nullptr);

    void updatePath(QPointF manualEndPoint = QPointF());

    void setVoltage(float voltage);
    float getVoltage() const { return m_voltage; }

    Pin* startPin() const { return m_startPin; }
    Pin* endPin() const { return m_endPin; }

    Pin* getOppositePin(Pin* currentPin) {
        if (currentPin == m_startPin) return m_endPin;
        if (currentPin == m_endPin) return m_startPin;
        return nullptr;
    }

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Pin* m_startPin;
    Pin* m_endPin;
    float m_voltage = 0.0f; 
};

