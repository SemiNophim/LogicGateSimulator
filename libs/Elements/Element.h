#pragma once
#include <QGraphicsItem>
#include <QString>

class Element : public QGraphicsObject { 
    Q_OBJECT
public:
    Element (QGraphicsItem *parent = nullptr) : QGraphicsObject(parent) {}
    virtual ~Element() = default;

    virtual float getOutput() = 0; 

    static void setGridSize(int gridSize);
    static int getGridSize();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static int m_gridSize;
};

