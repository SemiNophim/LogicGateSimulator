#pragma once
#include <QGraphicsItem>
#include <QString>

#include "Pin.h"
#include "ElementType.h"

class Element : public QGraphicsObject { 
    Q_OBJECT
public:
    Element (QGraphicsItem *parent = nullptr) : QGraphicsObject(parent) {}
    virtual ~Element() = default;

    static void setGridSize(int gridSize);
    static int getGridSize();

    const std::vector<Pin>& getPins() const { return m_pins; }
    std::vector<Pin>& getPins();


    virtual ElementType getElementType() const = 0;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
    std::vector<Pin> m_pins; 
    int m_id;

private:
    static int m_gridSize;
};

inline QString elementTypeToString(ElementType type) {
    switch (type) {
        case ElementType::DCPower: return "DCPower";
        case ElementType::LED:     return "LED";
        case ElementType::Ground:  return "Ground";
    }
    return "Unknown";
}

