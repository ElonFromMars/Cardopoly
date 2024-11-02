#pragma once
#include "flecs.h"

class IGameplaySystem
{
protected:
	flecs::world* _world;

public:
	IGameplaySystem(flecs::world* flecsWorld) : _world(flecsWorld)
	{
		
	}

	virtual void Initialize()
	{
		
	}
	
	virtual void Update()
	{
		
	}

	virtual ~IGameplaySystem() = default;
};
