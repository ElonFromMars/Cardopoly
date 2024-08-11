#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardFactory.generated.h"

class UGameplayAssetData;
class ACard;
class ABuildingsController;

UCLASS()
class CARDOPOLY_API UCardFactory : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UGameplayAssetData* GameplayAssetData;
	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	ABuildingsController* BuildingsController;
	
public:
	virtual void Construct(UWorld* world, UGameplayAssetData* gameplayAssetData, ABuildingsController* buildingsController);
	virtual ACard* CreateCard();


};
