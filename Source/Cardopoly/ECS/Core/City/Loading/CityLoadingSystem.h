#pragma once

#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class CityData;
class GridLayout;

class CityLoadingSystem : public IGameplaySystem
{
public:
	CityLoadingSystem(
		flecs::world* world,
		CityData* cityData,
		BuildingService* buildingService
	)
	: IGameplaySystem(world),
		_cityData(cityData),
		_buildingService(buildingService)
	{}
	
	virtual void Initialize() override;

private:
	CityData* _cityData;
	BuildingService* _buildingService;
};
