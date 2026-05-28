#include <QGraphicsScene>

#include "Element.h"
#include "LED.h"

int Element::m_gridSize = 20;

void Element::setGridSize(int gridSize) {
if (gridSize <= 0 || m_gridSize == gridSize || gridSize >= 100) return;
    
    m_gridSize = gridSize;
}

int Element::getGridSize(){
    return m_gridSize;
}



void Element::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsObject::mouseReleaseEvent(event);

    QPointF currentPos = this->pos();
    int step = getGridSize();
    qreal snappedX = std::round(currentPos.x() / step) * step;
    qreal snappedY = std::round(currentPos.y() / step) * step;
    this->setPos(snappedX, snappedY);

    if (scene()) {
        for (QGraphicsItem* item : scene()->items()) {
            LED* led = dynamic_cast<LED*>(item);
            if (led) {
                led->checkInputConnection();
            }
        }
    }
}


