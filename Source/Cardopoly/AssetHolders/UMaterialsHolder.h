#pragma once

#include "Cardopoly/Configs/Buildings/EMaterialIdConfig.h"
#include "Engine/DataAsset.h"
#include "UMaterialsHolder.generated.h"

class ABuilding;

UCLASS(BlueprintType)
class UMaterialsHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<EMaterialIdConfig, UMaterialInstance*> MaterialById;
};
