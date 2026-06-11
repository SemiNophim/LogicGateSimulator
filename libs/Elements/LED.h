#pragma once
#include "LoadElement.h"

class LED : public LoadElement {
    Q_OBJECT 
public:
    explicit LED(QGraphicsItem *parent = nullptr);

    void setInputValue(int pinId, float voltage) override;
    float getOutputValue(int pinId) const override;


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float currentVoltage = 0.0f;
    float thresholdVoltage = 4.8f; 
};

