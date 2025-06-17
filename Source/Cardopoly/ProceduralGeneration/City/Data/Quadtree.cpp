#include "Quadtree.h"

Quadtree::Quadtree(const FRect& bounds, int maxObjects, int maxLevels, int level)
	: _maxObjects(maxObjects), _maxLevels(maxLevels), _level(level), _bounds(bounds)
{
	_nodes.resize(4, nullptr);
}

void Quadtree::Clear()
{
	_objects.clear();

	for (Quadtree*& node : _nodes)
	{
		if (node)
		{
			node->Clear();
			delete node;
			node = nullptr;
		}
	}
}

void Quadtree::Split()
{
	int subWidth = _bounds.Size.X / 2;
	int subHeight = _bounds.Size.Y / 2;
	int x = _bounds.Position.X;
	int y = _bounds.Position.Y;

	int nextLevel = _level + 1;

	// Top-right NE
	_nodes[0] = new Quadtree({{x + subWidth, y + subHeight, 0}, {subWidth, subHeight, 0}}, _maxObjects, _maxLevels,
	                         nextLevel);

	// Top-left NW
	_nodes[1] = new Quadtree({{x, y + subHeight, 0}, {subWidth, subHeight, 0}}, _maxObjects, _maxLevels, nextLevel);

	// Bottom-left SW
	_nodes[2] = new Quadtree({{x, y, 0}, {subWidth, subHeight, 0}}, _maxObjects, _maxLevels, nextLevel);

	// Bottom-right SE
	_nodes[3] = new Quadtree({{x + subWidth, y, 0}, {subWidth, subHeight, 0}}, _maxObjects, _maxLevels, nextLevel);
}

int Quadtree::GetIndex(const FRect& rect) const
{
	int index = -1;

	int verticalMidpoint = _bounds.Position.X + (_bounds.Size.X / 2);
	int horizontalMidpoint = _bounds.Position.Y + (_bounds.Size.Y / 2);

	bool topQuadrant = (rect.Position.Y > horizontalMidpoint);
	bool bottomQuadrant = (rect.Position.Y + rect.Size.Y) < horizontalMidpoint;

	if ((rect.Position.X + rect.Size.X) < verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 1; // Top-left
		}
		else if (bottomQuadrant)
		{
			index = 2; // Bottom-left
		}
	}
	else if (rect.Position.X > verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 0; // Top-right
		}
		else if (bottomQuadrant)
		{
			index = 3; // Bottom-right
		}
	}

	return index;
}

void Quadtree::Insert(const FRect& rect)
{
	if (_nodes[0])
	{
		int index = GetIndex(rect);
		if (index != -1)
		{
			_nodes[index]->Insert(rect);
			return;
		}
	}

	_objects.push_back(rect);

	if (_objects.size() > _maxObjects && _level < _maxLevels)
	{
		if (!_nodes[0])
		{
			Split();
		}

		auto it = _objects.begin();
		while (it != _objects.end())
		{
			int index = GetIndex(*it);
			if (index != -1)
			{
				_nodes[index]->Insert(*it);
				it = _objects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

std::vector<FRect> Quadtree::Retrieve(const FRect& rect) const
{
	std::vector<FRect> returnObjects = _objects;
	int index = GetIndex(rect);

	if (_nodes[0])
	{
		if (index != -1)
		{
			auto childObjects = _nodes[index]->Retrieve(rect);
			returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());
		}
		else
		{
			for (const Quadtree* node : _nodes)
			{
				auto childObjects = node->Retrieve(rect);
				returnObjects.insert(returnObjects.end(), childObjects.begin(), childObjects.end());
			}
		}
	}

	return returnObjects;
}
