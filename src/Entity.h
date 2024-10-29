#pragma once
#include <unordered_map>
#include <typeindex>
using namespace std;

#include "common.h"

#include "Unit.h"

// class Entity {
// public:
//     TestUnit* test;
//     RenderUnit* render;
// };

using Entity = size_t;

class EntityManager {
public:
    Entity createEntity() {
        nextEntityId ++;
        assert(nextEntityId); // 检查溢出
        return nextEntityId--;
    };

    void deleteEntity(Entity entity) {
        for (auto& unit: entityTable[entity]) {
            // 释放unit
            delete unitTable[unit.first][entity];
            unitTable[unit.first].erase(entity);
        }
        entityTable.erase(entity);
    };

    template <typename U>
    void addUnit(Entity entity, U* unit) {
        type_index typeId = type_index(typeid(U));
        entityTable[entity][typeId] = unit;
        unitTable[typeId][entity] = unit;
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
        auto unit = entityTable.at(entity).find(typeId);
        if (unit != entityTable.at(entity).end()) {
            return static_cast<U*>(unit->second);
        }
        return nullptr;
    };

    template <typename U>
    bool hasUnit(Entity entity) const {
        type_index typeId = type_index(typeid(U));
        auto unit = entityTable.at(entity).find(typeId);
        return unit != entityTable.at(entity).end();
    }

    template <typename U, typename Func>
    void forEach(Func&& func) const {
        type_index typeId = type_index(typeid(U));
        auto vec = unitTable.find(typeId);
        if (vec != unitTable.end()) {
            for (auto& unit: vec->second) {
                func(unit.first, static_cast<U*>(unit.second));
            }
        }
    };

private:
    unordered_map<Entity, unordered_map<type_index, Unit*>> entityTable;
    unordered_map<type_index, unordered_map<Entity, Unit*>> unitTable;

    Entity nextEntityId = 0;
};
