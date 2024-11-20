#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocalConfigHolder.generated.h"

class UBuildingConfigHolder;
class UInputLocalConfig;
class UHandLocalConfig;

UCLASS()
class CARDOPOLY_API ULocalConfigHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHandLocalConfig* HandLocalConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBuildingConfigHolder* BuildingConfigHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputLocalConfig* InputLocalConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* BuildingCardsConfig;
};
