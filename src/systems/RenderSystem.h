#pragma once

#include "systems/System.h"

class RenderSystem : public System {
private:
    MTL::RenderPipelineState* metalRenderPSO_;

public:
    void init(EntityManager* em) override;
    void update() override;

private:
    void createRenderPipeline();
    void sendRenderCommand(CA::MetalDrawable* drawable);
    void encodeRenderCommand(MTL::RenderCommandEncoder* renderCommandEncoder);
};
