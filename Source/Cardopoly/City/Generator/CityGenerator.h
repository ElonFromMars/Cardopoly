#pragma once

class UCityGeneratorConfig;

class CityGenerator
{

private:
	UCityGeneratorConfig* cityGeneratorConfig;
	UWorld* world;
	
public:
	CityGenerator(UCityGeneratorConfig* cityGeneratorConfig, UWorld* world)
		: cityGeneratorConfig(cityGeneratorConfig),
		  world(world)
	{
	}

	void Generate();
};
