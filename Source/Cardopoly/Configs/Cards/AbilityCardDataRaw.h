#pragma once

#include "CoreMinimal.h"
#include "AbilityCardDataRaw.generated.h"

USTRUCT()
struct FAbilityCardDataRaw : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	int Cost = 0;

	UPROPERTY(EditAnywhere)
	int Radius = 0;

	UPROPERTY(EditAnywhere)
	int BaseDamage = 0;
};
