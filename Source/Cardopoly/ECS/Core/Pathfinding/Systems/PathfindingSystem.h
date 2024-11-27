#pragma once


#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/GridLayout.h"

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
		GridLayout* gridLayout,
		CityGridService* cityGrid,
		Pathfinding::AStar* aStar
		)
		: IGameplaySystem(world),
		_gridLayout(gridLayout),
		_cityGrid(cityGrid),
		_aStar(aStar)
	{
		
	}
	
	virtual void Initialize() override;

private:
	GridLayout* _gridLayout;
	CityGridService* _cityGrid;
	Pathfinding::AStar* _aStar;
};
