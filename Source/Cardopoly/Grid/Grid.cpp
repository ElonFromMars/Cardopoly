#include "Grid.h"
#include "FGridCell.h"
#include "IOccupyGrid.h"
#include "IOccupyGridData.h"

void UGrid::AddObjectToCell(FIntVector position, IOccupyGrid* gridObject)
{
	IOccupyGridData* gridData = gridObject->GetGridData();
	for (const FIntVector& localPositionIt : gridData->GetLocalPositions())
	{
		m_gridCells.FindOrAdd(position + localPositionIt).Objects.Add(gridObject);
	}
}

const TArray<IOccupyGrid*>* UGrid::TryGetObjectsInCell(FIntVector position) const
{
	if (const FGridCell* cell = m_gridCells.Find(position))
	{
		return &cell->Objects;
	}
	return nullptr;

}

void UGrid::RemoveObject(FIntVector position, IOccupyGrid* gridObject)
{
	IOccupyGridData* gridData = gridObject->GetGridData();
	for(const FIntVector& localPositionIt : gridData->GetLocalPositions())
	{
		FIntVector cellPosition = position + localPositionIt;
		if(m_gridCells.Contains(cellPosition))
		{
			TMap<FIntVector, FGridCell>::ValueType cell = m_gridCells[cellPosition];
			cell.Objects.Remove(gridObject);
			if(cell.Objects.Num() == 0)
			{
				m_gridCells.Remove(cellPosition);
			}
		}
	}
}
