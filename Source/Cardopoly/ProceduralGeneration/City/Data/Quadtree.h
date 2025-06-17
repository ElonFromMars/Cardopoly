#pragma once

#include <vector>
#include "CoreMinimal.h"

struct FRect
{
	FIntVector Position;
	FIntVector Size;
};

class Quadtree
{
public:
	Quadtree(const FRect& bounds, int maxObjects = 10, int maxLevels = 4, int level = 0);

	void Clear();
	void Insert(const FRect& rect);
	std::vector<FRect> Retrieve(const FRect& rect) const;

private:
	void Split();
	int GetIndex(const FRect& rect) const;
	
	int _maxObjects;
	int _maxLevels;
	int _level;
	FRect _bounds;
	std::vector<FRect> _objects;
	std::vector<Quadtree*> _nodes;
};