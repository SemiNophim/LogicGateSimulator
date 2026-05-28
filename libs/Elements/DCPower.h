#pragma once
#include "Element.h"

class DCPower : public Element {
    Q_OBJECT 
public:
    explicit DCPower(QGraphicsItem *parent = nullptr);

    float getOutput() override;
    void setValue(float value);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float m_outputValue = 5.0f; 
};

