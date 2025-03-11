#pragma once

#include "Cardopoly/ECS/Core/Player/Common/Services/LocalPlayerService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class PlayerInitializeSystem : public IGameplaySystem
{
public:
	PlayerInitializeSystem
	(
		flecs::world* flecsWorld,
		LocalPlayerService* localPlayerService
	) :
		IGameplaySystem(flecsWorld),
		_localPlayerService(localPlayerService)
	{}

	virtual void Initialize() override;

	flecs::entity CreateLocalPlayer(int32 playerIndex) const;
	flecs::entity CreateAIOpponentPlayer(int32 playerIndex) const;

private:
	LocalPlayerService* _localPlayerService;
};
