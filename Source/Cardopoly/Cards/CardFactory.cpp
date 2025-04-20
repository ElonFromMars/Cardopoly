#include "CardFactory.h"
#include "Card.h"
#include "CardViewComponent.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Kismet/KismetMathLibrary.h"

void UCardFactory::Construct(
	UWorld* world,
	UGameplayAssetData* gameplayAssetData,
	BuildingService* buildingsService,
	BuildingPrototypeService* buildingPrototypeService,
	ULocalConfigHolder* localConfigHolder
	)
{
	World = world;
	GameplayAssetData = gameplayAssetData;
	_buildingsService = buildingsService;
	_buildingPrototypeService = buildingPrototypeService;
	BuildingCardsConfig = localConfigHolder->BuildingCardsConfig;
}

ACard* UCardFactory::CreateCard(FName cardId)
{
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];
	
	FString ContextString = "houses query";
	FBuildingCardDataRaw* CardData = BuildingCardsConfig->FindRow<FBuildingCardDataRaw>(cardId, ContextString);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	Card->Construct(_buildingsService, _buildingPrototypeService, static_cast<uint32>(CardData->BuildingId));//TODO replace with function call

	if(auto CardWidget = Card->GetCardWidget())
	{
		CardWidget->SetDescription(CardData->Description);
        CardWidget->SetName(CardData->Name);
        CardWidget->SetCost(FText::AsNumber(CardData->Cost));
	}
	
	return Card;
}
