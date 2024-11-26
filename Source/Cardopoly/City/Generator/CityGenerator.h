#pragma once

class BuildingService;
class UCityGeneratorConfig;

class CityGenerator
{

private:
	UCityGeneratorConfig* CityGeneratorConfig;
	UWorld* World;
	BuildingService* BuildingsController;
	
public:
	CityGenerator(
		UCityGeneratorConfig* cityGeneratorConfig,
		UWorld* world,
		BuildingService* buildingsController)
		: CityGeneratorConfig(cityGeneratorConfig),
		  World(world),
		  BuildingsController(buildingsController)
	{
	}

	void Generate();
};
