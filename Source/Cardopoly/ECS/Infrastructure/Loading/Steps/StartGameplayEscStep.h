#pragma once

#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class IServiceContainer;

class StartGameplayEscStep : LoadSequenceStep
{
public:
	StartGameplayEscStep(IServiceContainer& serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual SD::TExpectedFuture<void> Execute() override
	{
		ServiceContainer.Set<LoadS>()
		
		return SD::MakeReadyFuture();
	}
};