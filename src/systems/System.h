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
    
    // update默认自动化更新
    virtual void update() {
        vector<Entity> ets = em_->forEachEntity([this](Entity e){
            return filter(e);
        });
        for(auto& e: ets) {
            task(e);
        }
    };

    virtual bool filter(Entity entity) const { return false; };
    virtual void task(Entity entity) {};
};
