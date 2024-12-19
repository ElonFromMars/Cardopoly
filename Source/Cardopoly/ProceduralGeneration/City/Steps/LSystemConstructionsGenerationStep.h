#pragma once

#include "GenerationStep.h"

class LSystemConstructionsGenerationStep : public GenerationStep
{
public:
	LSystemConstructionsGenerationStep(CityGenerationData& cityGenerationData)
		: GenerationStep(cityGenerationData)
	{ }
	
	virtual void Initialize() override;

	virtual void SubStep() override;

	virtual bool IsFinished() const override;
};
