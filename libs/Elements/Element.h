#pragma once
#include <QGraphicsItem>
#include <QString>

#include "Pin.h"

class Element : public QGraphicsObject { 
    Q_OBJECT
public:
    Element (QGraphicsItem *parent = nullptr) : QGraphicsObject(parent) {}
    virtual ~Element() = default;

    static void setGridSize(int gridSize);
    static int getGridSize();

    const std::vector<Pin>& getPins() const { return m_pins; }
    std::vector<Pin>& getPins();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
    std::vector<Pin> m_pins; 
    int m_id;

private:
    static int m_gridSize;
};

