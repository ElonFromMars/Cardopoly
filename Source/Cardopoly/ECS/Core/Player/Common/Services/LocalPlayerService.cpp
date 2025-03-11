#include "LocalPlayerService.h"

#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"

void LocalPlayerService::AddPlayerEntity(flecs::entity entity)
{
	auto playerIndex = entity.get<PlayerIndexComponent>()->Value;

	_playerEntityByIndex[playerIndex];
}

flecs::entity LocalPlayerService::GetPlayerEntity(int playerIndex)
{
	return _playerEntityByIndex[playerIndex];
}
