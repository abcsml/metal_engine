#pragma once

#include "common.h"
#include "units/Unit.h"
#include "units/ShapeUnit.h"
#include "units/TransFormUnit.h"

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

struct RenderConfig {
    bool useIndex = false;
    bool useTransform = false;
    // bool useTexture = false;
    uint32_t vertexCount;
    MTL::PrimitiveType primitiveType;
    uint32_t vertexIndexCount;
    MTL::IndexType vertexIndexType = MTL::IndexTypeUInt16;
};

struct RenderData {
    MTL::Buffer* vertexBuffer;
    MTL::Buffer* vertexIndexBuffer;
    MTL::Buffer* transformBuffer;
};

class RenderUnit: public Unit {
public:
    RenderConfig config_;
    RenderData data_;

    // 关联其他unit
    TransFormUnit* transformUnit_;

    RenderUnit();
    RenderUnit(RenderConfig config, RenderData data): config_(config), data_(data) {};
    RenderUnit(VertexUnit* vertex, VertexIndexUnit* index = nullptr);
    RenderUnit(ShapeUnit* shape);
    ~RenderUnit();

    void addTransform(TransFormUnit* transform);
};

class ColorUnit: public Unit {
public:
    union ColorData {
        uint32_t rgba;
        struct {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        } data;
    } colorData_;

    ColorUnit(ColorData colorData): colorData_(colorData) {};
};

class FragmentShaderUnit: public Unit {
public:
    std::string fragmentShader_;

    FragmentShaderUnit(std::string fragmentShader): fragmentShader_(fragmentShader) {};
};
