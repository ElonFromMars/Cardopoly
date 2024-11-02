#pragma once

#include <vector>
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class GameplayFeature
{
private:
	std::vector<IGameplaySystem*> _systems;

public:
	virtual ~GameplayFeature() = default;

	const std::vector<IGameplaySystem*>& GetSystems()
	{
		_systems.clear();
		AddSystems();
		
		return _systems;
	}
	
	virtual void AddSystems() = 0;
	
protected:
	template<typename TSystem>
	void AddSystem()
	{
		_systems.push_back(new TSystem());
	}
};
