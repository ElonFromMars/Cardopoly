#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class GridLayout;

class MovementSystem : public IGameplaySystem
{
public:
	MovementSystem(flecs::world* world, GridLayout* gridLayout) : IGameplaySystem(world)
	{
		_gridLayout = gridLayout;
	}
	
	virtual void Initialize() override;

private:
	GridLayout* _gridLayout;
};
