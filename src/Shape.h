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

    static RenderUnit* genQuad(float l, float w);
    static RenderUnit* genQuad(float ratio = 0.1);

    static RenderUnit* genCircle(float r, int n);
    static RenderUnit* genCircle(float ratio = 0.1);
};
