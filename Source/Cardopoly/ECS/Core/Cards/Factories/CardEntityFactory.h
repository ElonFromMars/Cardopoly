#pragma once

#include "Cardopoly/Configs/Cards/CardType.h"
#include "Cardopoly/ECS/Infrastructure/Factories/EntityFactory.h"

class CardConfigService;

class CardEntityFactory : EntityFactory
{
public:
	CardEntityFactory(
		flecs::world* world,
		CardConfigService* cardConfigService
		)
		: EntityFactory(world),
		_cardConfigService(cardConfigService)
	{}

	flecs::entity Create(FName cardId) const;

private:
	void InitializeBuildingCard(flecs::entity cardEntity, FName cardId) const;
	void InitializeAbilityCard(flecs::entity cardEntity, FName cardId) const;

	CardConfigService* _cardConfigService;
};
