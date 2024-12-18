#pragma once

#include "GenerationStep.h"

class LSystemConstructionsGenerationStep : public GenerationStep
{
public:
	LSystemConstructionsGenerationStep(CityGenerationData& cityGenerationData)
		: GenerationStep(cityGenerationData)
	{ }
	
	void Initialize();

	void SubStep();

	bool IsFinished() const;
};
