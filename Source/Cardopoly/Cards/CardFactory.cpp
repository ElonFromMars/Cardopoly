#include "CardFactory.h"
#include "Card.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"
#include "Cardopoly/Configs/Cards/CardConfigService.h"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"

void UCardFactory::Construct(
	UWorld* world,
	UGameplayAssetData* gameplayAssetData,
	PositionConversionService* positionConversionService,
	BuildingPrototypeService* buildingPrototypeService,
	BuildingService* buildingService,
	CardConfigService* cardConfigService
	)
{
	World = world;
	GameplayAssetData = gameplayAssetData;
	_positionConversionService = positionConversionService;
	_buildingPrototypeService = buildingPrototypeService;
	_buildingService = buildingService;
	_cardConfigService = cardConfigService;
}

ACard* UCardFactory::CreateCard(flecs::entity entity)
{
	FName cardId = entity.get<CardComponent>()->Id;
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];

	auto cardData = _cardConfigService->GetBaseCardData(cardId);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	
	Card->Construct(_buildingService, _positionConversionService, _buildingPrototypeService, entity);

	if(auto CardWidget = Card->GetCardWidget())
	{
		CardWidget->SetDescription(cardData.Description);
        CardWidget->SetName(cardData.Name);
        CardWidget->SetCost(FText::AsNumber(cardData.Cost));
	}
	
	return Card;
}
