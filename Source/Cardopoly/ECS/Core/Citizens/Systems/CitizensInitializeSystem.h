#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/UGridSubsystem.h"

class CitizensInitializeSystem : public IGameplaySystem
{
public:
	CitizensInitializeSystem(
		flecs::world* flecsWorld,
		UGridSubsystem* gridSubsystem
		)
		: IGameplaySystem(flecsWorld),
		_gridSubsystem(gridSubsystem)
	{
	}

	virtual void Initialize() override;

private:
	UGridSubsystem* _gridSubsystem;
};
