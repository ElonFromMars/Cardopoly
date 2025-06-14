#include "CardEntityFactory.h"

#include "Cardopoly/Configs/Cards/AbilityCardDataRaw.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Cardopoly/Configs/Cards/CardConfigService.h"
#include "Cardopoly/ECS/Core/Cards/Components/BuildingCardComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/ExplodingCardComponent.hpp"

flecs::entity CardEntityFactory::Create(FName cardId) const
{
	auto cardType = _cardConfigService->GetBaseCardData(cardId).Type;
	
	flecs::entity cardEntity = _world->entity()
		.set<CardComponent>({cardId, cardType});

	switch (cardType)
	{
		case ECardType::Building:
			InitializeBuildingCard(cardEntity, cardId);
			break;
		case ECardType::Ability:
			InitializeAbilityCard(cardEntity, cardId);
			break;
		
		default:
			checkNoEntry();
			break;
	}
	
	return cardEntity;
}

void CardEntityFactory::InitializeBuildingCard(flecs::entity cardEntity, FName cardId) const
{
	auto buildingCardData = _cardConfigService->GetCardData<FBuildingCardDataRaw>(cardId);
	cardEntity.set<BuildingCardComponent>({buildingCardData->BuildingId});
}

void CardEntityFactory::InitializeAbilityCard(flecs::entity cardEntity, FName cardId) const
{
	auto abilityCardData = _cardConfigService->GetCardData<FAbilityCardDataRaw>(cardId);
	cardEntity.set<ExplodingCardComponent>({abilityCardData->BaseDamage, abilityCardData->Radius});
}
