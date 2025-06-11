#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include "IGridObjectsDataProvider.hpp"

class CityGridService
{
public:
	CityGridService(IGridObjectsDataProvider* gridObjectsDataProvider);
	
	bool ContainsBuildingAtPosition(const FIntVector Position) const;

	void PutEntityAtPosition(const FIntVector Position, const flecs::entity entity);
	
	void PutEntityAtPosition(FIntVector Position, flecs::entity entity, uint32 id);

	bool GetBuildingAtPosition(const FIntVector Position, flecs::entity& entity);

	bool IsValidPosition(const FIntVector& Pos);

private:
	TMap<FIntVector, flecs::entity> _entityByCellPosition;

	IGridObjectsDataProvider* _gridObjectsDataProvider;
};
