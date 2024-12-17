#pragma once

#include "flecs.h"

class CityData
{
	CityData(flecs::world* world)
		: _world(world)
	{ }

protected:
	flecs::world* _world;
};
