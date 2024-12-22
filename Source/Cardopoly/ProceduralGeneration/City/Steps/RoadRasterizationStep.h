#pragma once

#include "GenerationStep.h"
#include "Cardopoly/ProceduralGeneration/City/CityGenerationData.h"

class GenerationStep;

class RoadRasterizationStep : public GenerationStep
{
public:
	RoadRasterizationStep(CityGenerationData& cityGenerationData)
		: GenerationStep(cityGenerationData)
	{ }
};
