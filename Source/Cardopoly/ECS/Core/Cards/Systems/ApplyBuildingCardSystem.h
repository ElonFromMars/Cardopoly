#pragma once

#include "flecs.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class ApplyBuildingCardSystem : public IGameplaySystem
{
public:
	ApplyBuildingCardSystem(
		flecs::world* flecsWorld,
		BuildingService* buildingService
	)
		: IGameplaySystem(flecsWorld),
		_buildingService(buildingService)
	{
	}

	virtual void Initialize() override;
	
private:
	BuildingService* _buildingService;
};
