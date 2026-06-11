#pragma once
#include "Element.h"

class LoadElement : public Element {
    Q_OBJECT
public:
    using Element::Element;
    ~LoadElement() override = default;

    virtual void setInputValue(int pinId, float voltage) = 0;

    virtual float getOutputValue(int pinId) const = 0;
};

