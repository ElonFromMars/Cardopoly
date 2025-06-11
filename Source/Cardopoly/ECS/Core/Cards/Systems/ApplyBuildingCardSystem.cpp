#include "ApplyBuildingCardSystem.h"

#include "Cardopoly/ECS/Core/Buildings/FBuildingTag.h"
#include "Cardopoly/ECS/Core/Cards/Components/ApplyCardRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/BuildingCardComponent.hpp"
#include "Cardopoly/ECS/Core/Economy/FIncomeComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Components/FGridPositionComponent.hpp"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/ECS/Core/View/FCreateViewRequest.hpp"
#include "Cardopoly/ECS/Core/View/FLocalOffsetComponent.hpp"

void ApplyBuildingCardSystem::Initialize()
{
	_world->system<ApplyCardRequest, BuildingCardComponent, PlayerIndexComponent>("ApplyBuildingCardSystem")
		.immediate()
		.write<BuildingCardComponent>()
		.write<FBuildingTag>()
		.write<FCreateViewRequest>()
		.write<FIdComponent>()
		.write<FLocalOffsetComponent>()
		.write<FGridPositionComponent>()
		.write<FIncomeComponent>()
		.write<PlayerIndexComponent>()
		.each([this](flecs::entity entity, ApplyCardRequest& request, BuildingCardComponent& buildingCardComponent, PlayerIndexComponent& playerIndexComponent)
		{
			uint32 buildingId = static_cast<uint32>(buildingCardComponent.BuildingId);
			flecs::entity building;
			if (_buildingService->TryCreateBuilding(request.CellPosition, buildingId, building))
			{
				building.set<PlayerIndexComponent>({playerIndexComponent.Value});
				entity.destruct();
			}
		});
}
