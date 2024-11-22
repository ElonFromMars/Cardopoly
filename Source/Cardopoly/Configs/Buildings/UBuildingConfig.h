#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Grid/UBuildingGridData.h"
#include "Engine/DataAsset.h"
#include "UBuildingConfig.generated.h"

UCLASS()
class CARDOPOLY_API UBuildingConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 Income = 0;

	UPROPERTY(EditAnywhere, Instanced)
	UBuildingGridData* GridData;
};
