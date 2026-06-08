#include <QGraphicsScene>

#include "Element.h"
#include "Pin.h"

int Element::m_gridSize = 20;

void Element::setGridSize(int gridSize) {
if (gridSize <= 0 || m_gridSize == gridSize || gridSize >= 100) return;
    
    m_gridSize = gridSize;
}

int Element::getGridSize(){
    return m_gridSize;
}

QPointF Pin::globalPos() const {
    if (!parentElement) return QPointF();
    return parentElement->mapToScene(localPos);
}

void Element::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsObject::mouseReleaseEvent(event);
}

std::vector<Pin>& Element::getPins() {
    return m_pins; 
}

