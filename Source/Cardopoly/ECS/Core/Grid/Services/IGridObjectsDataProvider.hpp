#pragma once

class IGridObjectsDataProvider
{
public:
	virtual const TArray<FIntVector>& GetGridLocalPositions(uint32 id) = 0;

	virtual const FVector GetCenterOffset(uint32 id) = 0;
	
	virtual ~IGridObjectsDataProvider() = default;
};
