#pragma once
#include <unordered_map>
#include <typeindex>
using namespace std;

// #include "common.h"

#include "unit.h"
#include "spdlog/spdlog.h"

// class Entity {
// public:
//     TestUnit* test;
//     RenderUnit* render;
// };

using Entity = size_t;

class EntityManager {
public:
    Entity createEntity() {
        spdlog::trace("create Entity {}", nextEntityId);
        nextEntityId ++;
        assert(nextEntityId); // 检查溢出
        return nextEntityId-1;
    };

    void deleteEntity(Entity entity) {
        for (auto& unit: entityTable_[entity]) {
            // 释放unit
            delete unitTable_[unit.first][entity];
            unitTable_[unit.first].erase(entity);
        }
        entityTable_.erase(entity);
    };

    template <typename U>
    void addUnit(Entity entity, U* unit) {
        type_index typeId = type_index(typeid(U));
        entityTable_[entity][typeId] = unit;
        unitTable_[typeId][entity] = unit;
    };

    // template <typename U>
    // void removeUnit(Entity entity, U unit) {
    //     type_index typeId = type_index(typeid(U));
    //     entityTable[entity][typeId] = &unit;
    //     unitTable[typeId][entity] = &unit;
    // };

    template <typename U>
    U* getUnit(Entity entity) const {
        type_index typeId = type_index(typeid(U));
        auto unit = entityTable_.at(entity).find(typeId);
        if (unit != entityTable_.at(entity).end()) {
            return static_cast<U*>(unit->second);
        }
        return nullptr;
    };

    template <typename U>
    bool hasUnit(Entity entity) const {
        type_index typeId = type_index(typeid(U));
        auto unit = entityTable_.at(entity).find(typeId);
        return unit != entityTable_.at(entity).end();
    }

    template <typename U, typename Func>
    void forEach(Func&& func) const {
        type_index typeId = type_index(typeid(U));
        auto vec = unitTable_.find(typeId);
        if (vec != unitTable_.end()) {
            for (auto& unit: vec->second) {
                func(unit.first, static_cast<U*>(unit.second));
            }
        }
    };

    template <typename Func>
    vector<Entity> forEachEntity(Func func) const {
        vector<Entity> ets;
        ets.reserve(entityTable_.size());
        std::for_each(entityTable_.begin(), entityTable_.end(),
            [&ets, func](auto& p){ if (func(p.first)) ets.emplace_back(p.first); }
        );
        return ets;
    };

private:
    unordered_map<Entity, unordered_map<type_index, Unit*>> entityTable_;
    unordered_map<type_index, unordered_map<Entity, Unit*>> unitTable_;

    Entity nextEntityId = 0;
};
