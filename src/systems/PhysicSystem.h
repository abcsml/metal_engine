#pragma once

#include "systems/System.h"

class PhysicSystem: public System {
public:
    bool filter(Entity entity) const override {
        return em_->hasUnit<TransFormUnit>(entity) &&
            em_->hasUnit<PhysicUnit>(entity);
    };

    void task(Entity entity) override {
        float deltaT = em_->getUnit<ClockUnit>(0)->getDeltaTime();

        TransFormUnit* pos = em_->getUnit<TransFormUnit>(entity);
        PhysicUnit* phy = em_->getUnit<PhysicUnit>(entity);
        pos->data_.columns[0].z += phy->v_.x * deltaT;
        pos->data_.columns[1].z += phy->v_.y * deltaT;

        phy->v_.y += -9.8f * deltaT;
    };
};