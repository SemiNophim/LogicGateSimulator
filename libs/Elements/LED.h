#pragma once
#include "Element.h"

class LED : public Element {
    Q_OBJECT 
public:
    explicit LED(QGraphicsItem *parent = nullptr);

    void setValue(float value);

    float getOutput() override { return 0.0f; }

    void checkInputConnection();
    

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float maxBrightness = 5.0f; 
    float currentVoltage = 0;
};

