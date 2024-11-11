#include <metal_stdlib>
using namespace metal;

using TransFormData = simd::float3x3;

struct VertexData {
    float2 position;
    uint32_t color;
};

struct VertexOut {
  float4 position [[position]];
  float4 color;
};

vertex VertexOut
vertexShader(uint vertexID [[vertex_id]],
             constant VertexData* vertexData,
             constant TransFormData* trans)
{
    float3 positions = float3(vertexData[vertexID].position, 1.0f);
    if (trans) {
        positions *= *trans;
    }

    VertexOut out {
        .position = float4(positions, 1.0f),
        .color = vertexData[vertexID].color
    };
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    return in.color;
}
