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
