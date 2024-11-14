#include "EconomicsSystem.h"

#include "FIncomeComponent.hpp"
#include "FMoneyComponent.hpp"

void EconomySystem::Initialize()
{
	flecs::query<FMoneyComponent> q = 
	   _world->query_builder<FMoneyComponent>()
		   .cached()
		   .build();
	
	_world->system<FIncomeComponent>("EconomicsSystem")
		.interval(1)
		.each([this, q](FIncomeComponent& income)
		{
			q.each([income](FMoneyComponent& money)
			{
				money.Value += income.Value;
			});
		});
}
