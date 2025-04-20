#pragma once

#include "flecs.h"

class LocalPlayerService
{
public:
	void AddPlayerEntity(flecs::entity entity);

	flecs::entity GetPlayerEntity(int32 playerIndex);

	int32 GetLocalPlayerIndex() const;

private:
	std::unordered_map<int32, flecs::entity> _playerEntityByIndex;

	int32 _localPlayerIndex = 0;
};
