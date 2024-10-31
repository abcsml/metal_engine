#pragma once

#include "units/Unit.h"
#include <chrono>

class ClockUnit: public Unit {
public:
    std::chrono::time_point<std::chrono::steady_clock> startTime_;
    std::chrono::time_point<std::chrono::steady_clock> lastTime_;
    std::chrono::milliseconds runTime_;
    std::chrono::milliseconds circleTime_;

    float getDeltaTime() {
        return circleTime_.count()/1000.0f;
    }
};