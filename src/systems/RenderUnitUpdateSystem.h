#pragma once

#include "systems/System.h"

class RenderUnitUpdateSystem: public System {
public:
    bool filter(Entity entity) const override {
        RenderUnit* render = em_->getUnit<RenderUnit>(entity);
        return render && render->transformUnit_ && render->config_.useTransform;
    };

    void task(Entity entity) override {
        RenderUnit* render = em_->getUnit<RenderUnit>(entity);
        memcpy(render->data_.transformBuffer->contents(), &render->transformUnit_->data_, sizeof(TransFormData));
    };
};