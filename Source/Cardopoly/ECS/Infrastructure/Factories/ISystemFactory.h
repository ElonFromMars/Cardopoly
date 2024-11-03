#pragma once
#include <Cardopoly/Utils/TypeIdUtils.h>

class IGameplaySystem;

class ISystemFactory
{
public:
	virtual ~ISystemFactory() = default;

	template <typename T>
	IGameplaySystem* Create()
	{
		uintptr_t TypeId = unique_id<T>::get_ID();
		return Create(TypeId);
	}
	
	virtual IGameplaySystem* Create(uintptr_t typeId) = 0;
};
