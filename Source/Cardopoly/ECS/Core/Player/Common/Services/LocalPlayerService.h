#pragma once

#include "flecs.h"

class LocalPlayerService
{
public:
	void AddPlayerEntity(flecs::entity entity);

	flecs::entity GetPlayerEntity(int playerIndex);
	
private:
	std::unordered_map<int, flecs::entity> _playerEntityByIndex;
};
