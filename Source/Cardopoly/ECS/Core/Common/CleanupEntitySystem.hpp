#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

template<typename T>
class CleanupEntitySystem : public IGameplaySystem
{
public:
    CleanupEntitySystem(flecs::world* world)
        : IGameplaySystem(world), _world(world)
    {
    }

    virtual void Initialize() override
    {
        _world->system<T>()
            .each([](flecs::entity entity, const T& component)
            {
                entity.destruct();
            });
    }

private:
    flecs::world* _world;
};
