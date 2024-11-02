#pragma once
#include "Cardopoly/ECS/Infrastructure/Features/GameplayFeature.h"

class MainGameplayFeature : GameplayFeature
{
public:
	virtual void AddSystems() override
	{
		AddSystem<class MovementSystem>();
		AddSystem<class PathfindingSystem>();
	}
};
