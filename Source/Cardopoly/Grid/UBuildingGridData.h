#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ObjectMacros.h"
#include "UBuildingGridData.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class UBuildingGridData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> GridCells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Columns;
};