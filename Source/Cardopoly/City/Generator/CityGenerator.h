#pragma once

class ABuildingsController;
class UCityGeneratorConfig;

class CityGenerator
{

private:
	UCityGeneratorConfig* CityGeneratorConfig;
	UWorld* World;
	ABuildingsController* BuildingsController;
	
public:
	CityGenerator(
		UCityGeneratorConfig* cityGeneratorConfig,
		UWorld* world,
		ABuildingsController* buildingsController)
		: CityGeneratorConfig(cityGeneratorConfig),
		  World(world),
		  BuildingsController(buildingsController)
	{
	}

	void Generate();
};
