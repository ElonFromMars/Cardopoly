#include "BuildingEntityFactory.h"

#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Economy/FIncomeComponent.hpp"

flecs::entity BuildingEntityFactory::Create() const
{
	return world->entity()
		.add<FBuildingTag>()
		.set<FIncomeComponent>({10});
}
