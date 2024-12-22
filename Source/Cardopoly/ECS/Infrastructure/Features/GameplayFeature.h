#pragma once

#include <memory>
#include <vector>

#include "Cardopoly/ECS/Infrastructure/Factories/ISystemFactory.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class GameplayFeature
{
public:
	GameplayFeature(std::unique_ptr<ISystemFactory> systemFactory)
		: _systemFactory(std::move(systemFactory))
	{
		
	}

	virtual void Initialize()
	{
		for (auto system : GetSystems())
		{
			system->Initialize();
		}
	}
	
	virtual ~GameplayFeature()
	{
		for (auto system : _systems)
		{
			delete system;
		}
	}

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
		auto typeId = unique_id<TSystem>::get_ID();
		_systems.push_back(_systemFactory->Create(typeId));
	}

private:
	std::vector<IGameplaySystem*> _systems;
	std::unique_ptr<ISystemFactory> _systemFactory;
};
