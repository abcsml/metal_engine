#pragma once

#include "systems/System.h"

class ClockSystem : public System {
private:
    ClockUnit* clock_;
public:
    void init(EntityManager* em) override {
        clock_ = em->getUnit<ClockUnit>(0);
        clock_->startTime_ = std::chrono::steady_clock::now();
        clock_->lastTime_ = std::chrono::steady_clock::now();
    };

    void update() override {
        clock_->circleTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - clock_->lastTime_
        );

        clock_->runTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - clock_->startTime_
        );

        clock_->lastTime_ = std::chrono::steady_clock::now();
    };
};
