#pragma once

#include "systems/System.h"

class PhysicSystem: public System {
public:
    bool filter(Entity entity) const override {
        return em_->hasUnit<PositionUnit>(entity) &&
            em_->hasUnit<PhysicUnit>(entity);
    };

    void task(Entity entity) override {
        float deltaT = em_->getUnit<ClockUnit>(0)->getDeltaTime();

        PositionUnit* pos = em_->getUnit<PositionUnit>(entity);
        PhysicUnit* phy = em_->getUnit<PhysicUnit>(entity);
        pos->data_.x += phy->v_.x * deltaT;
        pos->data_.y += phy->v_.y * deltaT;

        phy->v_.y += -0.5f * deltaT;
    };
};