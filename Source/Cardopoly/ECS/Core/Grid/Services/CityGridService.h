#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include "IGridObjectsDataProvider.hpp"

class CityGridService
{
public:
	CityGridService(IGridObjectsDataProvider* gridObjectsDataProvider);
	
	bool ContainsBuildingAtPosition(FIntVector Position) const;

	void PutEntityAtPosition(FIntVector Position, flecs::entity entity);

	bool GetBuildingAtPosition(FIntVector Position, flecs::entity& entity);

	bool IsValidPosition(const FIntVector& Pos);

private:
	TMap<FIntVector, flecs::entity> _entityByCellPosition;

	IGridObjectsDataProvider* _gridObjectsDataProvider;
};
