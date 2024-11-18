#include "TurnSystem.h"

#include "FEndTurnRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/FDrawCardRequest.hpp"

void TurnSystem::Initialize()
{
	
	_world->system<const FEndTurnRequest>("TurnSystem")
		.each([this](flecs::entity entity, const FEndTurnRequest& request)
		{
			_world->entity().add<FDrawCardRequest>();
			entity.destruct();
		});
}
