#include "PlayerInitializeSystem.h"

#include "Cardopoly/ECS/Core/Economy/FMoneyComponent.hpp"

void PlayerInitializeSystem::Initialize()
{
	_world->entity()
		.set<FMoneyComponent>({});
}
