#include "PathfindingSystem.h"

#include "Cardopoly/ECS/Core/Grid/Components/FGridPositionComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Services/CityGridService.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FGridPathComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FSearchPathRequest.h"
#include "Cardopoly/Pathfinding/AStar.h"

void PathfindingSystem::Initialize()
{
	_world->system<FGridPositionComponent>("PathfindingSystem")
		.with<FPositionComponent>()
		.with<FSearchPathRequest>()
		.each([this](flecs::entity entity, FGridPositionComponent& gridPos) {

			int xOffset = FMath::RandRange(-5, 5);
			int yOffset = FMath::RandRange(-5, 5);
			
			FIntVector targetGridPos ={
				gridPos.Value.X + xOffset,
				gridPos.Value.Y + yOffset,
				0
			};
			if(_cityGrid->ContainsBuildingAtPosition(targetGridPos))
			{
				return;
			}
			std::vector<FIntVector> path = _aStar->FindPath(gridPos.Value, targetGridPos,
															Pathfinding::Heuristic::Euclidean);
			if(path.size() > 1)
			{
				entity.remove<FSearchPathRequest>();
				entity.set<FGridPathComponent>({
					path[0],
					0,
					path
				});
			}
		});
}
