#pragma once

#include "flecs.h"

class EntityFactory
{
	
public:
	EntityFactory(flecs::world* world) : _world(world)
	{
		
	}
	
protected:
	flecs::world* _world;
};
