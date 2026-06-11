#pragma once
#include "Element.h"

class PowerElement : public Element {
    Q_OBJECT
public:
    using Element::Element; 
    ~PowerElement() override = default;

    virtual float getOutputVoltage() const = 0; 
};

