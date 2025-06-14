#pragma once

#include "flecs.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/Cards/CardConfigService.h"
#include "Cardopoly/ECS/Core/Cards/Factories/CardEntityFactory.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class HandSystem : public IGameplaySystem
{
public:
	HandSystem(
		flecs::world* flecsWorld,
		ULocalConfigHolder* localConfigHolder,
		CardConfigService* cardConfigService,
		CardEntityFactory* cardEntityFactorySystem
	)
		: IGameplaySystem(flecsWorld),
		_localConfigHolder(localConfigHolder),
		_cardConfigService(cardConfigService),
		_cardEntityFactory(cardEntityFactorySystem)
	{}

	virtual void Initialize() override;

private:
	void DrawCard(flecs::entity playerEntity);
	
	ULocalConfigHolder* _localConfigHolder;
	CardConfigService* _cardConfigService;
	CardEntityFactory* _cardEntityFactory;
};
