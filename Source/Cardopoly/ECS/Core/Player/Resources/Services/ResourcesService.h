#pragma once

#include "flecs.h"

class ResourcesService
{
public:
	ResourcesService(flecs::world* world);

	bool TryChangeActionPoints(flecs::entity player, int points);

	bool HasEnoughActionPoints(flecs::entity player, int points);

private:
	flecs::world* _world;
};
