#pragma once
#include "Element.h"

class Ground : public Element {
    Q_OBJECT
public:
    Ground(QGraphicsItem *parent = nullptr);
    ~Ground() override = default;

    float getOutput() override { return 0.0f; } 

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

