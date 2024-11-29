#include "BuildingEntityFactory.h"

#include "Cardopoly/Configs/Buildings/GridObjectsDataProvider.h"
#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Economy/FIncomeComponent.hpp"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/ECS/Core/View/FCreateViewRequest.hpp"
#include "Cardopoly/ECS/Core/View/FLocalOffsetComponent.hpp"

flecs::entity BuildingEntityFactory::Create(const FIntVector cellPosition, const uint32 id) const
{
	FVector localPosition = _gridObjectsDataProvider->GetCenterOffset(id);
	
	return world->entity()
		.add<FBuildingTag>()
		.add<FCreateViewRequest>()
		.set<FIdComponent>({id})
		.set<FLocalOffsetComponent>({localPosition})
		.set<FGridPositionComponent>({cellPosition})
		.set<FIncomeComponent>({10});
}
