#pragma once

#include <unordered_map>
#include <Cardopoly/Utils/TypeIdUtils.h>

class ServiceContainer
{
public:
	template <typename T>
	std::shared_ptr<T> Get()
	{
		uintptr_t typeId = unique_id<T>::get_ID();

		auto it = systemByType.find(typeId);
		if (it != systemByType.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}

		throw std::runtime_error("Type not found");
	}

	template <typename T>
	bool TryGet(std::shared_ptr<T>& system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		auto it = systemByType.find(typeId);
		if (it != systemByType.end())
		{
			system = std::static_pointer_cast<T>(it->second);
			return true;
		}
		return false;
	}

	template <typename T>
	void Set(std::shared_ptr<T> system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		systemByType[typeId] = system;
	}

	template <typename T>
	void RemoveSystem()
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		systemByType.erase(typeId);
	}
	
private:
	std::unordered_map<uintptr_t, std::shared_ptr<void>> systemByType;
};
