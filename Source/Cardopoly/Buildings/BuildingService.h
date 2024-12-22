#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/ECS/Core/Grid/Services/CityGridService.h"
#include "GameFramework/Actor.h"

class PositionConversionService;
class GridObjectsDataProvider;
class UBuildingConfigHolder;
class GridLayout;

class BuildingService
{
public:
	BuildingService(
		CityGridService* cityGrid,
		BuildingEntityFactory* buildingEntityFactory,
		GridLayout* gridLayout,
		UBuildingConfigHolder* buildingConfigHolder,
		GridObjectsDataProvider* gridObjectsDataProvider,
		PositionConversionService* positionConversionService
	)
		: _gridLayout(gridLayout),
		_cityGrid(cityGrid),
		_buildingEntityFactory(buildingEntityFactory),
		_buildingConfigHolder(buildingConfigHolder),
		_gridObjectsDataProvider(gridObjectsDataProvider),
		_positionConversionService(positionConversionService)
	{
		
	}

	bool CreateBuildingUnderScreenPosition(const FVector2D screenPosition, const uint32 id, flecs::entity& building) const;

	flecs::entity CreateBuilding(const FIntVector cellPosition, const uint32 id) const;

	bool CanCreateBuildingUnderScreenPosition(const FVector2D screenPosition, const uint32 id) const;
	bool IsBuildingOverlaps(FIntVector cellPosition, const uint32 id) const;

private:
	GridLayout* _gridLayout;
	CityGridService* _cityGrid;
	BuildingEntityFactory* _buildingEntityFactory;
	UBuildingConfigHolder* _buildingConfigHolder;
	GridObjectsDataProvider* _gridObjectsDataProvider;
	PositionConversionService* _positionConversionService;
};
