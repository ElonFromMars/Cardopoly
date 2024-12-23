#pragma once

#include <memory>

#include "Cardopoly/ECS/Infrastructure/Loading/Steps/CreateEcsWorldStep.h"
#include "Cardopoly/ECS/Infrastructure/Loading/Steps/CreateHandStep.h"
#include "Cardopoly/ECS/Infrastructure/Loading/Steps/CreateServicesStep.h"
#include "Cardopoly/ECS/Infrastructure/Loading/Steps/StartGameplayEscStep.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequence.h"
#include "Cardopoly/ProceduralGeneration/Infrastructure/Loading/ProceduralCityGenerationSequenceStep.h"


class MainLoadSequence
{
public:
	static std::shared_ptr<LoadSequence> CreateMainLoadingQueue(IServiceContainer* serviceContainer)
	{
		std::shared_ptr<LoadSequence> sequence = std::make_shared<LoadSequence>(serviceContainer);

		sequence->
			Sequential<CreateEcsWorldStep>().
			Sequential<CreateServicesStep>().
			Sequential<ProceduralCityGenerationSequenceStep>().
			Sequential<CreateHandStep>().
			Sequential<StartGameplayEscStep>().
			End();

		return sequence;
	}
};
