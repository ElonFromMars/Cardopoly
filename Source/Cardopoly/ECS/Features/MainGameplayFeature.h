﻿#pragma once

#include "Cardopoly/ECS/Core/Citizens/Systems/CitizensInitializeSystem.h"
#include "Cardopoly/ECS/Core/Common/CleanupSystem.hpp"
#include "Cardopoly/ECS/Core/Debug/Systems/DrawDebugViewSystem.h"
#include "Cardopoly/ECS/Core/GameplayFlow/Players/LocalPlayerFlowSystem.h"
#include "Cardopoly/ECS/Core/GameplayFlow/Players/AI/AIOpponentPlayerFlowSystem.h"
#include "Cardopoly/ECS/Core/Movement/Systems/MovementSystem.h"
#include "Cardopoly/ECS/Core/Pathfinding/Systems/PathfindingSystem.h"
#include "Cardopoly/ECS/Core/View/FCreateViewRequest.hpp"
#include "Cardopoly/ECS/Infrastructure/Features/GameplayFeature.h"

class OverlayPositionSystem;
class IncomeOverlaySystem;
class TurnSystem;
class HandUISystem;
class InitializeGridPositionSystem;
class CreateViewSystem;
class EconomySystem;
class PlayerInitializeSystem;
class HUDViewSystem;

class MainGameplayFeature : public GameplayFeature
{
public:
	MainGameplayFeature(std::unique_ptr<ISystemFactory> systemFactory, flecs::world* world)
		: GameplayFeature(std::move(systemFactory)), _world(world)
	{
	}
	
	virtual void AddSystems() override
	{
		//Logic initialization
		AddSystem<CitizensInitializeSystem>();
		AddSystem<PlayerInitializeSystem>();
		AddSystem<InitializeGridPositionSystem>();

		//Logic flow
		AddSystem<TurnSystem>();
		AddSystem<LocalPlayerFlowSystem>();
		AddSystem<AIOpponentPlayerFlowSystem>();

		AddSystem<EconomySystem>();

		//Logic request handlers
		AddSystem<PathfindingSystem>();
		AddSystem<MovementSystem>();
		
		//View
		AddSystem<CreateViewSystem>();

		//Debug
		AddSystem<DrawDebugViewSystem>();

		//UI
		AddSystem<IncomeOverlaySystem>();
		AddSystem<OverlayPositionSystem>();
		
		AddSystem<HUDViewSystem>();
		AddSystem<HandUISystem>();
		AddSystem(new CleanupSystem<FCreateViewRequest>(_world));
	}
	
private:
	flecs::world* _world;
};
