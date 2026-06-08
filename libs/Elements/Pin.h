#pragma once
#include <QPointF>
#include <vector>

class Element; 
class Wire;

enum class PinType {
    BiDirectional,
    Input,
    Output
};

struct Pin {
    int id;
    Element* parentElement;
    QPointF localPos;
    PinType type;
    int wireNetId = -1;

    std::vector<Wire*> connectedWires;

    QPointF globalPos() const;

    static int generateUniqueId() {
        static int currentId = 0; 
        return ++currentId;      
    }
};

