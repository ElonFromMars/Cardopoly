#pragma once

#include "flecs.h"

template<typename T>
class CleanupSystem : public IGameplaySystem
{
public:
    CleanupSystem(flecs::world* world)
        : IGameplaySystem(world), _world(world)
    {
    }

    virtual void Initialize() override
    {
        _world->system<T>()
            .each([](flecs::entity entity, const T& component)
            {
                entity.remove<T>();
            });
    }

private:
    flecs::world* _world;
};