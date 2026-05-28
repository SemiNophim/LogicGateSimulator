#include "ConstructorScheme.h"
#include <QPainter>
#include <QPen>
#include <cmath>
#include <Qt>

#include "Element.h"


ConstructorScheme::ConstructorScheme(QObject *parent) : QGraphicsScene(parent) {
    setSceneRect(0, 0, 2000, 2000);
    Element::setGridSize(m_gridSize);
}

void ConstructorScheme::addSchemeItem(Element *item){
    if(!item) return;

    m_items.push_back(item);
    addItem(item);
}

void ConstructorScheme::drawBackground(QPainter *painter, const QRectF &rect) {
    painter->fillRect(rect, Qt::white);

    QPen gridPen(Qt::lightGray, m_borderSize);
    painter->setPen(gridPen);

    qreal left = std::floor(rect.left() / m_gridSize) * m_gridSize;
    qreal top = std::floor(rect.top() / m_gridSize) * m_gridSize;

    for (qreal x = left; x <= rect.right(); x += m_gridSize) {
        painter->drawLine(x, rect.top(), x, rect.bottom());
    }

    for (qreal y = top; y <= rect.bottom(); y += m_gridSize) {
        painter->drawLine(rect.left(), y, rect.right(), y);
    }
}

void ConstructorScheme::setGridSize(int gridSize){
    if(gridSize <= 0 || m_gridSize == gridSize ||gridSize >= 100) return;

    Element::setGridSize(gridSize);
    m_gridSize = gridSize;
}

