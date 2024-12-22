#pragma once

#include <vector>
#include "CityGenerationData.h"
#include "flecs.h"
#include "Steps/GenerationStep.h"

class BuildingService;
class UCityGeneratorConfig;

class CityGeneratorService
{
public:
	CityGeneratorService(
		UCityGeneratorConfig* cityGeneratorConfig,
		BuildingService* buildingsController
	)
	:
		_cityGeneratorConfig(cityGeneratorConfig),
		_buildingsController(buildingsController)
	{}

	CityGenerationData* Generate();

	void InitSteps(CityGenerationData* cityGenerationData);
	void ApplySteps();

	~CityGeneratorService()
	{
		for (auto step : _generationSteps)
		{
			delete step;
		}
	}

private:
	UCityGeneratorConfig* _cityGeneratorConfig;
	BuildingService* _buildingsController;
	std::vector<GenerationStep*> _generationSteps;
};
