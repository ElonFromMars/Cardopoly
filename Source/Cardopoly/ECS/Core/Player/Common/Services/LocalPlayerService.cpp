#include "LocalPlayerService.h"

#include "Cardopoly/ECS/Core/Player/Common/Components/LocalPlayerTag.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"

void LocalPlayerService::AddPlayerEntity(flecs::entity entity)
{
	auto playerIndex = entity.get<PlayerIndexComponent>()->Value;

	if (entity.has<LocalPlayerTag>())
	{
		_localPlayerIndex = playerIndex;
	}
	
	_playerEntityByIndex[playerIndex];
}

flecs::entity LocalPlayerService::GetPlayerEntity(int32 playerIndex)
{
	return _playerEntityByIndex[playerIndex];
}

int32 LocalPlayerService::GetLocalPlayerIndex() const
{
	return _localPlayerIndex;
}
