#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class GridLayout;
class UGameplayAssetData;

class InitializeGridPositionSystem : public IGameplaySystem
{
public:
	InitializeGridPositionSystem(
		flecs::world* flecsWorld,
		GridLayout* gridLayout,
		UWorld* viewWorld
		)
		: IGameplaySystem(flecsWorld)
	{
		_gridLayout = gridLayout;
		_viewWorld = viewWorld;
	}

	virtual void Initialize() override;
	
	GridLayout* _gridLayout;
	UWorld* _viewWorld;
};
