#pragma once

#include "AIOpponentStateComponent.hpp"
#include "flecs.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class AIOpponentPlayerFlowSystem : public IGameplaySystem
{
public:
	AIOpponentPlayerFlowSystem(
		flecs::world* flecsWorld
	)
		: IGameplaySystem(flecsWorld)
	{
	}

	virtual void Initialize() override;
	void ApplyTurnCards(flecs::entity entity);

	void ChangeState(flecs::entity entity, AIOpponentState newState);
};