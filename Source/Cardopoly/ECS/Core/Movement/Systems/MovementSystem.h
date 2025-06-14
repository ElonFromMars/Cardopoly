#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class CitizenGridService;
class GridLayout;

class MovementSystem : public IGameplaySystem
{
public:
	MovementSystem(flecs::world* world, GridLayout* gridLayout, CitizenGridService* citizenGridService) : IGameplaySystem(world)
	{
		_gridLayout = gridLayout;
		_citizenGridService = citizenGridService;
	}
	
	virtual void Initialize() override;

private:
	GridLayout* _gridLayout;
	CitizenGridService* _citizenGridService;
};
