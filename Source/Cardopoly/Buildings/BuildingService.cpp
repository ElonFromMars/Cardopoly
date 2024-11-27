#include "BuildingService.h"

#include "Cardopoly/Configs/Buildings/UBuildingConfig.h"
#include "Cardopoly/Configs/Buildings/UBuildingConfigHolder.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Kismet/GameplayStatics.h"

bool BuildingService::CreateBuildingUnderScreenPosition(const FVector2D ScreenPosition, const uint32 id, flecs::entity& building) const
{
	FIntVector cellPosition;

	if(ScreenPointToGroundPosition(ScreenPosition, cellPosition)
		&& !IsCellOccupied(cellPosition))
	{
		building = CreateBuilding(cellPosition, id);
		return true;
	}
	
	return false;
}

flecs::entity BuildingService::CreateBuilding(const FIntVector cellPosition, const uint32 id) const
{
	flecs::entity buildingEntity = _buildingEntityFactory->Create(cellPosition, id);
	const FVector CellWorldPosition = _gridLayout->GetCellCenterWorldPosition(cellPosition);

	//TODO rewrite asap
	/*ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(ABuilding::StaticClass(), CellWorldPosition,FRotator::ZeroRotator);

	CityGrid->PutBuildingAtPosition(cellPosition, Building);
	
	return Building;*/


	_cityGrid->PutEntityAtPosition(cellPosition, buildingEntity);
	for (auto building : _buildingConfigHolder->BuildingsById)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building: %d"), building.Key);
		for (auto cell : building.Value->GridData.GetCellsAsIntVectors())
		{
			UE_LOG(LogTemp, Warning, TEXT("Cell: %s"), *cell.ToString());
		}
	}
	
	return buildingEntity;
}

bool BuildingService::CanCreateBuildingUnderScreenPosition(const FVector2D screenPosition) const
{
	FIntVector CellPosition;
	return ScreenPointToGroundPosition(screenPosition, CellPosition)
		&& !IsCellOccupied(CellPosition);
}

bool BuildingService::IsCellOccupied(FIntVector cellPosition) const
{
	return _cityGrid->ContainsBuildingAtPosition(cellPosition);
}

bool BuildingService::ScreenPointToGroundPosition(const FVector2D screenPosition, FIntVector& cellPosition) const
{
	if(APlayerController* PlayerController = _viewWorld->GetFirstPlayerController())
	{
		FVector RayStart;
		FVector RayDirection;

		UGameplayStatics::DeprojectScreenToWorld(PlayerController, screenPosition, RayStart, RayDirection);
		
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		
		if (_viewWorld->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_GameTraceChannel1, CollisionParams))
		{
			cellPosition = _gridLayout->WorldPositionToGrid(HitResult.Location);
			return true;
		}
	}
	return false;
}
