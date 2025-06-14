#include "ApplyExplodingCardSystem.h"

#include "Cardopoly/ECS/Core/Cards/Components/ApplyCardRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/ExplodingCardComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Services/CitizenGridService.h"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/Grid/RadiusIterator.hpp"

void ApplyExplodingCardSystem::Initialize()
{
	_world->system<ApplyCardRequest, ExplodingCardComponent, PlayerIndexComponent>("ApplyExplodingCardSystem")
		.immediate()
		.each([this](flecs::entity entity, ApplyCardRequest& request, ExplodingCardComponent& explodingCard, PlayerIndexComponent& playerIndexComponent)
		{
			FIntVector position = request.CellPosition;

			for (const FIntVector& cell : GetCellsInRadius(position, explodingCard.Radius))
			{
				auto entities = _citizenGridService->GetEntitiesAtPosition(cell);
				if (entities == nullptr || entities->empty())
				{
					continue;
				}
				for (const flecs::entity& targetEntity : *entities)
				{
					if (targetEntity.is_alive())
					{
						targetEntity.destruct();
						_citizenGridService->RemoveEntityFromPosition(cell, targetEntity);
					}
				}
				/*if (targetEntity.is_alive())
				{
					targetEntity.destruct();
					if (targetEntity.has<PlayerIndexComponent>())
					{
						const PlayerIndexComponent* playerIndex = targetEntity.get<PlayerIndexComponent>();
						if (playerIndex->Value != playerIndexComponent.Value)
						{
							targetEntity.destruct();
						}
					}
					else
					{
						targetEntity.destruct();
					}
				}*/
			}
		});	
}
