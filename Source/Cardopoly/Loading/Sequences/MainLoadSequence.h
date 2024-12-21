#pragma once

#include <memory>
#include "Cardopoly/Infrastructure/Loading/LoadSequence.h"
#include "Cardopoly/Loading/Steps/TestStep.h"

class StartGameplayEscStep;
class ProceduralCityGenerationSequenceStep;

class MainLoadSequence
{
public:
	static std::shared_ptr<LoadSequence> CreateMainLoadingQueue(IServiceContainer& serviceContainer)
	{
		std::shared_ptr<LoadSequence> sequence = std::make_shared<LoadSequence>(serviceContainer);

		sequence->
			Sequential<ProceduralCityGenerationSequenceStep>().
			Sequential<StartGameplayEscStep>().
			End();

		return sequence;
	}
};
