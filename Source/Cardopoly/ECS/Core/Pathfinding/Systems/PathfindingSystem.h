#pragma once


#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/UGridSubsystem.h"

class CityGridService;

namespace Pathfinding
{
	class AStar;
}

class PathfindingSystem : public IGameplaySystem
{
public:
	PathfindingSystem(
		flecs::world* world,
		UGridSubsystem* gridSubsystem,
		CityGridService* cityGrid,
		Pathfinding::AStar* aStar
		)
		: IGameplaySystem(world),
		_gridSubsystem(gridSubsystem),
		_cityGrid(cityGrid),
		_aStar(aStar)
	{
		
	}
	
	virtual void Initialize() override;

private:
	UGridSubsystem* _gridSubsystem;
	CityGridService* _cityGrid;
	Pathfinding::AStar* _aStar;
};
