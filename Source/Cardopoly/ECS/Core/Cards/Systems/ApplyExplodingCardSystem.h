#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class CitizenGridService;

class ApplyExplodingCardSystem : public IGameplaySystem
{
public:
	ApplyExplodingCardSystem(
		flecs::world* flecsWorld,
		CitizenGridService* citizenGridService
	)
		: IGameplaySystem(flecsWorld),
		_citizenGridService(citizenGridService)
	{
	}

	virtual void Initialize() override;

private:
	CitizenGridService* _citizenGridService;
};
