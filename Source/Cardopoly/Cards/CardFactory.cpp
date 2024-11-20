#include "CardFactory.h"
#include "Card.h"
#include "CardViewComponent.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Kismet/KismetMathLibrary.h"

void UCardFactory::Construct(
	UWorld* world,
	UGameplayAssetData* gameplayAssetData,
	ABuildingsController* buildingsController,
	ULocalConfigHolder* localConfigHolder)
{
	World = world;
	GameplayAssetData = gameplayAssetData;
	BuildingsController = buildingsController;
	BuildingCardsConfig = localConfigHolder->BuildingCardsConfig;
}

ACard* UCardFactory::CreateCard()
{
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];


	//TODO move to appropriate place
	TArray<FName> RowNames = BuildingCardsConfig->GetRowNames();
	int32 RandomIndex = UKismetMathLibrary::RandomInteger(RowNames.Num());
	FName RandomRowName = RowNames[RandomIndex];

	
	FString ContextString = "houses query";
	FBuildingCardDataRaw* CardData = BuildingCardsConfig->FindRow<FBuildingCardDataRaw>(RandomRowName, ContextString);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	Card->Construct(BuildingsController, static_cast<uint32>(CardData->BuildingId));//TODO replace with function call

	if(auto CardWidget = Card->GetCardWidget())
	{
		CardWidget->SetDescription(CardData->Description);
        CardWidget->SetName(CardData->Name);
        CardWidget->SetCost(FText::AsNumber(CardData->Cost));
	}
	
	return Card;
}
