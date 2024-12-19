#pragma once

#include "flecs.h"

class BuildingService;
class UCityGeneratorConfig;

class CityGeneratorService
{
public:
	CityGeneratorService(
		UCityGeneratorConfig* cityGeneratorConfig,
		flecs::world* world,
		BuildingService* buildingsController
	)
	:
		_cityGeneratorConfig(cityGeneratorConfig),
		_world(world),
		_buildingsController(buildingsController)
	{}

	void Generate();

private:
	UCityGeneratorConfig* _cityGeneratorConfig;
	flecs::world* _world;
	BuildingService* _buildingsController;
};
