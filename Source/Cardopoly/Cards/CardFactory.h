#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardFactory.generated.h"

class UGameplayAssetData;
class ACard;

UCLASS()
class CARDOPOLY_API UCardFactory : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init(UGameplayAssetData* gameplayAssetData, UWorld* world);
	virtual ACard* CreateCard();

private:
	UPROPERTY()
	UGameplayAssetData* GameplayAssetData;
	UPROPERTY()
	UWorld* World;
};
