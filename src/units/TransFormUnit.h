#pragma once

#include "units/Unit.h"
#include "simd/simd.h"

using TransFormData = simd::float3x3;

class TransFormUnit: public Unit {
public:
    TransFormData data_;

    TransFormUnit();
    TransFormUnit(TransFormData data): data_(data) {};
    TransFormUnit(float x, float y) {
        data_ = {
            simd::make_float3(1,0,x),
            simd::make_float3(0,1,y),
            simd::make_float3(0,0,1),
        };
    };

    simd::float2 getPosition() const {
        return simd::make_float2(data_.columns[0].z, data_.columns[1].z);
    }

    void setPosition(float x, float y) {
        data_.columns[0].z = x;
        data_.columns[1].z = y;
    }
};
