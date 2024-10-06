#include "CityGrid.h"

bool UCityGrid::ContainsBuildingAtPosition(FIntVector position) const
{
	return m_buildingByCellPosition.Contains(position);
}

void UCityGrid::PutBuildingAtPosition(FIntVector position, ABuilding* building)
{
	m_buildingByCellPosition.Add(position, building);
}

bool UCityGrid::TryGetBuildingAtPosition(FIntVector position, ABuilding*& outBuilding)
{
	if (ContainsBuildingAtPosition(position))
	{
		outBuilding = m_buildingByCellPosition[position];
		return true;
	}
	return false;
}
