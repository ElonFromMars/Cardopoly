#pragma once
#include "Engine/DataTable.h"
#include "FTestDataTableRow.generated.h"

class ABuilding;

USTRUCT(BlueprintType)
struct FTestDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> Building;
};
