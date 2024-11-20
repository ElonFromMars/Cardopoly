#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/Buildings/EBuildingIdConfig.h"
#include "BuildingCardDataRaw.generated.h"

USTRUCT()
struct FBuildingCardDataRaw : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	int32 Cost = 0;

	UPROPERTY(EditAnywhere)
	EBuildingIdConfig BuildingId;
};
