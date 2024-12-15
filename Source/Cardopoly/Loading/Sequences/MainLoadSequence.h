#pragma once

#include <memory>
#include "Cardopoly/Infrastructure/Loading/LoadSequence.h"
#include "Cardopoly/Loading/Steps/TestStep.h"

class MainLoadSequence
{
public:
	static std::shared_ptr<LoadSequence> GetLoadingQueue()
	{
		std::shared_ptr<LoadSequence> sequence;

		sequence->
			Sequential<TestStep>().
			Sequential<TestStep>().
			End();

		return sequence;
	}
};
