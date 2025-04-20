#include "HandUISystem.h"

#include "Cardopoly/Cards/Hand/Hand.h"
#include "Cardopoly/ECS/Core/Cards/Components/CardAddedEvent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"

void HandUISystem::Initialize()
{
	_world->system<const CardAddedEvent>("HandUISystem")
		.each([this](flecs::entity entity, const CardAddedEvent& request)
		{
			if (!request.CardEntity.has<CardComponent>()
				|| request.PlayerIndex != _localPlayerService->GetLocalPlayerIndex())
			{
				return;
			}
			
			_hand->DrawCard(request.CardEntity.get<CardComponent>()->Id);
		});
}
