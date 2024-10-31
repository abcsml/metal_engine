#pragma once

#include "common.h"
#include "unit.h"

class Shape {
public:
    enum Type {
        Triangle,
        Circle,
        Square
    };

    static RenderUnit* genTriangle(float points[3][2]);
    static RenderUnit* genTriangle(float ratio = 0.1);
};
