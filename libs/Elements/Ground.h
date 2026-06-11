#pragma once
#include "LoadElement.h"

class Ground : public LoadElement {
    Q_OBJECT
public:
    Ground(QGraphicsItem *parent = nullptr);
    ~Ground() override = default;

    void setInputValue(int pinId, float voltage) override;
    float getOutputValue(int pinId) const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

