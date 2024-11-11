#pragma once

#include <simd/simd.h>
#include "units/Unit.h"

enum ShapeType {
    Triangle,
    Circle,
    Rectangle
};

struct TriangleShapeData {
    simd::float2 center;
    // 以中心点为原点，三个顶点的坐标
    simd::float2 A;
    simd::float2 B;
    simd::float2 C;
};

struct CircleShapeData {
    simd::float2 center;
    float radius;
};

struct RectangleShapeData {
    simd::float2 center;
    // 以中心为原点，再确定两个点，以这两个点做原点对称得到四个点
    simd::float2 A;
    simd::float2 B;
};

class ShapeUnit: public Unit {
public:
    ShapeType type_;

    // 三选一
    TriangleShapeData triangle_;
    CircleShapeData circle_;
    RectangleShapeData rectangle_;

    uint32_t color_; // RGBA
    bool onlyFrame_; // 只留边框

    ShapeUnit(ShapeType type, uint32_t color): type_(type), color_(color) {
        // TODO
    }
};
