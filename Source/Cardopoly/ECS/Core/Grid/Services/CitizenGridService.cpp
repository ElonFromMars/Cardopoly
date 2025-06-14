#include "CitizenGridService.h"
#include <algorithm>

CitizenGridService::CitizenGridService()
{

}

bool CitizenGridService::ContainsEntitiesAtPosition(const FIntVector Position) const
{
	auto it = _entitiesByCellPosition.find(Position);
	return it != _entitiesByCellPosition.end() && !it->second.empty();
}

void CitizenGridService::PutEntityAtPosition(const FIntVector Position, const flecs::entity entity)
{
	_entitiesByCellPosition[Position].push_back(entity);
}

const std::vector<flecs::entity>* CitizenGridService::GetEntitiesAtPosition(const FIntVector Position) const
{
	auto it = _entitiesByCellPosition.find(Position);
	if (it != _entitiesByCellPosition.end())
	{
		return &it->second;
	}
	return nullptr;
}

int32 CitizenGridService::GetEntityCountAtPosition(const FIntVector Position) const
{
	auto it = _entitiesByCellPosition.find(Position);
	if (it != _entitiesByCellPosition.end())
	{
		return static_cast<int32>(it->second.size());
	}
	return 0;
}

void CitizenGridService::RemoveEntityFromPosition(const FIntVector Position, const flecs::entity entity)
{
	auto it = _entitiesByCellPosition.find(Position);
	if (it != _entitiesByCellPosition.end())
	{
		auto& entities = it->second;
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());

		if (entities.empty())
		{
			_entitiesByCellPosition.erase(it);
		}
	}
}

void CitizenGridService::ClearEntitiesAtPosition(const FIntVector Position)
{
	_entitiesByCellPosition.erase(Position);
}

bool CitizenGridService::IsValidPosition(const FIntVector& Pos)
{
	return true;
}
