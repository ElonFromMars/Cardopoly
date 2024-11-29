#pragma once

#include "Cardopoly/ECS/Infrastructure/Factories/EntityFactory.h"

class GridObjectsDataProvider;

class BuildingEntityFactory : public EntityFactory
{
public:
	BuildingEntityFactory(
		flecs::world* world,
		GridObjectsDataProvider* gridObjectsDataProvider	
		)
		: EntityFactory(world),
		_gridObjectsDataProvider(gridObjectsDataProvider)
	{}
	
	flecs::entity Create(const FIntVector cellPosition, const uint32 id) const;
	GridObjectsDataProvider* _gridObjectsDataProvider;
};
