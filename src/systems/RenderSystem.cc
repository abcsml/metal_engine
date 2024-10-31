#include "RenderSystem.h"
#include "spdlog/spdlog.h"
#include "MTLEngine.h"

void RenderSystem::init(EntityManager* em) {
    spdlog::info("RenderSystem init");
    em_ = em;
    createRenderPipeline();
};

void RenderSystem::update() {
    sendRenderCommand(MTLEngine::getCurrentDrawable());
};
void RenderSystem::createRenderPipeline() {
    MTL::Library* metalDefaultLibrary = MTLEngine::getLibrary();
    MTL::Function* vertexShader = metalDefaultLibrary->newFunction(NS::String::string("vertexShader", NS::ASCIIStringEncoding));
    assert(vertexShader);
    MTL::Function* fragmentShader = metalDefaultLibrary->newFunction(NS::String::string("fragmentShader", NS::ASCIIStringEncoding));
    assert(fragmentShader);

    // default vetex descriptor
    MTL::VertexDescriptor* vertexDescriptor = MTL::VertexDescriptor::alloc()->init();
    MTL::VertexAttributeDescriptor* vd = vertexDescriptor->attributes()->object(0);
    vd->setFormat(MTL::VertexFormatFloat3);
    vd->setOffset(0);
    vd->setBufferIndex(0);
    vertexDescriptor->layouts()->object(0)->setStride(sizeof(simd::float3));
    
    MTL::RenderPipelineDescriptor* renderPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    renderPipelineDescriptor->setLabel(NS::String::string("Triangle Rendering Pipeline", NS::ASCIIStringEncoding));
    renderPipelineDescriptor->setVertexFunction(vertexShader);
    renderPipelineDescriptor->setFragmentFunction(fragmentShader);
    assert(renderPipelineDescriptor);
    MTL::PixelFormat pixelFormat = MTL::PixelFormat::PixelFormatBGRA8Unorm;
    renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(pixelFormat);
    renderPipelineDescriptor->setVertexDescriptor(vertexDescriptor);
        
    NS::Error* error;
    MTL::Device* device = MTLEngine::getDevice();
    metalRenderPSO_ = device->newRenderPipelineState(renderPipelineDescriptor, &error);
    // printf("error:%ld\n", error->code());
    // assert(metalRenderPSO);
    
    vertexDescriptor->release();
    renderPipelineDescriptor->release();
}

void RenderSystem::sendRenderCommand(CA::MetalDrawable* drawable) {
    MTL::CommandBuffer* metalCommandBuffer = MTLEngine::getCommandQueue()->commandBuffer();
    
    MTL::RenderPassDescriptor* renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor* cd = renderPassDescriptor->colorAttachments()->object(0);
    cd->setTexture(drawable->texture());
    cd->setLoadAction(MTL::LoadActionClear);
    cd->setClearColor(MTL::ClearColor(41.0f/255.0f, 42.0f/255.0f, 48.0f/255.0f, 1.0));
    cd->setStoreAction(MTL::StoreActionStore);
    
    MTL::RenderCommandEncoder* renderCommandEncoder = metalCommandBuffer->renderCommandEncoder(renderPassDescriptor);
    encodeRenderCommand(renderCommandEncoder);
    renderCommandEncoder->endEncoding();

    metalCommandBuffer->presentDrawable(drawable);
    metalCommandBuffer->commit();
    metalCommandBuffer->waitUntilCompleted();
    
    renderPassDescriptor->release();
}   

void RenderSystem::encodeRenderCommand(MTL::RenderCommandEncoder* renderCommandEncoder) {
    renderCommandEncoder->setRenderPipelineState(metalRenderPSO_);

    em_->forEach<RenderUnit>([&](Entity entity, RenderUnit* unit) {
        // position
        PositionUnit* posUnit = em_->getUnit<PositionUnit>(entity);
        if (posUnit) {
            simd::float2 pos;
            pos.x = posUnit->data_.x;
            pos.y = posUnit->data_.y;
            memcpy(unit->transformBuffer_->contents(), &pos, sizeof(simd_float2));
        }

        if (unit->useTransform_) {
            renderCommandEncoder->setVertexBuffer(unit->transformBuffer_, 0, 1);
        }

        renderCommandEncoder->setVertexBuffer(unit->vertex_.buffer, 0, 0);
        renderCommandEncoder->drawPrimitives(
            unit->vertex_.primitiveType,
            (NS::UInteger)unit->vertex_.start,
            (NS::UInteger)unit->vertex_.count
        );
    });
}
