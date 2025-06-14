#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/CardopolyGameMode.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "UObject/Object.h"
#include "CardFactory.generated.h"

class CardConfigService;
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
		PositionConversionService* positionConversionService,
		BuildingPrototypeService* buildingPrototypeService,
		BuildingService* buildingsService,
		CardConfigService* cardConfigService
	);
	
	virtual ACard* CreateCard(flecs::entity entity);

private:
	UPROPERTY()
	UGameplayAssetData* GameplayAssetData;
	UPROPERTY()
	UWorld* World;

	BuildingService* _buildingService;
	BuildingPrototypeService* _buildingPrototypeService;
	PositionConversionService* _positionConversionService;
	CardConfigService* _cardConfigService;
};
