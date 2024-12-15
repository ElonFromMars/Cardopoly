#pragma once

#include <memory>
#include "Cardopoly/Infrastructure/Loading/LoadSequence.h"
#include "Cardopoly/Loading/Steps/TestStep.h"

class MainLoadSequence
{
public:
	static std::shared_ptr<LoadSequence> CreateMainLoadingQueue(IServiceContainer& serviceContainer)
	{
		std::shared_ptr<LoadSequence> sequence = std::make_shared<LoadSequence>(serviceContainer);

		sequence->
			Sequential<TestStep>().
			Sequential<TestStep>().
			End();

		return sequence;
	}
};
