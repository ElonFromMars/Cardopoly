#pragma once

class BuildingService;
class UCityGeneratorConfig;

class CityGeneratorService
{

private:
	UCityGeneratorConfig* CityGeneratorConfig;
	UWorld* World;
	BuildingService* BuildingsController;
	
public:
	CityGeneratorService(
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
