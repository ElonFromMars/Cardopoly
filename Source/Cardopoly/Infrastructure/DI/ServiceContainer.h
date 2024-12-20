#pragma once

#include <unordered_map>
#include "Cardopoly/Utils/TypeIdUtils.h"
#include "IServiceContainer.h"

class ServiceContainer : public IServiceContainer
{
public:
	virtual void* Get(uintptr_t typeId) override
	{
		auto it = _systemByType.find(typeId);
		if (it != _systemByType.end())
		{
			return it->second;
		}

		throw std::runtime_error("Type not found");
	}
	
	virtual bool TryGet(uintptr_t typeId, void*& system) override
	{
		auto it = _systemByType.find(typeId);
		if (it != _systemByType.end())
		{
			system = it->second;
			return true;
		}
		return false;
	}

	virtual void Set(uintptr_t typeId, IInstanceWrapper* system) override
	{
		_systemByType[typeId] = system;
	}
	
	virtual void RemoveSystem(uintptr_t typeId) override
	{
		_systemByType.erase(typeId);
	}
	
private:
	std::unordered_map<uintptr_t, IInstanceWrapper*> _systemByType;
};
