#pragma once

#include <vector>
#include <simd/simd.h>
#include "units/Unit.h"

struct VertexData {
    simd::float2 position;
    uint32_t color;

    VertexData() {};
    VertexData(float x, float y, uint32_t c) {
        position.x = x;
        position.y = y;
        color = c;
    }
};

class VertexUnit: public Unit {
public:
    std::vector<VertexData> data_;
};

class VertexIndexUnit: public Unit {
public:
    std::vector<std::uint16_t> data_;
};
