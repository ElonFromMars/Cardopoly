﻿#include "MovementSystem.h"

#include "Cardopoly/ECS/Core/Grid/Components/FGridPositionComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Services/CitizenGridService.h"
#include "Cardopoly/ECS/Core/Movement/Components/FMaxSpeedComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FGridPathComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FSearchPathRequest.h"
#include "Cardopoly/Grid/GridLayout.h"

void MovementSystem::Initialize()
{
	_world->system<FPositionComponent, FGridPositionComponent, FGridPathComponent, FMaxSpeedComponent>("MoveSystem")
		.immediate()
		.each([this](flecs::entity entity, FPositionComponent& pos, FGridPositionComponent& gridPos, FGridPathComponent& gridPath, FMaxSpeedComponent& speed) {

				auto deltaTime = _world->delta_time();
				FVector targetWorldPos = _gridLayout->GetCellCenterWorldPosition(gridPath.CurrentGridTarget);
				FVector difference = (targetWorldPos - pos.Value).GetSafeNormal() * speed.Value * deltaTime;
				FVector newWorldPos = pos.Value + difference;
				pos.Value = newWorldPos;

				auto oldGridPos = gridPos.Value;
				auto newGridPos = _gridLayout->WorldPositionToGrid(newWorldPos);
				gridPos.Value = newGridPos;
				if(oldGridPos != newGridPos)
				{
					_citizenGridService->RemoveEntityFromPosition(oldGridPos, entity);
					_citizenGridService->PutEntityAtPosition(newGridPos, entity);
				}

				auto size = gridPath.Path.size();
				if((newWorldPos -targetWorldPos).Size() < 20.0f)
				{
					if(gridPath.CurrentTargetIndex >= size - 1)
					{
						entity.remove<FGridPathComponent>();
						entity.add<FSearchPathRequest>();
					}
					else
					{
						gridPath.CurrentTargetIndex++;
						gridPath.CurrentGridTarget = gridPath.Path[gridPath.CurrentTargetIndex];
					}
				}
		});
}
