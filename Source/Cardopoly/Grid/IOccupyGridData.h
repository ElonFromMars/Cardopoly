#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOccupyGridData.generated.h"


UINTERFACE()
class UOccupyGridData : public UInterface
{
	GENERATED_BODY()
};

class CARDOPOLY_API IOccupyGridData
{
	GENERATED_BODY()

public:
	virtual FIntVector GetCenter() = 0;
	
	virtual TArray<FIntVector> GetLocalPositions() = 0;
};
