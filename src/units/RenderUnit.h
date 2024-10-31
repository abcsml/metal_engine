#pragma once

#include "common.h"
#include "units/Unit.h"

class VertexUnit: public Unit {
public:
    std::unique_ptr<simd::float3[]> vertices_;
};

class VertexIndexUnit: public Unit {
public:
    std::unique_ptr<std::uint16_t[]> vertexIndices_;
};

class RenderUnit: public Unit {
public:
    bool useIndex_ = false;
    bool useTransform_ = false;
    // bool useTexture;

    struct Vertex {
        uint32_t start;
        uint32_t count;
        MTL::PrimitiveType primitiveType;
        MTL::Buffer* buffer;
    } vertex_;

    struct VertexIndex {
        uint32_t count;
        MTL::IndexType type;
        MTL::Buffer* buffer;
    } vertexIndex_;

    MTL::Buffer* transformBuffer_;
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
