#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOccupyGrid.generated.h"


class IOccupyGridData;

UINTERFACE()
class UOccupyGrid : public UInterface
{
	GENERATED_BODY()
};

class CARDOPOLY_API IOccupyGrid
{
	GENERATED_BODY()

public:
	virtual FIntVector GetPosition() = 0;
	
	virtual IOccupyGridData* GetGridData() = 0;
};
