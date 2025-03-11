#pragma once

#include "Cardopoly/Infrastructure/DI/IServiceContainer.h"
#include "UE5Coro.h"

class LoadSequenceStep
{
public:
	LoadSequenceStep(IServiceContainer* serviceContainer)
		: ServiceContainer(serviceContainer)
	{ }
	
	virtual UE5Coro::TCoroutine<> Execute() = 0;

	virtual ~LoadSequenceStep() = default;
	LoadSequenceStep() = default;

protected:
	IServiceContainer* ServiceContainer;
};
