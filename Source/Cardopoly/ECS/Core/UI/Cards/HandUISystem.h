#pragma once

#include "Cardopoly/ECS/Core/Player/Common/Services/LocalPlayerService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UHandLocalConfig;
class AHand;

class HandUISystem : public IGameplaySystem
{
public:
	HandUISystem(
		flecs::world* world,
		AHand* playerHand,
		UHandLocalConfig* playerHandLocalConfig,
		LocalPlayerService* localPlayerService
		)
		: IGameplaySystem(world),
		_hand(playerHand),
		_handLocalConfig(playerHandLocalConfig),
		_localPlayerService(localPlayerService)
	{
		
	}
	
	virtual void Initialize() override;

private:
	AHand* _hand;
	UHandLocalConfig* _handLocalConfig;
	LocalPlayerService* _localPlayerService;
};

