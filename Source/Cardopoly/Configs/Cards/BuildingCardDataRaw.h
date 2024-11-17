#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/EBuildingViewIdConfig.h"
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
	int32 Income = 0;

	UPROPERTY(EditAnywhere)
	EBuildingViewIdConfig ViewId;
};
