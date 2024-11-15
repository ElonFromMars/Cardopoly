#pragma once

#include "Cardopoly/Configs/EBuildingViewIdConfig.h"
#include "Engine/DataAsset.h"
#include "UBuildingsViewHolder.generated.h"

class ABuilding;

UCLASS(BlueprintType)
class UBuildingsViewHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<EBuildingViewIdConfig, TSubclassOf<ABuilding>> BuildingsById;
};
