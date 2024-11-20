#pragma once

#include "Cardopoly/Configs/Buildings/EBuildingIdConfig.h"
#include "Engine/DataAsset.h"
#include "UBuildingConfigHolder.generated.h"

class UBuildingConfig;

UCLASS(BlueprintType)
class UBuildingConfigHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<EBuildingIdConfig, UBuildingConfig*> BuildingsById;
};

