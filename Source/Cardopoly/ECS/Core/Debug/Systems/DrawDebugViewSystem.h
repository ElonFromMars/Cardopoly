#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class DrawDebugViewSystem : IGameplaySystem
{
UWorld* _UWorld;
	
	DrawDebugViewSystem(flecs::world* flecsWorld, UWorld* world) : IGameplaySystem(flecsWorld),
		_UWorld(world)
	{
		
	}

public:
	virtual void Initialize() override;
};
