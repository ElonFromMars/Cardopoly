#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UHandLocalConfig;
class AHand;

class HandUISystem : public IGameplaySystem
{
public:
	HandUISystem(
		flecs::world* world,
		AHand* playerHand,
		UHandLocalConfig* playerHandLocalConfig) : IGameplaySystem(world),
		_hand(playerHand),
		_handLocalConfig(playerHandLocalConfig)
	{
		
	}
	
	virtual void Initialize() override;

private:
	AHand* _hand;
	UHandLocalConfig* _handLocalConfig;
};

