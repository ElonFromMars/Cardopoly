﻿#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/GridLayout.h"

class CitizenGridService;

class CitizensInitializeSystem : public IGameplaySystem
{
public:
	CitizensInitializeSystem(
		flecs::world* flecsWorld,
		GridLayout* gridLayout,
		CitizenGridService* citizenGridService
		)
		: IGameplaySystem(flecsWorld),
		_gridLayout(gridLayout),
		_citizenGridService(citizenGridService)
	{
	}

	virtual void Initialize() override;

private:
	GridLayout* _gridLayout;
	CitizenGridService* _citizenGridService;
};
