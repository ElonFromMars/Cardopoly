#pragma once

#include "GenerationStep.h"

class LSystemConstructionsGenerationStep : public GenerationStep
{
public:
	LSystemConstructionsGenerationStep(CityGenerationData& cityGenerationData)
		: GenerationStep(cityGenerationData)
	{ }
	
	virtual void SubStep() override;
};
