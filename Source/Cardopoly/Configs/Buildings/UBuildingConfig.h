#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UBuildingConfig.generated.h"

UCLASS()
class CARDOPOLY_API UBuildingConfig : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Income = 0;
};
