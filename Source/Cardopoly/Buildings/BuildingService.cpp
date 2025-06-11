#include "BuildingService.h"

#include "Cardopoly/Configs/Buildings/GridObjectsDataProvider.h"
#include "Cardopoly/Configs/Buildings/UBuildingConfig.h"
#include "Cardopoly/Configs/Buildings/UBuildingConfigHolder.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/Grid/PositionConversionService.h"

bool BuildingService::CreateBuildingUnderScreenPosition(const FVector2D ScreenPosition, const uint32 id, flecs::entity& building) const
{
	FIntVector cellPosition;

	if(_positionConversionService->ScreenPointToGroundPosition(ScreenPosition, cellPosition)
		&& !IsBuildingOverlaps(cellPosition, id))
	{
		building = CreateBuilding(cellPosition, id);
		return true;
	}
	
	return false;
}

bool BuildingService::TryCreateBuilding(const FIntVector& cellPosition, const uint32 id, flecs::entity& building) const
{
	if(!IsBuildingOverlaps(cellPosition, id))
	{
		building = CreateBuilding(cellPosition, id);
		return true;
	}
	
	return false;
}

flecs::entity BuildingService::CreateBuilding(const FIntVector cellPosition, const uint32 id) const
{
	flecs::entity building = _buildingEntityFactory->Create(cellPosition, id);
	const FVector CellWorldPosition = _gridLayout->GetCellCenterWorldPosition(cellPosition);
	
	_cityGrid->PutEntityAtPosition(cellPosition, building, id);
	for (auto buildingConfigIt : _buildingConfigHolder->BuildingsById)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building: %d"), buildingConfigIt.Key);
		for (auto cell : buildingConfigIt.Value->GridData.GetCellsAsIntVectors())
		{
			UE_LOG(LogTemp, Warning, TEXT("Cell: %s"), *cell.ToString());
		}
	}
	
	return building;
}

bool BuildingService::CanCreateBuildingUnderScreenPosition(const FVector2D screenPosition, const uint32 id) const
{
	FIntVector CellPosition;
	return _positionConversionService->ScreenPointToGroundPosition(screenPosition, CellPosition)
		&& !IsBuildingOverlaps(CellPosition, id);
}

bool BuildingService::IsBuildingOverlaps(FIntVector cellPosition, const uint32 id) const
{
	const TArray<FIntVector>& positions = _gridObjectsDataProvider->GetGridLocalPositions(id);

	for (auto& pos : positions)
	{
		if(_cityGrid->ContainsBuildingAtPosition(cellPosition + pos))
		{
			return true;
		}
	}
	
	return _cityGrid->ContainsBuildingAtPosition(cellPosition);
}
