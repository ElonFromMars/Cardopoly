#pragma once
#include "Engine/DataAsset.h"
#include "UBuildingsHolder.generated.h"

class ABuilding;

UCLASS(BlueprintType)
class UBuildingsHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<FName, TSubclassOf<ABuilding>> BuildingsById;
};
