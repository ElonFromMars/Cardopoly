﻿#pragma once

#include "Cardopoly/Configs/Buildings/EBuildingIdConfig.h"
#include "Engine/DataAsset.h"
#include "UBuildingsViewHolder.generated.h"

class ABuilding;

UCLASS(BlueprintType)
class UBuildingsViewHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<EBuildingIdConfig, TSubclassOf<ABuilding>> BuildingsById;
};
