#pragma once

#include <simd/simd.h>
#include "units/Unit.h"
#include "units/VertexUnit.h"

enum ShapeType {
    Circle,
    Triangle,
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
private:
    const int circleSmooth_ = 32;

public:
    ShapeType type_;

    // 三选一
    CircleShapeData circle_ = {
        {0,0},
        0.5
    };
    TriangleShapeData triangle_ = {
        {0,0},
        {-0.5,0},
        {0.5,0},
        {0,0.866}
    };
    RectangleShapeData rectangle_ = {
        {0,0},
        {-0.5,0.5},
        {0.5,0.5}
    };

    uint32_t color_ = 0; // RGBA
    bool onlyFrame_ = false; // 只留边框

    ShapeUnit(ShapeType type = Circle, uint32_t color = 0);

    VertexUnit genVertexUnit();
    VertexIndexUnit genVertexIndexUnit();
};
