#include "EconomicsSystem.h"

#include "FIncomeComponent.hpp"
#include "FIncomeEvent.hpp"
#include "FMoneyComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"

void EconomySystem::Initialize()
{
	flecs::query<FIncomeComponent, PlayerIndexComponent> incomeQuery = 
	   _world->query_builder<FIncomeComponent, PlayerIndexComponent>()
		   .cached()
		   .build();
	
	_world->system<FMoneyComponent, PlayerIndexComponent>("EconomicsSystem")
		.interval(1)
		.immediate()
		.each([this, incomeQuery](flecs::entity entity, FMoneyComponent& money, PlayerIndexComponent& playerIndex)
		{
			int playerIndexValue = playerIndex.Value;
			int totalIncomeChange{};
			incomeQuery.each([playerIndexValue, &totalIncomeChange](flecs::entity entity,
				FIncomeComponent& income, PlayerIndexComponent& incomePlayerIndex)
			{
				if (incomePlayerIndex.Value == playerIndexValue)
				{
					totalIncomeChange += income.Value;
					entity.set(FIncomeEvent{income.Value});
				}
			});
			money.Value += totalIncomeChange;
		});
}
