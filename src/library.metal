#include <metal_stdlib>
using namespace metal;

using TransFormData = simd::float3x3;

struct VertexData {
    float2 position [[attribute(0)]];
    uint32_t color [[attribute(1)]];
};

struct VertexOut {
  float4 position [[position]];
  float4 color;
};

vertex VertexOut
vertexShader(VertexData in [[stage_in]],
             constant TransFormData &trans [[buffer(1)]])
{
    float3 positions = float3(in.position, 1.0f);
    // if (trans) {
        positions *= trans;
    // }

    VertexOut out {
        .position = float4(positions.xy, 0.0f, 1.0f),
        .color = 1
        // float4((float)((in.color >> 24) & 0xFF) / 255.0, // R
        //     (float)((in.color >> 16) & 0xFF) / 255.0, // G
        //     (float)((in.color >> 8) & 0xFF) / 255.0,  // B
        //     (float)(in.color & 0xFF) / 255.0)        // A
    };
    return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    return in.color;
}
