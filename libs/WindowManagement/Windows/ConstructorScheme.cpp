#include "ConstructorScheme.h"
#include <QPainter>
#include <QPen>
#include <cmath>
#include <Qt>

ConstructorScheme::ConstructorScheme(QObject *parent) : QGraphicsScene(parent) {
    setSceneRect(0, 0, 2000, 2000);
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

