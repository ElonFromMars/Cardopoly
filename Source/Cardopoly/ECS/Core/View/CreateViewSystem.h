#pragma once

#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGridSubsystem;
class UGameplayAssetData;

class CreateViewSystem : public IGameplaySystem
{
public:
	CreateViewSystem(
		flecs::world* flecsWorld,
		UGameplayAssetData* gameplayAssetData,
		UWorld* viewWorld
		)
		: IGameplaySystem(flecsWorld)
	{
		_gameplayAssetData = gameplayAssetData;
		_viewWorld = viewWorld;
	}

	virtual void Initialize() override;

	UGameplayAssetData* _gameplayAssetData;
	UWorld* _viewWorld;
};
