#pragma once

#include "flecs.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class IServiceContainer;

class CreateEcsWorldStep : LoadSequenceStep
{
public:
	CreateEcsWorldStep(IServiceContainer& serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual SD::TExpectedFuture<void> Execute() override
	{
		flecs::world* world = new flecs::world();

		ServiceContainer
			.Set<flecs::world>(world)
			.BindLifetimeToContainer();
		
		return SD::MakeReadyFuture();
	}
};