// Fill out your copyright notice in the Description page of Project Settings.


#include "UGridSubsystem.h"

#include "Cardopoly/Settings/CustomWorldSettings.h"
#include "Cardopoly/Settings/GameplayWorldSettings.h"


void UGridSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	const UGameplayWorldSettings* GameplayWorldSettings = ACustomWorldSettings::GetGameplayWorldSettings(InWorld);
	
	CellSize = GameplayWorldSettings->CellSize;
	HalfCellSize = CellSize / 2;
}

FIntVector UGridSubsystem::WorldPositionToGrid(const FVector WorldPosition) const
{
	const int GridX = FMath::Floor(WorldPosition.X / CellSize);
	const int GridY = FMath::Floor(WorldPosition.Y / CellSize);
	return FIntVector(GridX, GridY, 0);
}

FVector UGridSubsystem::GetCellCenterWorldPosition(const FIntVector GridPosition) const
{
	return GetCellCenterWorldPosition(GridPosition.X, GridPosition.Y);
}

FVector UGridSubsystem::GetCellCenterWorldPosition(const int X, const int Y) const
{
	const double WorldX = X * CellSize + HalfCellSize;
	const double WorldY = Y * CellSize + HalfCellSize;
	return FVector(WorldX, WorldY, 0);
}

FVector UGridSubsystem::GetClosestCellCenterWorldPosition(const FVector WorldPosition) const
{
	const FIntVector CellPosition = WorldPositionToGrid(WorldPosition);
	const FVector CellWorldPosition = GetCellCenterWorldPosition(CellPosition);
	return CellWorldPosition;
}
