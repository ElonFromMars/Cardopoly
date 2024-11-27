#include "GridLayout.h"

#include "Cardopoly/Settings/CustomWorldSettings.h"
#include "Cardopoly/Settings/GameplayWorldSettings.h"

void GridLayout::Construct(UWorld* inViewWorld)
{
	const UGameplayWorldSettings* gameplayWorldSettings = ACustomWorldSettings::GetGameplayWorldSettings(*inViewWorld);
	CellSize = gameplayWorldSettings->CellSize;
	HalfCellSize = CellSize / 2;
}

FIntVector GridLayout::WorldPositionToGrid(const FVector worldPosition) const
{
	const int gridX = FMath::Floor(worldPosition.X / CellSize);
	const int gridY = FMath::Floor(worldPosition.Y / CellSize);
	return FIntVector(gridX, gridY, 0);
}

FVector GridLayout::GetCellCenterWorldPosition(const FIntVector gridPosition) const
{
	return GetCellCenterWorldPosition(gridPosition.X, gridPosition.Y);
}

FVector GridLayout::GetCellCenterWorldPosition(const int x, const int y) const
{
	const double worldX = x * CellSize + HalfCellSize;
	const double worldY = y * CellSize + HalfCellSize;
	return FVector(worldX, worldY, 0);
}

FVector GridLayout::GetClosestCellCenterWorldPosition(const FVector worldPosition) const
{
	const FIntVector cllPosition = WorldPositionToGrid(worldPosition);
	const FVector cllWorldPosition = GetCellCenterWorldPosition(cllPosition);
	return cllWorldPosition;
}
