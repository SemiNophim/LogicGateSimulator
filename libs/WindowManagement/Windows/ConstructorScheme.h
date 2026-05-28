#pragma once 

#include <QWidget>
#include <QGraphicsScene>
#include <vector>

#include "Element.h"

class ConstructorScheme : public QGraphicsScene{
    Q_OBJECT 
public:
    explicit ConstructorScheme(QObject *parent = nullptr);

    void setGridSize(int gridSize);
    void setBorderSize(int borderSize) { this->m_borderSize = borderSize; }

    int getGridSize() { return m_gridSize; }
    int getBorderSize() { return m_borderSize; }

    void addSchemeItem(Element *item);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    int m_gridSize = 20;
    int m_borderSize = 2;

    std::vector<Element *> m_items;
};

