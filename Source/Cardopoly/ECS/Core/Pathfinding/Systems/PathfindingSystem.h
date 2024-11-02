#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class PathfindingSystem : IGameplaySystem
{
public:
	virtual void Initialize() override;
};
