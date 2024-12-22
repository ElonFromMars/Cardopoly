#pragma once

#include <memory>
#include "IInstanceWrapper.h"

template<typename T>
class InstanceOwnerWrapper : public IInstanceWrapper
{
public:
	InstanceOwnerWrapper(T* instance)
		: _instance(instance)
	{
	}

	virtual void* GetInstance() override
	{
		return _instance;
	}

	virtual void ReleaseInstance() override
	{
		delete _instance;
	}

	virtual ~InstanceOwnerWrapper() override
	{
		if (IsBindLifetime)
		{
			delete _instance;	
		}
	}
	
private:
	T* _instance;
};
