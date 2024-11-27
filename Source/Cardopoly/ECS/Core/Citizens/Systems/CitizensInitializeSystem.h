#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "Cardopoly/Grid/GridLayout.h"

class CitizensInitializeSystem : public IGameplaySystem
{
public:
	CitizensInitializeSystem(
		flecs::world* flecsWorld,
		GridLayout* gridLayout
		)
		: IGameplaySystem(flecsWorld),
		_gridLayout(gridLayout)
	{
	}

	virtual void Initialize() override;

private:
	GridLayout* _gridLayout;
};
