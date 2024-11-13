#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class EconomySystem : public IGameplaySystem
{
public:
	EconomySystem(
		flecs::world* flecsWorld
		)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
};

