#pragma once
#include "PowerElement.h"

class DCPower : public PowerElement {
    Q_OBJECT 
public:
    explicit DCPower(QGraphicsItem *parent = nullptr);

    float getOutputVoltage() const override;
    void setValue(float value);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float m_outputValue = 5.0f; 
};

