#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/CardopolyGameMode.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "UObject/Object.h"
#include "CardFactory.generated.h"

class ULocalConfigHolder;
class UGameplayAssetData;
class ACard;
class BuildingService;

UCLASS()
class CARDOPOLY_API UCardFactory : public UObject
{
	GENERATED_BODY()

public:
	void Construct(
		UWorld* world,
		UGameplayAssetData* gameplayAssetData,
		BuildingService* buildingsService,
		BuildingPrototypeService* buildingPrototypeService,
		ULocalConfigHolder* localConfigHolder
	);
	
	virtual ACard* CreateCard();

private:
	UPROPERTY()
	UGameplayAssetData* GameplayAssetData;
	UPROPERTY()
	UDataTable* BuildingCardsConfig;
	UPROPERTY()
	UWorld* World;

	BuildingService* _buildingsService;
	BuildingPrototypeService* _buildingPrototypeService;
};
