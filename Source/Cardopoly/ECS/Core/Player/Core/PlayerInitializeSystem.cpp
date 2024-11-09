#include "PlayerInitializeSystem.h"

#include "Cardopoly/ECS/Core/Player/Resources/FMoneyComponent.hpp"

void PlayerInitializeSystem::Initialize()
{
	_world->entity()
		.set<FMoneyComponent>({});
}
