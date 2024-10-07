#include "CityGrid.h"

bool UCityGrid::ContainsBuildingAtPosition(FIntVector Position) const
{
	return BuildingByCellPosition.Contains(Position);
}

void UCityGrid::PutBuildingAtPosition(FIntVector Position, ABuilding* Building)
{
	BuildingByCellPosition.Add(Position, Building);
}

bool UCityGrid::GetBuildingAtPosition(FIntVector Position, ABuilding*& Building)
{
	if (ContainsBuildingAtPosition(Position))
	{
		Building = BuildingByCellPosition[Position];
		return true;
	}
	return false;
}

//TODO implement
bool UCityGrid::IsValidPosition(const FIntVector& Pos)
{
	return true;
}
