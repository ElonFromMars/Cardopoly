#include "GridObjectsDataProvider.h"

GridObjectsDataProvider::GridObjectsDataProvider(UBuildingConfigHolder* buildingCardsConfig)
{
	_buildingCardsConfig = buildingCardsConfig;
}

TArray<FIntVector> GridObjectsDataProvider::GetLocalPositions(uint32 id)
{
	return {};//TODO ASAP fix 
}

GridObjectsDataProvider::~GridObjectsDataProvider()
{
	
}
