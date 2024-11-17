#pragma once

#include "flecs.h"
#include "Cardopoly/City/CityGrid.h"
#include "Cardopoly/ECS/Core/Citizens/Systems/CitizensInitializeSystem.h"
#include "Cardopoly/ECS/Core/Debug/Systems/DrawDebugViewSystem.h"
#include "Cardopoly/ECS/Core/Movement/Systems/MovementSystem.h"
#include "Cardopoly/ECS/Core/Pathfinding/Systems/PathfindingSystem.h"
#include "Cardopoly/ECS/Infrastructure/Factories/ISystemFactory.h"
#include "Cardopoly/Grid/UGridSubsystem.h"
#include "Cardopoly/Pathfinding/AStar.h"
#include "Cardopoly/UI/UHUDWidget.h"
#include "Cardopoly/Utils/TypeIdUtils.h"

class UGameplayAssetData;
class IGameplaySystem;

class CoreGameplaySystemsFactory : public ISystemFactory
{
public:
	CoreGameplaySystemsFactory(
		flecs::world* world,
		UGridSubsystem* gridSubsystem,
		UCityGrid* cityGrid,
		Pathfinding::AStar* aStar,
		UWorld* viewWorld,
		UHUDWidget* hudWidget,
		UGameplayAssetData* gameplayAssetData
	) :
		_gridSubsystem(gridSubsystem),
		_cityGrid(cityGrid),
		_aStar(aStar),
		_world(world),
		_viewWorld(viewWorld),
		_hudWidget(hudWidget),
		_gameplayAssetData(gameplayAssetData)
	{
	}

	virtual IGameplaySystem* Create(uintptr_t typeId) override;

private:
	UGridSubsystem* _gridSubsystem;
	UCityGrid* _cityGrid;
	Pathfinding::AStar* _aStar;
	flecs::world* _world;
	UWorld* _viewWorld;
	UHUDWidget* _hudWidget;
	UGameplayAssetData* _gameplayAssetData;
};
