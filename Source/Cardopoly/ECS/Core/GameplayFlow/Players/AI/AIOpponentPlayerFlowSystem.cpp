#include "AIOpponentPlayerFlowSystem.h"

#include "AIOpponentState.hpp"
#include "AIOpponentStateComponent.hpp"
#include "TurnTimer.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/ApplyCardRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardInHandRelation.hpp"

void AIOpponentPlayerFlowSystem::Initialize()
{
	_world->system<AIOpponentStateComponent>("AIOpponentPlayerFlowSystem")
		.write<TurnTimer>()
		.immediate()
		.each([this](flecs::entity entity, AIOpponentStateComponent& stateComponent)
		{
			switch (stateComponent.State)
			{
				case AIOpponentState::WaitingForTurn:
					{
						if (entity.has<TurnTimer>())
						{
							float timeLeft = entity.get<TurnTimer>()->TimeLeft;
							if (timeLeft <= 0.0f)
							{
								ChangeState(entity, AIOpponentState::ApplyingTurnCards);
								entity.remove<TurnTimer>();
							}
							else
							{
								entity.set<TurnTimer>({timeLeft-= _world->delta_time()});
							}
						}
						else
						{
							auto cardsCount = entity.world().query_builder()
								.term_at(0)
								.first<CardInHandRelation>()
								.second(entity)
								.build()
								.count();

							if (cardsCount > 0)
							{
								ChangeState(entity, AIOpponentState::ApplyingTurnCards);	
							}
						}
					}
					break;
				case AIOpponentState::ApplyingTurnCards:
					ApplyTurnCards(entity);
					break;
			}
		});
}

void AIOpponentPlayerFlowSystem::ApplyTurnCards(flecs::entity handEntity)
{
	auto firstChild = handEntity.world().query_builder()
		.term_at(0)
			.first<CardInHandRelation>()
			.second(handEntity)
		.build().first();

	if (firstChild.is_alive())
	{
		int32 X = FMath::RandRange(-20, 20);
		int32 Y = FMath::RandRange(-20, 20);
		FIntVector cellPosition = {X, Y, 0};
		firstChild.set<ApplyCardRequest>({
			cellPosition
		});

		handEntity.set<TurnTimer>({10.0f});
		ChangeState(handEntity, AIOpponentState::WaitingForTurn);
	}
}

void AIOpponentPlayerFlowSystem::ChangeState(flecs::entity entity, AIOpponentState newState)
{
	entity.set<AIOpponentStateComponent>({newState});
}
