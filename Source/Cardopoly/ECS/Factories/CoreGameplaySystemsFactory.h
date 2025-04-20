#pragma once

#include "flecs.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/ECS/Core/Citizens/Systems/CitizensInitializeSystem.h"
#include "Cardopoly/ECS/Core/Debug/Systems/DrawDebugViewSystem.h"
#include "Cardopoly/ECS/Core/Movement/Systems/MovementSystem.h"
#include "Cardopoly/ECS/Core/Pathfinding/Systems/PathfindingSystem.h"
#include "Cardopoly/ECS/Core/Player/Common/Services/LocalPlayerService.h"
#include "Cardopoly/ECS/Core/Player/Resources/Services/ResourcesService.h"
#include "Cardopoly/ECS/Infrastructure/Factories/ISystemFactory.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/Pathfinding/AStar.h"
#include "Cardopoly/UI/UHUDWidget.h"
#include "Cardopoly/Utils/TypeIdUtils.h"

class UGameplayOverlayWidget;
class UHandLocalConfig;
class AHand;
class UGameplayAssetData;
class IGameplaySystem;

class CoreGameplaySystemsFactory : public ISystemFactory
{
public:
	CoreGameplaySystemsFactory(
		flecs::world* world,
		GridLayout* gridLayout,
		CityGridService* cityGrid,
		Pathfinding::AStar* aStar,
		UWorld* viewWorld,
		UHUDWidget* hudWidget,
		UGameplayOverlayWidget* entityOverlayWidget,
		UGameplayAssetData* gameplayAssetData,
		AHand* playerHand,
		UHandLocalConfig* handLocalConfig,
		LocalPlayerService* localPlayerService,
		ResourcesService* resourcesService,
		ULocalConfigHolder* localConfigHolder
	) :
		_gridLayout(gridLayout),
		_cityGrid(cityGrid),
		_aStar(aStar),
		_world(world),
		_viewWorld(viewWorld),
		_hudWidget(hudWidget),
		_entityOverlayWidget(entityOverlayWidget),
		_gameplayAssetData(gameplayAssetData),
		_playerHand(playerHand),
		_handLocalConfig(handLocalConfig),
		_localPlayerService(localPlayerService),
		_resourcesService(resourcesService),
		_localConfigHolder(localConfigHolder)
	{
	}

	virtual IGameplaySystem* Create(uintptr_t typeId) override;

private:
	GridLayout* _gridLayout;
	CityGridService* _cityGrid;
	Pathfinding::AStar* _aStar;
	flecs::world* _world;
	UWorld* _viewWorld;
	UHUDWidget* _hudWidget;
	UGameplayOverlayWidget* _entityOverlayWidget;
	UGameplayAssetData* _gameplayAssetData;
	AHand* _playerHand;
	UHandLocalConfig* _handLocalConfig;
	LocalPlayerService* _localPlayerService;
	ResourcesService* _resourcesService;
	ULocalConfigHolder* _localConfigHolder;
};
