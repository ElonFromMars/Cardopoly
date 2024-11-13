#pragma once

#include "Cardopoly/ECS/Infrastructure/Factories/EntityFactory.h"

class BuildingEntityFactory : public EntityFactory
{
public:
	flecs::entity Create();
};
