#include "BuildingEntityFactory.h"

#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"

flecs::entity BuildingEntityFactory::Create()
{
	
	return world->entity()
		.add<FBuildingTag>()
		.add<PositionComponent>();
}
