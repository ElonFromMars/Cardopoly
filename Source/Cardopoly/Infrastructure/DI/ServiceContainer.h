#pragma once

#include <unordered_map>
#include "Cardopoly/Utils/TypeIdUtils.h"
#include "IServiceContainer.h"

class ServiceContainer : public IServiceContainer
{
public:
	template <typename T>
	std::shared_ptr<T> Get()
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		void* systemPtr = Get(typeId);
		
		return std::static_pointer_cast<T>(systemPtr);
	}
	
	virtual void* Get(uintptr_t typeId) override
	{
		auto it = _systemByType.find(typeId);
		if (it != _systemByType.end())
		{
			return it->second;
		}

		throw std::runtime_error("Type not found");
	}

	template <typename T>
	bool TryGet(T*& system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		void* systemPtr;
		bool isSuccess = TryGet(typeId, systemPtr);
		system = std::static_pointer_cast<T>(systemPtr);
		
		return isSuccess;
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

	template <typename T>
	void Set(std::shared_ptr<T> system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		Set(typeId, system);
	}

	virtual void Set(uintptr_t typeId, void* system) override
	{
		_systemByType[typeId] = system;
	}
	
	template <typename T>
	void RemoveSystem()
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		RemoveSystem(typeId);
	}
	
	virtual void RemoveSystem(uintptr_t typeId) override
	{
		_systemByType.erase(typeId);
	}
	
private:
	std::unordered_map<uintptr_t, void*> _systemByType;
};
