#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class LocalPlayerFlowSystem : public IGameplaySystem
{
public:
	LocalPlayerFlowSystem(
		flecs::world* flecsWorld
	)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
};
