#include "CityLoadingSystem.h"

#include "Cardopoly/City/CityData.h"
#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "flecs.h"
#include "Cardopoly/ECS/Core/Grid/Components/FGridPositionComponent.hpp"

void CityLoadingSystem::Initialize()
{
	flecs::world* world = _cityData->GetWorld();

	auto q = world->
		query_builder<FIdComponent, FGridPositionComponent, FBuildingTag>()
		.build();

	q.each([this](const FIdComponent& id, const FGridPositionComponent& position, const FBuildingTag& tag)
	{
		_buildingService->CreateBuilding(position.Value, id.Value);
	});
}

