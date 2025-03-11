#include "PlayerInitializeSystem.h"

#include "Cardopoly/ECS/Core/Economy/FMoneyComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerTag.hpp"


void PlayerInitializeSystem::Initialize()
{
	auto localPlayerEntity = CreateLocalPlayer(0);
	_localPlayerService->AddPlayerEntity(localPlayerEntity);
	
	auto aiOpponentEntity = CreateAIOpponentPlayer(1);
	_localPlayerService->AddPlayerEntity(aiOpponentEntity);
}

flecs::entity PlayerInitializeSystem::CreateLocalPlayer(int32 playerIndex) const
{
	return _world->entity()
	      .set<FMoneyComponent>({})
	      .set<PlayerTag>({})
	      .set<PlayerIndexComponent>({playerIndex})
	;
}

flecs::entity PlayerInitializeSystem::CreateAIOpponentPlayer(int32 playerIndex) const
{
	return _world->entity()
	      .set<FMoneyComponent>({})
	      .set<PlayerTag>({})
	      .set<PlayerIndexComponent>({playerIndex})
	;
}
