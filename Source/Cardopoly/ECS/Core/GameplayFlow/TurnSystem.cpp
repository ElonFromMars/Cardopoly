#include "TurnSystem.h"

#include "FEndTurnRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/FDrawCardRequest.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerTag.hpp"

void TurnSystem::Initialize()
{
	_world->system<const FEndTurnRequest>("TurnSystem")
		.each([this](flecs::entity entity, const FEndTurnRequest& request)
		{
			_world->each<PlayerTag>([this](flecs::entity entity, const PlayerTag playerTag) {
				entity.add<FDrawCardRequest>();
			});
			
			entity.destruct();
		});
}
