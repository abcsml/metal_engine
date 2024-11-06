#pragma once

#include "units/Unit.h"
#include "simd/simd.h"

class PhysicUnit: public Unit {
public:
    float m_;
    struct V {
        float x;
        float y;
    } v_;

    PhysicUnit(float m = 1, V v = {0, 0}): m_(m), v_(v) {};
};

class CollisionBoxUnit: public Unit {
public:
    struct CircleBox {
        simd::float2 center;
        float radius;
    };

    struct RectBox {
    };

    // std::vector<>
};
