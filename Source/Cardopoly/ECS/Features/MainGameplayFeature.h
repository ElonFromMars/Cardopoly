#pragma once

#include "Cardopoly/ECS/Core/Citizens/Systems/CitizensInitializeSystem.h"
#include "Cardopoly/ECS/Core/Debug/Systems/DrawDebugViewSystem.h"
#include "Cardopoly/ECS/Core/Movement/Systems/MovementSystem.h"
#include "Cardopoly/ECS/Core/Pathfinding/Systems/PathfindingSystem.h"
#include "Cardopoly/ECS/Infrastructure/Features/GameplayFeature.h"

class EconomicsSystem;
class PlayerInitializeSystem;
class HUDViewSystem;

class MainGameplayFeature : public GameplayFeature
{
public:
	MainGameplayFeature(std::unique_ptr<ISystemFactory> systemFactory)
		: GameplayFeature(std::move(systemFactory))
	{
	}
	
	virtual void AddSystems() override
	{
		AddSystem<CitizensInitializeSystem>();
		AddSystem<PlayerInitializeSystem>();
		AddSystem<PathfindingSystem>();
		AddSystem<MovementSystem>();
		AddSystem<DrawDebugViewSystem>();
		AddSystem<EconomicsSystem>();
		AddSystem<HUDViewSystem>();
	}
};
