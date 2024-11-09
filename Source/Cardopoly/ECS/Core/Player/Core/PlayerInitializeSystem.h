#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class PlayerInitializeSystem : public IGameplaySystem
{
public:
	PlayerInitializeSystem(
		flecs::world* flecsWorld
		)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
};
