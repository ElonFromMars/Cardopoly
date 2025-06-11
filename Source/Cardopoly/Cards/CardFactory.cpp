#include "CardFactory.h"
#include "Card.h"
#include "CardViewComponent.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"
#include "Kismet/KismetMathLibrary.h"

void UCardFactory::Construct(
	UWorld* world,
	UGameplayAssetData* gameplayAssetData,
	PositionConversionService* positionConversionService,
	BuildingPrototypeService* buildingPrototypeService,
	BuildingService* buildingService,
	ULocalConfigHolder* localConfigHolder
	)
{
	World = world;
	GameplayAssetData = gameplayAssetData;
	_positionConversionService = positionConversionService;
	_buildingPrototypeService = buildingPrototypeService;
	_buildingService = buildingService;
	BuildingCardsConfig = localConfigHolder->BuildingCardsConfig;
}

ACard* UCardFactory::CreateCard(flecs::entity entity)
{
	FName cardId = entity.get<CardComponent>()->Id;
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];
	
	FString ContextString = "houses query";
	FBuildingCardDataRaw* CardData = BuildingCardsConfig->FindRow<FBuildingCardDataRaw>(cardId, ContextString);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	
	Card->Construct(_buildingService, _positionConversionService, _buildingPrototypeService, entity);

	if(auto CardWidget = Card->GetCardWidget())
	{
		CardWidget->SetDescription(CardData->Description);
        CardWidget->SetName(CardData->Name);
        CardWidget->SetCost(FText::AsNumber(CardData->Cost));
	}
	
	return Card;
}
