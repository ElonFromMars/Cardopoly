#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGridSubsystem;

class MovementSystem : public IGameplaySystem
{
public:
	MovementSystem(flecs::world* world, UGridSubsystem* gridSubsystem) : IGameplaySystem(world)
	{
		_gridSubsystem = gridSubsystem;
	}
	
	virtual void Initialize() override;

private:
	UGridSubsystem* _gridSubsystem;
};
