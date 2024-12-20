#pragma once

#include <memory>

#include "IInstanceWrapper.h"
#include "InstanceOwnerWrapper.h"
#include "Cardopoly/Utils/TypeIdUtils.h"

class IServiceContainer
{
public:
	template <typename T>
	T Get()
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		void* systemPtr = Get(typeId);
		
		return static_cast<T>(systemPtr);
	}

	virtual void* Get(uintptr_t typeId) = 0;

	template <typename T>
	bool TryGet(T*& system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		void* systemPtr;
		bool isSuccess = TryGet(typeId, systemPtr);
		system = static_cast<T>(systemPtr);
		
		return isSuccess;
	}

	virtual bool TryGet(uintptr_t typeId, void*& system) = 0;

	template <typename T>
	void Set(T system)
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		Set(typeId, new InstanceOwnerWrapper<T>(system));
	}

	virtual void Set(uintptr_t typeId, IInstanceWrapper* system) = 0;

	template <typename T>
	void RemoveSystem()
	{
		uintptr_t typeId = unique_id<T>::get_ID();
		RemoveSystem(typeId);
	}

	virtual void RemoveSystem(uintptr_t typeId) = 0;

	virtual ~IServiceContainer() = default;
};
