#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGridSubsystem;
class UGameplayAssetData;

class InitializeGridPositionSystem : public IGameplaySystem
{
public:
	InitializeGridPositionSystem(
		flecs::world* flecsWorld,
		UGridSubsystem* gridSubsystem,
		UWorld* viewWorld
		)
		: IGameplaySystem(flecsWorld)
	{
		_gridSubsystem = gridSubsystem;
		_viewWorld = viewWorld;
	}

	virtual void Initialize() override;
	
	UGridSubsystem* _gridSubsystem;
	UWorld* _viewWorld;
};
