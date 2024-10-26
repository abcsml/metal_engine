#pragma once

#include <QuartzCore/QuartzCore.hpp>
#include "common.h"

class World {
private:
    std::vector<Entity*> entities;
    std::vector<System*> systems;

public:
    // World();
    virtual ~World() {};

    virtual void draw() {};

    void add(Entity* entity) {
        entities.push_back(entity);
    };

    void addSystem(System* system) {
        systems.push_back(system);
    };

    void update(CA::MetalDrawable* drawable) {
        for (auto system: systems) {
            system->update(drawable);
        }
    };

    std::vector<Entity*>* getEntities() {
        return &entities;
    }
};
