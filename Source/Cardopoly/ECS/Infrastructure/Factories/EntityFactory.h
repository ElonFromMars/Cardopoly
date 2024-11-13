#pragma once
#include "flecs.h"

class EntityFactory
{
	
public:
	EntityFactory(flecs::world* world) : world(world)
	{
		
	}
	
protected:
	flecs::world* world;
};
