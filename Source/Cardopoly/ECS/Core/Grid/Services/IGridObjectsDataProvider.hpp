#pragma once

class IGridObjectsDataProvider
{
public:
	virtual const TArray<FIntVector>& GetLocalPositions(uint32 id) = 0;
	
	virtual ~IGridObjectsDataProvider() = default;
};
