#include "CardFactory.h"
#include "Card.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"

void UCardFactory::Construct(
	UWorld* world,
	UGameplayAssetData* gameplayAssetData,
	ABuildingsController* buildingsController)
{
	World = world;
	GameplayAssetData = gameplayAssetData;
	BuildingsController = buildingsController;
}

ACard* UCardFactory::CreateCard()
{
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];

	check(CardAsset);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	Card->Construct(BuildingsController);
	
	return Card;
}
