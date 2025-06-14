#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include <unordered_map>
#include <vector>

// Hash function for FIntVector to use in std::unordered_map
struct FIntVectorHash
{
	std::size_t operator()(const FIntVector& Vector) const
	{
		return std::hash<int32>()(Vector.X) ^ 
		       std::hash<int32>()(Vector.Y) ^ 
		       std::hash<int32>()(Vector.Z);
	}
};

// Equality comparison for FIntVector to use in std::unordered_map
struct FIntVectorEqual
{
	bool operator()(const FIntVector& Left, const FIntVector& Right) const
	{
		return Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z;
	}
};

class CitizenGridService
{
public:
	CitizenGridService();

	bool ContainsEntitiesAtPosition(const FIntVector Position) const;

	void PutEntityAtPosition(const FIntVector Position, const flecs::entity entity);

	// Get all entities at a specific position
	const std::vector<flecs::entity>* GetEntitiesAtPosition(const FIntVector Position) const;

	// Get count of entities at a specific position
	int32 GetEntityCountAtPosition(const FIntVector Position) const;

	// Remove entity from position
	void RemoveEntityFromPosition(const FIntVector Position, const flecs::entity entity);

	// Clear all entities at position
	void ClearEntitiesAtPosition(const FIntVector Position);

	bool IsValidPosition(const FIntVector& Pos);

private:
	std::unordered_map<FIntVector, std::vector<flecs::entity>, FIntVectorHash, FIntVectorEqual> _entitiesByCellPosition;
};
