#include "Shape.h"
#include "MTLEngine.h"

RenderUnit* Shape::genTriangle(float points[3][2]) {
    simd::float3 triangle[] = {
        {points[0][0], points[0][1], 0.0f},
        {points[1][0], points[1][1], 0.0f},
        {points[2][0], points[2][1], 0.0f}
    };
    RenderUnit* render = new RenderUnit;
    render->vertex_.start = 0;
    render->vertex_.count = 3;
    render->vertex_.primitiveType = MTL::PrimitiveTypeTriangle;
    render->vertex_.buffer =
        MTLEngine::getDevice()->newBuffer(triangle, 3*sizeof(simd::float3), MTL::ResourceStorageModeShared);
    return render;
}

RenderUnit* Shape::genTriangle(float ratio) {
    float x = std::sqrt(3)/2 * ratio;
    float y = 0.5 * ratio;
    float points[3][2] = {{-x,-y}, {x,-y}, {0.0f,x}};
    return genTriangle(points);
}

RenderUnit* Shape::genQuad(float l, float w) {
    simd::float3 quad[] = {
        {-l/2, w/2, 0.0f},
        {-l/2, -w/2, 0.0f},
        {l/2, w/2, 0.0f},
        {l/2, -w/2, 0.0f}
    };
    RenderUnit* render = new RenderUnit;
    render->vertex_.start = 0;
    render->vertex_.count = 4;
    render->vertex_.primitiveType = MTL::PrimitiveTypeTriangleStrip;
    render->vertex_.buffer =
        MTLEngine::getDevice()->newBuffer(quad, 4*sizeof(simd::float3), MTL::ResourceStorageModeShared);
    return render;
}

RenderUnit* Shape::genQuad(float ratio) {
    return genQuad(ratio, ratio);
}

RenderUnit* Shape::genCircle(float r, int n) {
    // float radius = r/cos(2*3.1415/2/n);
    float radius = r;
    simd::float3 *vertices = new simd::float3[n+1];
    std::uint16_t *vertexIndices = new std::uint16_t[3*(n+1)];
    for (int i = 0; i < n+1; ++i) {
        float y = radius*cos(1.0/n*i*2*3.1415)/2;
        float x = radius*sin(1.0/n*i*2*3.1415)/2;
        vertices[i] = {x, y, 0};

        vertexIndices[i*3] = n;
        vertexIndices[i*3+1] = i;
        vertexIndices[i*3+2] = i+1;
    }
    vertices[n] = {0, 0, 0};
    vertexIndices[3*n+1] = n-1;
    vertexIndices[3*n+2] = 0;

    RenderUnit* render = new RenderUnit;
    render->useIndex_ = true;
    render->vertex_.start = 0;
    render->vertex_.count = n+1;
    render->vertex_.primitiveType = MTL::PrimitiveTypeTriangleStrip;
    render->vertex_.buffer =
        MTLEngine::getDevice()->newBuffer(vertices, (n+1)*sizeof(simd::float3), MTL::ResourceStorageModeShared);
    render->vertexIndex_.count = 3*(n+1);
    render->vertexIndex_.type = MTL::IndexTypeUInt16;
    render->vertexIndex_.buffer =
        MTLEngine::getDevice()->newBuffer(vertexIndices, (3*(n+1))*sizeof(simd::float3), MTL::ResourceStorageModeShared);
    
    // 新问题： 相对大小与绝对大小

    return render;
}

RenderUnit* Shape::genCircle(float ratio) {
    return genCircle(ratio, 32);
}
