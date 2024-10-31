#pragma once
#include "Entity.h"

class System {
protected:
    EntityManager* em_;
public:
    // System();
    virtual ~System() {};
    virtual void init(EntityManager* em) {
        em_ = em;
    };
    virtual void update(CA::MetalDrawable* drawable) {};
};
