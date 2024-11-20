#pragma once

#include "UBuildingConfigHolder.h"
#include "Cardopoly/ECS/Core/Grid/Services/IGridObjectsDataProvider.hpp"

class GridObjectsDataProvider : public IGridObjectsDataProvider
{
public:
	GridObjectsDataProvider(UBuildingConfigHolder* buildingCardsConfig);
	
	virtual TArray<FIntVector> GetLocalPositions(uint32 id) override;
	
	virtual ~GridObjectsDataProvider() override;

private:
	UBuildingConfigHolder* _buildingCardsConfig;
};
