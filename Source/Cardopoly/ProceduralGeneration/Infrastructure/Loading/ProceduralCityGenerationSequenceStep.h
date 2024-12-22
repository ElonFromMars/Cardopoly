#pragma once

#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"
#include "Cardopoly/ProceduralGeneration/City/CityGenerationData.h"
#include "Cardopoly/ProceduralGeneration/City/CityGeneratorService.h"

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
		flecs::world* world = ServiceContainer.Get<flecs::world>();
		UCityGeneratorConfig* CityGeneratorConfig = ServiceContainer.Get<UCityGeneratorConfig>();
		BuildingService* BuildingsController = ServiceContainer.Get<BuildingService>();
		
		CityGenerationData* cityGenerationData = new CityGenerationData();

		CityGeneratorService cityGenerator = CityGeneratorService(CityGeneratorConfig, world, BuildingsController);

		cityGenerator.Generate();
		
		ServiceContainer
			.Set<CityGenerationData>(cityGenerationData)
			.BindLifetimeToContainer();
		
		return SD::MakeReadyFuture();
	}
};
