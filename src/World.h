#pragma once

#include "common.h"

#include "Entity.h"
#include "system.h"

class World {
private:
    std::vector<System*> systems;

public:
    EntityManager em_;
    // World();
    virtual ~World() {};

    virtual void setup() {};

    // void add(Entity* entity) {
    //     entities.push_back(entity);
    // };

    void addSystem(System* system) {
        system->init(&em_);
        systems.push_back(system);
    };

    void update() {
        for (auto& system: systems) {
            system->update();
        }
    };

};
