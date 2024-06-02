#include "CardFactory.h"
#include "Card.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/CardsHolder.h"
#include "Cardopoly/Configs/ViewAssetIdConfig.h"

void UCardFactory::Init(UGameplayAssetData* gameplayAssetData, UWorld* world)
{
	this->GameplayAssetData = gameplayAssetData;
	this->World = world;
}

ACard* UCardFactory::CreateCard()
{
	check(GameplayAssetData->CardsHolder);
	
	const TSubclassOf<ACard> CardAsset = GameplayAssetData->CardsHolder->CardByName[ViewAssetIdConfig::CardId];

	check(CardAsset);
	
	ACard* Card = World->SpawnActor<ACard>(CardAsset, FVector(), FRotator());
	
	return Card;
}
