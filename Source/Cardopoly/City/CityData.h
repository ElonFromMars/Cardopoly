#pragma once

#include "flecs.h"

class CityData
{
public:
	CityData()
	{
		_world = new flecs::world();
	}

	virtual ~CityData()
	{
		delete _world;
	}

	flecs::world* GetWorld() const
	{
		return _world;
	}
	
protected:
	flecs::world* _world;
};
