#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class TurnSystem : public IGameplaySystem
{
public:
	TurnSystem(flecs::world* world) : IGameplaySystem(world)
	{
		
	}
	
	virtual void Initialize() override;
};
