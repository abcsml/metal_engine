#pragma once
#include "common.h"

// enum UnitType {
//     RenderUnit
// };

class Unit {
public:
    // Unit();
    virtual ~Unit() {};
    // virtual void update();
};

class RenderUnit: public Unit {
public:
    struct VertexData {
        std::vector<simd::float3> vertices;
        std::vector<std::uint16_t> vertexIndices;
        MTL::PrimitiveType primitiveType;
    } vertexData;

    MTL::Buffer* vertexBuffer;
    // MTL::Buffer* vertexIndexBuffer;

    RenderUnit(VertexData vertexData) {
        vertexData = vertexData;
        vertexBuffer = MTLEngine::getDevice()->newBuffer(
            vertexData.vertices.data(),
            3 * sizeof(simd::float3),
            MTL::ResourceStorageModeShared
        );

        if (vertexData.vertexIndices.size()) {
        }
    };
};

class TestUnit: public Unit {
public:
    MTL::Buffer* vertexBuffer;
    // MTL::Buffer* vertexIndexBuffer;

    TestUnit() {
        simd::float3 triangleVertices[] = {
            {-0.5f, -0.5f, 0.0f},
            { 0.5f, -0.5f, 0.0f},
            { 0.0f,  0.5f, 0.0f}
        };
        vertexBuffer = MTLEngine::getDevice()->newBuffer(
            triangleVertices,
            3 * sizeof(simd::float3),
            MTL::ResourceStorageModeShared
        );
    };
};
