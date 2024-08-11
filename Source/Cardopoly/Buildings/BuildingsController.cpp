#include "BuildingsController.h"
#include "Cardopoly/Buildings/ABuilding.h"
#include "Cardopoly/Grid/UGridSubsystem.h"
#include "Kismet/GameplayStatics.h"

ABuildingsController::ABuildingsController()
{
	
}

void ABuildingsController::Construct(UCityGrid* cityGrid)
{
	CityGrid = cityGrid;
}

void ABuildingsController::BeginPlay()
{
	Super::BeginPlay();
	GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();//TODO remove
}

bool ABuildingsController::CreateBuildingUnderScreenPosition(FVector2D ScreenPosition, ABuilding*& Building) const
{
	FIntVector CellPosition;

	if(ScreenPointToGroundPosition(ScreenPosition, CellPosition)
		&& !IsCellOccupied(CellPosition))
	{
		Building = CreateBuilding(CellPosition);
		return true;
	}
	
	return false;
}

ABuilding* ABuildingsController::CreateBuilding(const FIntVector CellPosition) const
{
	const FVector CellWorldPosition = GridSubsystem->GetCellCenterWorldPosition(CellPosition);

	ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(ABuilding::StaticClass(), CellWorldPosition,FRotator::ZeroRotator);

	CityGrid->PutBuildingAtPosition(CellPosition, Building);
	
	return Building;
}

bool ABuildingsController::CanCreateBuildingUnderScreenPosition(FVector2D ScreenPosition) const
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
			CellPosition = GridSubsystem->WorldPositionToGrid(HitResult.Location);
			return true;
		}
	}
	return false;
}
