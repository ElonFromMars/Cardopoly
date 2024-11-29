#pragma once

#include "FBuildingLookupData.h"
#include "UBuildingConfigHolder.h"
#include "Cardopoly/ECS/Core/Grid/Services/IGridObjectsDataProvider.hpp"

class GridObjectsDataProvider : public IGridObjectsDataProvider
{
public:
	GridObjectsDataProvider(UBuildingConfigHolder* buildingCardsConfig);

	void Initialize();
	
	virtual const TArray<FIntVector>& GetGridLocalPositions(uint32 id) override;

	virtual const FVector GetCenterOffset(uint32 id) override;
	
	virtual ~GridObjectsDataProvider() override;

private:
	UBuildingConfigHolder* _buildingCardsConfig;

	TMap<uint32, FBuildingLookupData> _localBuildingsPositionsById;
};
