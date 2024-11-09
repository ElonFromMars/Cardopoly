#include "CoreGameplaySystemsFactory.h"

#include "Cardopoly/ECS/Core/Player/Core/PlayerInitializeSystem.h"
#include "Cardopoly/ECS/Core/Player/Resources/EconomicsSystem.h"
#include "Cardopoly/ECS/Core/UI/HUD/HUDViewSystem.h"

IGameplaySystem* CoreGameplaySystemsFactory::Create(uintptr_t typeId)
{

	if (typeId == unique_id<CitizensInitializeSystem>::get_ID()) {
		return new CitizensInitializeSystem(_world, _gridSubsystem);
	} else if (typeId == unique_id<DrawDebugViewSystem>::get_ID()) {
		return new DrawDebugViewSystem(_world, _viewWorld);
	} else if (typeId == unique_id<PathfindingSystem>::get_ID()) {
		return new PathfindingSystem(_world, _gridSubsystem, _cityGrid, _aStar);
	} else if (typeId == unique_id<MovementSystem>::get_ID()) {
		return new MovementSystem(_world, _gridSubsystem);
	} else if (typeId == unique_id<HUDViewSystem>::get_ID()) {
		return new HUDViewSystem(_world, _hudWidget);
	} else if (typeId == unique_id<PlayerInitializeSystem>::get_ID()) {
		return new PlayerInitializeSystem(_world);
	} else if (typeId == unique_id<EconomicsSystem>::get_ID()) {
		return new EconomicsSystem(_world);
	}
	
	return nullptr;
}
