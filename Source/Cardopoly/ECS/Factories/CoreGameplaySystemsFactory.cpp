#include "CoreGameplaySystemsFactory.h"

#include "Cardopoly/ECS/Core/Economy/EconomicsSystem.h"
#include "Cardopoly/ECS/Core/GameplayFlow/TurnSystem.h"
#include "Cardopoly/ECS/Core/Player/Common/PlayerInitializeSystem.h"
#include "Cardopoly/ECS/Core/UI/Cards/HandUISystem.h"
#include "Cardopoly/ECS/Core/UI/HUD/HUDViewSystem.h"
#include "Cardopoly/ECS/Core/UI/Overlay/IncomeOverlaySystem.h"
#include "Cardopoly/ECS/Core/UI/Overlay/OverlayPositionSystem.h"
#include "Cardopoly/ECS/Core/View/CreateViewSystem.h"
#include "Cardopoly/ECS/Core/View/InitializeGridPositionSystem.h"

IGameplaySystem* CoreGameplaySystemsFactory::Create(uintptr_t typeId)
{
	using SystemConstructor = std::function<IGameplaySystem*()>;

	std::unordered_map<uintptr_t, SystemConstructor> systemConstructors = {
	{ unique_id<CitizensInitializeSystem>::get_ID(),
		[this]() { return new CitizensInitializeSystem(_world, _gridLayout); } },
	{ unique_id<DrawDebugViewSystem>::get_ID(),
		[this]() { return new DrawDebugViewSystem(_world, _viewWorld); } },
	{ unique_id<CreateViewSystem>::get_ID(), 
		[this]() { return new CreateViewSystem(_world, _gameplayAssetData, _viewWorld); } },
	{ unique_id<InitializeGridPositionSystem>::get_ID(), 
		[this]() { return new InitializeGridPositionSystem(_world, _gridLayout, _viewWorld); } },
	{ unique_id<PathfindingSystem>::get_ID(), 
		[this]() { return new PathfindingSystem(_world, _gridLayout, _cityGrid, _aStar); } },
	{ unique_id<MovementSystem>::get_ID(), 
		[this]() { return new MovementSystem(_world, _gridLayout); } },
	{ unique_id<HUDViewSystem>::get_ID(), 
		[this]() { return new HUDViewSystem(_world, _hudWidget); } },
	{ unique_id<PlayerInitializeSystem>::get_ID(), 
		[this]() { return new PlayerInitializeSystem(_world); } },
	{ unique_id<EconomySystem>::get_ID(), 
		[this]() { return new EconomySystem(_world); } },
	{ unique_id<TurnSystem>::get_ID(), 
		[this]() { return new TurnSystem(_world); } },
	{ unique_id<HandUISystem>::get_ID(), 
		[this]() { return new HandUISystem(_world, _playerHand, _handLocalConfig); } },
	{ unique_id<OverlayPositionSystem>::get_ID(),
		[this]() { return new OverlayPositionSystem(_world, _entityOverlayWidget); } },
	{ unique_id<IncomeOverlaySystem>::get_ID(),
		[this]() { return new IncomeOverlaySystem(_world, _gameplayAssetData, _entityOverlayWidget); } }
	};

	auto it = systemConstructors.find(typeId);
	if (it != systemConstructors.end()) {
		return it->second();
	}
	
	return nullptr;
}
