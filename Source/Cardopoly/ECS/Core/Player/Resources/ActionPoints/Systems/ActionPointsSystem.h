#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class ActionPointsSystem : public IGameplaySystem
{
public:
	ActionPointsSystem(
		flecs::world* flecsWorld
	)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
};
