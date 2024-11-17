#include "BuildingEntityFactory.h"

#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Economy/FIncomeComponent.hpp"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/ECS/Core/View/FCreateViewRequest.hpp"

flecs::entity BuildingEntityFactory::Create(const FIntVector cellPosition, const uint32 id) const
{
	return world->entity()
		.add<FBuildingTag>()
		.add<FCreateViewRequest>()
		.set<FIdComponent>({id})
		.set<FGridPositionComponent>({cellPosition})
		.set<FIncomeComponent>({10});
}
