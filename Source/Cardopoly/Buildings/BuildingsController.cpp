#include "BuildingsController.h"
#include "Cardopoly/Buildings/ABuilding.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/Grid/UGridSubsystem.h"
#include "Kismet/GameplayStatics.h"


void ABuildingsController::Construct(UCityGrid* cityGrid, BuildingEntityFactory* buildingEntityFactory)
{
	CityGrid = cityGrid;
	_buildingEntityFactory = buildingEntityFactory;
}

void ABuildingsController::BeginPlay()
{
	Super::BeginPlay();
	_gridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();//TODO remove
}

bool ABuildingsController::CreateBuildingUnderScreenPosition(const FVector2D ScreenPosition, const uint32 id, ABuilding*& Building) const
{
	FIntVector cellPosition;

	if(ScreenPointToGroundPosition(ScreenPosition, cellPosition)
		&& !IsCellOccupied(cellPosition))
	{
		Building = CreateBuilding(cellPosition, id);
		return true;
	}
	
	return false;
}

ABuilding* ABuildingsController::CreateBuilding(const FIntVector cellPosition, const uint32 id) const
{
	_buildingEntityFactory->Create(cellPosition, id);
	const FVector CellWorldPosition = _gridSubsystem->GetCellCenterWorldPosition(cellPosition);

	//TODO: rewrite asap
	/*ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(ABuilding::StaticClass(), CellWorldPosition,FRotator::ZeroRotator);

	CityGrid->PutBuildingAtPosition(cellPosition, Building);
	
	return Building;*/

	return nullptr;
}

bool ABuildingsController::CanCreateBuildingUnderScreenPosition(const FVector2D ScreenPosition) const
{
	FIntVector CellPosition;
	if (!IsValid(CityGrid))
	{
		UE_LOG(LogTemp, Error, TEXT("%hs"), "CityGrid = null");
		return false;
	}
	return ScreenPointToGroundPosition(ScreenPosition, CellPosition)
		&& !IsCellOccupied(CellPosition);
}

bool ABuildingsController::IsCellOccupied(FIntVector CellPosition) const
{
	return CityGrid->ContainsBuildingAtPosition(CellPosition);
}

bool ABuildingsController::ScreenPointToGroundPosition(const FVector2D ScreenPosition, FIntVector& CellPosition) const
{
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FVector RayStart;
		FVector RayDirection;

		UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPosition, RayStart, RayDirection);
		
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		UWorld* World = GetWorld();
		if (World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_GameTraceChannel1, CollisionParams))
		{
			CellPosition = _gridSubsystem->WorldPositionToGrid(HitResult.Location);
			return true;
		}
	}
	return false;
}
