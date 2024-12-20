#pragma once

#include "units/Unit.h"
#include "simd/simd.h"
#include "ShapeUnit.h"

class PhysicUnit: public Unit {
public:
    float m_;
    struct V {
        float x;
        float y;
    } v_;

    ShapeUnit* collisionBox_ = nullptr;

    PhysicUnit(float m = 1, V v = {0, 0}): m_(m), v_(v) {};

    void addCollisionBox(ShapeUnit* collisionBox) {
        collisionBox_ = collisionBox;
    }
};
