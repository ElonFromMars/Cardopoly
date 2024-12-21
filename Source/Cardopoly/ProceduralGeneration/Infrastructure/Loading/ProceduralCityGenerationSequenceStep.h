#pragma once

#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"
#include "Cardopoly/ProceduralGeneration/City/CityGenerationData.h"

class IServiceContainer;

class ProceduralCityGenerationSequenceStep : LoadSequenceStep
{
public:
	ProceduralCityGenerationSequenceStep(IServiceContainer& serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual SD::TExpectedFuture<void> Execute() override
	{
		CityGenerationData* cityGenerationData = new CityGenerationData();
		
		ServiceContainer
			.Set<CityGenerationData>(cityGenerationData)
			.BindLifetimeToContainer();
		
		return SD::MakeReadyFuture();
	}
};
