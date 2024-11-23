#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ObjectMacros.h"
#include "FBuildingGridData.generated.h"

USTRUCT(BlueprintType)
struct FBuildingGridData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> GridCells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Columns = 0;
};