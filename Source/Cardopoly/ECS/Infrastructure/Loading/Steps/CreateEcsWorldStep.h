#pragma once

#include "flecs.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class IServiceContainer;

class CreateEcsWorldStep : LoadSequenceStep
{
public:
	CreateEcsWorldStep(IServiceContainer* serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual UE5Coro::TCoroutine<> Execute() override
	{
		flecs::world* world = new flecs::world();

		ServiceContainer->Set<flecs::world>(world)
		;
		//.BindLifetimeToContainer();
		
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
};