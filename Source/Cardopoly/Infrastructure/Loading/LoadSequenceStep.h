#pragma once

#include <FutureExtensions.h>

#include "Cardopoly/Infrastructure/DI/IServiceContainer.h"

class LoadSequenceStep
{
public:
	LoadSequenceStep(IServiceContainer& serviceContainer)
		: ServiceContainer(serviceContainer)
	{ }
	
	virtual SD::TExpectedFuture<void> Execute() = 0;

	virtual ~LoadSequenceStep() = default;
	LoadSequenceStep() = default;

protected:
	IServiceContainer& ServiceContainer;
};
