#include "CityGeneratorService.h"
#include "CityGenerationData.h"
#include "Steps/LSystemConstructionsGenerationStep.h"
#include "Steps/RoadRasterizationStep.h"

CityGenerationData* CityGeneratorService::Generate()
{
	CityGenerationData* cityGenerationData = new CityGenerationData();

	InitSteps(cityGenerationData);
	ApplySteps();
	
	return cityGenerationData;
}

void CityGeneratorService::InitSteps(CityGenerationData* cityGenerationData)
{
	_generationSteps.clear();
	_generationSteps.push_back(new LSystemConstructionsGenerationStep(*cityGenerationData));
	_generationSteps.push_back(new RoadRasterizationStep(*cityGenerationData));
}

void CityGeneratorService::ApplySteps()
{
	CityGenerationData* cityGenerationData = Generate();
	
	for (auto stepIt : _generationSteps)
	{
		while (!stepIt->IsFinished())
		{
			stepIt->SubStep();
		}
	}
}
