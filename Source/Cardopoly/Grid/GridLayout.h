#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

class GridLayout
{
public:
	void Construct(UWorld* inViewWorld);
	
	FIntVector WorldPositionToGrid(const FVector worldPosition) const;
	
	FVector GetCellCenterWorldPosition(const FIntVector gridPosition) const;
	FVector GetCellCenterWorldPosition(int x, int y) const;
	
	FVector GetClosestCellCenterWorldPosition(const FVector worldPosition) const;
	
	double CellSize;
	double HalfCellSize;
};
