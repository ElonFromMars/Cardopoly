#include "CityGridService.h"

#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"

CityGridService::CityGridService(IGridObjectsDataProvider* gridObjectsDataProvider)
	: _gridObjectsDataProvider(gridObjectsDataProvider)
{
	
}

bool CityGridService::ContainsBuildingAtPosition(FIntVector Position) const
{
	return _entityByCellPosition.Contains(Position);
}

void CityGridService::PutEntityAtPosition(FIntVector Position, flecs::entity entity)
{
	if (entity.has<FIdComponent>())
	{
		uint32 id = entity.get<FIdComponent>()->Value;
		TArray<FIntVector> localPositions = _gridObjectsDataProvider->GetLocalPositions(id);
		for (FIntVector localPosition : localPositions)
		{
			FIntVector absolutePosition = Position + localPosition;
			_entityByCellPosition.Add(absolutePosition, entity);
		}
	}
}

bool CityGridService::GetBuildingAtPosition(FIntVector Position, flecs::entity& entity)
{
	if (ContainsBuildingAtPosition(Position))
	{
		entity = _entityByCellPosition[Position];
		return true;
	}
	return false;
}

//TODO implement
bool CityGridService::IsValidPosition(const FIntVector& Pos)
{
	return true;
}
