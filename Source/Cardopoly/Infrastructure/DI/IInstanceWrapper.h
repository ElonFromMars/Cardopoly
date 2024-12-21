#pragma once

class IInstanceWrapper
{
public:
	virtual ~IInstanceWrapper() = default;

	virtual void* GetInstance() = 0;

	virtual void ReleaseInstance() = 0;

	virtual void BindLifetimeToContainer()
	{
		IsBindLifetime = true;
	}
	
protected:
	bool IsBindLifetime = false;
};
