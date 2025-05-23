﻿#pragma once
#include "Cardopoly/ProceduralGeneration/City/CityGenerationData.h"

class GenerationStep
{
public:
	GenerationStep(CityGenerationData& cityGenerationData)
		: _cityGenerationData(cityGenerationData)
	{
		
	}
	
	virtual void Initialize();

	virtual void SubStep();

	virtual bool IsFinished() const;
	
	virtual ~GenerationStep() = default;

protected:
	CityGenerationData& _cityGenerationData;
	bool _isFinished = true;
};
