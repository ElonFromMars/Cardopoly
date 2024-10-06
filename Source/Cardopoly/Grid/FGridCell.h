#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGridCell.generated.h"

class IOccupyGrid;

USTRUCT()
struct FGridCell
{
	GENERATED_BODY()
	
	TArray<IOccupyGrid*> Objects;
};