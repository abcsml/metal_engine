#pragma once

#include "units/Unit.h"

class PositionUnit: public Unit {
public:
    struct Data {
        float x;
        float y;
    } data_;

    PositionUnit(Data data): data_(data) {};
};
