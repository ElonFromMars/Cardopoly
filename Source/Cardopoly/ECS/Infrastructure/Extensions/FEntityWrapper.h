#pragma once

#include "flecs.h"
#include "FEntityWrapper.generated.h"

USTRUCT()
struct FEntityWrapper
{
	GENERATED_BODY()
	
	FEntityWrapper() = default;

	FEntityWrapper(flecs::entity InEntity)
		: Entity(InEntity)
	{
	}

	uint32 GetTypeHash() const
	{
		return ::GetTypeHash(Entity.id());
	}

	bool operator==(const FEntityWrapper& Other) const
	{
		return Entity.id() == Other.Entity.id();
	}

	flecs::entity GetEntity() const
	{
		return Entity;
	}

private:
	flecs::entity Entity;
};

inline uint32 GetTypeHash(const FEntityWrapper& Wrapper)
{
	return Wrapper.GetTypeHash();
}