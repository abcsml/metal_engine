#include "RenderUnit.h"
#include "MTLEngine.h"

RenderUnit::RenderUnit(VertexUnit* vertex, VertexIndexUnit* index) {
    config_.vertexCount = vertex->data_.size();
    config_.primitiveType = MTL::PrimitiveTypeTriangleStrip;
    data_.vertexBuffer = MTLEngine::getDevice()->newBuffer(
        vertex->data_.data(),
        config_.vertexCount*sizeof(VertexData),
        MTL::ResourceStorageModeShared
    );

    if (index) {
        config_.useIndex = true;
        config_.vertexIndexCount = index->data_.size();
        data_.vertexIndexBuffer = MTLEngine::getDevice()->newBuffer(
            index->data_.data(),
            config_.vertexIndexCount*sizeof(uint16_t),
            MTL::ResourceStorageModeShared
        );
    }
}
RenderUnit::RenderUnit(ShapeUnit* shape) {
    // TODO
}

RenderUnit::~RenderUnit() {
    data_.vertexBuffer->release();
    data_.vertexIndexBuffer->release();
    data_.transformBuffer->release();
}

void RenderUnit::addTransform(TransFormUnit* transform) {
    transformUnit_ = transform;
    config_.useTransform = true;
    data_.transformBuffer = MTLEngine::getDevice()->newBuffer(
        sizeof(TransFormData),
        MTL::ResourceStorageModeShared
    );
}
