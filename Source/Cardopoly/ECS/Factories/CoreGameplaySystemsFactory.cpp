#include "CoreGameplaySystemsFactory.h"

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
	}
	
	return nullptr;
}
