#pragma once
#include "common.h"

#include "World.h"
#include <cstdio>

class System {
public:
    // System();
    virtual ~System() {};
    // virtual void init();
    virtual void update(CA::MetalDrawable* drawable) {};
};

class RenderSystem : public System {
private:
    std::vector<Entity*>* datas;

    MTL::RenderPipelineState* metalRenderPSO;

public:
    RenderSystem(std::vector<Entity*>* datas) : datas(datas) {
        createRenderPipeline();
    };

    void update(CA::MetalDrawable* drawable) override {
        sendRenderCommand(drawable);
    };
private:
    void createRenderPipeline() {
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
        metalRenderPSO = device->newRenderPipelineState(renderPipelineDescriptor, &error);
        // printf("error:%ld\n", error->code());
        // assert(metalRenderPSO);
        
        vertexDescriptor->release();
        renderPipelineDescriptor->release();
    }

    void sendRenderCommand(CA::MetalDrawable* drawable) {
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

    void encodeRenderCommand(MTL::RenderCommandEncoder* renderCommandEncoder) {
        renderCommandEncoder->setRenderPipelineState(metalRenderPSO);

        // 遍历RenderUnit，逐个渲染
        for (auto entity: *datas) {
            if (entity->test) {
                renderCommandEncoder->setVertexBuffer(entity->test->vertexBuffer, 0, 0);
                renderCommandEncoder->drawPrimitives(
                    MTL::PrimitiveTypeTriangle,
                    (NS::UInteger)0,
                    (NS::UInteger)3
                );
            }
            if (entity->render) {
                renderCommandEncoder->setVertexBuffer(entity->render->vertexBuffer, 0, 0);
                renderCommandEncoder->drawPrimitives(
                    entity->render->vertexData.primitiveType,
                    (NS::UInteger)0,
                    (NS::UInteger)3
                );
            }
        }

        // renderCommandEncoder->setVertexBuffer(vertexBuffer, 0, 0);
        // renderCommandEncoder->setVertexBuffer(indexBuffer, 0, 1);
        // renderCommandEncoder->drawPrimitives(shape->obj.primitiveType, shape->obj.vertexStart, shape->obj.vertexCount);

        // renderCommandEncoder->drawIndexedPrimitives(
        //     shape->obj.primitiveType,
        //     shape->obj.vertexIndexCount,
        //     MTL::IndexTypeUInt16,
        //     indexBuffer,
        //     0
        // );
    }
};
