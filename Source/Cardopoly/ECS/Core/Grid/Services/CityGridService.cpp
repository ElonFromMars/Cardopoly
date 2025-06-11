#include "CityGridService.h"

#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"

CityGridService::CityGridService(IGridObjectsDataProvider* gridObjectsDataProvider)
	: _gridObjectsDataProvider(gridObjectsDataProvider)
{
	
}

bool CityGridService::ContainsBuildingAtPosition(const FIntVector Position) const
{
	return _entityByCellPosition.Contains(Position);
}

void CityGridService::PutEntityAtPosition(const FIntVector Position, const flecs::entity entity)
{
	if (entity.has<FIdComponent>())
	{
		uint32 id = entity.get<FIdComponent>()->Value;
		PutEntityAtPosition(Position, entity, id);
	}
}

void CityGridService::PutEntityAtPosition(const FIntVector Position, const flecs::entity entity, uint32 id)
{
	const TArray<FIntVector>& localPositions = _gridObjectsDataProvider->GetGridLocalPositions(id);
	for (const FIntVector localPosition : localPositions)
	{
		const FIntVector absolutePosition = Position + localPosition;
		_entityByCellPosition.Add(absolutePosition, entity);
	}
}

bool CityGridService::GetBuildingAtPosition(const FIntVector Position, flecs::entity& entity)
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
