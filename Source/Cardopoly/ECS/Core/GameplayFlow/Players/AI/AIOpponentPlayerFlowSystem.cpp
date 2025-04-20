#include "AIOpponentPlayerFlowSystem.h"

#include "AIOpponentState.hpp"
#include "AIOpponentStateComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardsRelation.hpp"

void AIOpponentPlayerFlowSystem::Initialize()
{
	_world->system<AIOpponentStateComponent>("AIOpponentPlayerFlowSystem")
		.each([this](flecs::entity entity, AIOpponentStateComponent& stateComponent)
		{
			switch (stateComponent.State)
			{
				case AIOpponentState::WaitingForTurn:
					if (entity.has<CardsRelation>())
					{
						ChangeState(stateComponent, AIOpponentState::ApplyingTurnCards);	
					}
					break;
				case AIOpponentState::ApplyingTurnCards:
					
					break;
			}
		});
}

void AIOpponentPlayerFlowSystem::ChangeState(AIOpponentStateComponent& stateComponent, AIOpponentState newState)
{
	stateComponent.State = newState;
}
