// Fill out your copyright notice in the Description page of Project Settings.


#include "IOccupyGrid.h"


// Add default functionality here for any IGridObject functions that are not pure virtual.
FIntVector2 IOccupyGrid::GetCenter()
{
	return FIntVector2();
}

TArray<FIntVector2> IOccupyGrid::GetPositions()
{
	return TArray<FIntVector2>();
}
