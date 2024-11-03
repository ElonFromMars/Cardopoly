#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class DrawDebugViewSystem : public IGameplaySystem
{
public:
	DrawDebugViewSystem(flecs::world* flecsWorld, UWorld* viewWorld)
		: IGameplaySystem(flecsWorld), _viewWorld(viewWorld)
	{
		
	}
	
	virtual void Initialize() override;

private:
	UWorld* _viewWorld;
};
