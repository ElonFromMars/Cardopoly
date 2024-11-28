#include "GridObjectsDataProvider.h"

#include "UBuildingConfig.h"

GridObjectsDataProvider::GridObjectsDataProvider(UBuildingConfigHolder* buildingConfigHolder)
{
	_buildingCardsConfig = buildingConfigHolder;
}

void GridObjectsDataProvider::Initialize()
{
	for (auto& building : _buildingCardsConfig->BuildingsById)
	{
		TArray<FIntVector> localPositions;
		for (FIntVector localPosition : building.Value->GridData.GetCellsAsIntVectors())
		{
			localPositions.Add(localPosition);
		}
		uint32 key = static_cast<uint32>(building.Key);
		_localBuildingsPositionsById.Add(key, localPositions);
	}
}

const TArray<FIntVector>& GridObjectsDataProvider::GetLocalPositions(uint32 id)
{
	return _localBuildingsPositionsById[id];
}

GridObjectsDataProvider::~GridObjectsDataProvider()
{
	
}
