#include "ResourcesService.h"

#include "Cardopoly/ECS/Core/Player/Resources/ActionPoints/Components/ActionPointsChangedEvent.hpp"
#include "Cardopoly/ECS/Core/Player/Resources/ActionPoints/Components/ActionPointsComponent.hpp"

ResourcesService::ResourcesService(flecs::world* world) : _world(world) {}

bool ResourcesService::TryChangeActionPoints(flecs::entity player, int32 points)
{
	auto actionPoints = player.get_ref<ActionPointsComponent>();
	if (actionPoints && actionPoints->CurrentPoints + points <= actionPoints->MaxPoints)
	{
		actionPoints->CurrentPoints += points;
		player.set<ActionPointsChangedEvent>({ points });
		
		return true;
	}
	
	return false;
}

bool ResourcesService::HasEnoughActionPoints(flecs::entity player, int points)
{
	auto actionPoints = player.get<ActionPointsComponent>();
	return actionPoints && actionPoints->CurrentPoints >= points;
}

