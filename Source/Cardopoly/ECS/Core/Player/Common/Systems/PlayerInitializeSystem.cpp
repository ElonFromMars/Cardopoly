#include "PlayerInitializeSystem.h"

#include "Cardopoly/ECS/Core/Economy/FMoneyComponent.hpp"
#include "Cardopoly/ECS/Core/GameplayFlow/Players/AI/AIOpponentStateComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerTag.hpp"
#include "Cardopoly/ECS/Core/Player/Resources/ActionPoints/Components/ActionPointsComponent.hpp"


void PlayerInitializeSystem::Initialize()
{
	auto localPlayerEntity = CreateLocalPlayer(0);
	_localPlayerService->AddPlayerEntity(localPlayerEntity);
	
	auto aiOpponentEntity = CreateAIOpponentPlayer(1);
	_localPlayerService->AddPlayerEntity(aiOpponentEntity);
}

flecs::entity PlayerInitializeSystem::CreateLocalPlayer(int32 playerIndex) const
{
	flecs::entity entity = _world->entity()
        .add<FMoneyComponent>()
		.add<PlayerTag>()
	    .set<PlayerIndexComponent>({playerIndex})
	    .set<ActionPointsComponent>({})
	;

	return entity;
}

flecs::entity PlayerInitializeSystem::CreateAIOpponentPlayer(int32 playerIndex) const
{
	flecs::entity entity = _world->entity()
		.add<FMoneyComponent>()
	    .add<PlayerTag>()
	    .set<PlayerIndexComponent>({playerIndex})
	    .set<ActionPointsComponent>({})
		.set<AIOpponentStateComponent>({AIOpponentState::WaitingForTurn})
	;
	
	return entity;
}
