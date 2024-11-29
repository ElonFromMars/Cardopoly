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
		FIntVector leftBottomPosition = FIntVector(-building.Value->GridData.Columns / 2, -building.Value->GridData.Rows / 2, 0);
		
		TArray<FIntVector> localPositions;
		for (FIntVector localPosition : building.Value->GridData.GetCellsAsIntVectors())
		{
			localPositions.Add(localPosition + leftBottomPosition);
		}
		uint32 key = static_cast<uint32>(building.Key);

		float xCenterOffset = building.Value->GridData.Columns % 2 == 0 ? -50.0f : 0;
		float yCenterOffset = building.Value->GridData.Rows % 2 == 0 ? -50.0f : 0;//TODO use cell size from unique config
		
		FVector centerOffset = FVector(xCenterOffset, yCenterOffset, 0);
		_localBuildingsPositionsById.Emplace(key, {localPositions, centerOffset});
	}
}

const TArray<FIntVector>& GridObjectsDataProvider::GetGridLocalPositions(uint32 id)
{
	return _localBuildingsPositionsById[id].GridCells;
}

const FVector GridObjectsDataProvider::GetCenterOffset(uint32 id)
{
	return _localBuildingsPositionsById[id].CenterOffset;
}

GridObjectsDataProvider::~GridObjectsDataProvider()
{
	
}
