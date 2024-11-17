#pragma once

#include "Cardopoly/ECS/Infrastructure/Factories/EntityFactory.h"

class BuildingEntityFactory : public EntityFactory
{
public:
	BuildingEntityFactory(flecs::world* world) : EntityFactory(world) {}
	
	flecs::entity Create(const FIntVector cellPosition, const uint32 id) const;
};
