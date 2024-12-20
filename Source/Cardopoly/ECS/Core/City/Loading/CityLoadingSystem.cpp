#include "CityLoadingSystem.h"

#include "Cardopoly/City/CityData.h"
#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FMaxSpeedComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FGridPathComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FSearchPathRequest.h"
#include "Cardopoly/Grid/GridLayout.h"

void CityLoadingSystem::Initialize()
{
	flecs::world* world = _cityData->GetWorld();

	auto q = world->
		query_builder<FBuildingTag>()
		.with<FIdComponent>()
		.with<FGridPositionComponent>()
		.build();
 
	q.each([this](const FIdComponent& id, const FGridPositionComponent& position)
	{
		_buildingService->CreateBuilding(position.Value, id.Value);
	});
}

