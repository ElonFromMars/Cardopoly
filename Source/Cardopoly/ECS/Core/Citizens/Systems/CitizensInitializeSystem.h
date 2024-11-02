#pragma once
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class CitizensInitializeSystem : IGameplaySystem
{
public:
	CitizensInitializeSystem()
	{
		
	}
	
	virtual void Initialize() override;
};
