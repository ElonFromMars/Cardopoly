#pragma once
#include "Cardopoly/ProceduralGeneration/City/CityGenerationData.h"

class GenerationStep
{
public:
	GenerationStep(CityGenerationData& cityGenerationData)
		: _cityGenerationData(cityGenerationData)
	{
		
	}
	
protected:
	CityGenerationData& _cityGenerationData;
};
