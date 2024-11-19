#pragma once
#include "Cardopoly/City/CityGridService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/UGridSubsystem.h"

namespace Pathfinding
{
	class AStar;
}

class PathfindingSystem : public IGameplaySystem
{
public:
	UGridSubsystem* _gridSubsystem;
	UCityGrid* _cityGrid;
	Pathfinding::AStar* _aStar;

	PathfindingSystem(
		flecs::world* world,
		UGridSubsystem* gridSubsystem,
		UCityGrid* cityGrid,
		Pathfinding::AStar* aStar
		)
		: IGameplaySystem(world),
		_gridSubsystem(gridSubsystem),
		_cityGrid(cityGrid),
		_aStar(aStar)
	{
		
	}
	
	virtual void Initialize() override;
};
