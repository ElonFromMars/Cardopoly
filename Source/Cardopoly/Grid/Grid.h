#pragma once

#include "CoreMinimal.h"
#include "FGridCell.h"
#include "UObject/Object.h"
#include "Grid.generated.h"

class IOccupyGrid;

UCLASS()
class CARDOPOLY_API UGrid : public UObject
{
	GENERATED_BODY()
	
	TMap<FIntVector, FGridCell> m_gridCells;

public:
	void AddObjectToCell(FIntVector position, IOccupyGrid* gridObject);

	const TArray<IOccupyGrid*>* TryGetObjectsInCell(FIntVector position) const;

	bool ContainsObjectsInCell(FIntVector position) const
	{
		return m_gridCells.Contains(position);
	}

	void RemoveObject(FIntVector position, IOccupyGrid* gridObject);
};