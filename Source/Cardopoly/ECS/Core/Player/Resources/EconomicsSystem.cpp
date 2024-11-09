#include "EconomicsSystem.h"

#include "Cardopoly/ECS/Core/Player/Resources/FMoneyComponent.hpp"

void EconomicsSystem::Initialize()
{
	_world->system<FMoneyComponent>("EconomicsSystem")
		.interval(1)
		.each([this](FMoneyComponent& money) {
			money.Value += 1;
		});
}
