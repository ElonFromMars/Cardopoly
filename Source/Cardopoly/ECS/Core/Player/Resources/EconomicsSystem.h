#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class EconomicsSystem : public IGameplaySystem
{
public:
	EconomicsSystem(
		flecs::world* flecsWorld
		)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
};

