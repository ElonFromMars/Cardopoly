#pragma once

#include <queue>
#include <vector>
#include <functional>

class UCityGrid;

namespace Pathfinding
{
	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(const FIntVector&, const FIntVector&, int)>;

	struct Node
	{
		Node() : pos(0, 0, 0), parent(-1, -1, 0), f(0), g(0), h(0)
		{
		}

		Node(const FIntVector& pos, uint f) : pos(pos), parent(-1, 1, 0), f(f), g(0), h(0)
		{
		}

		Node(const FIntVector& pos, const FIntVector& parent, uint f, uint g, uint h) : pos(pos), parent(parent), f(f),
			g(g), h(h)
		{
		}

		FIntVector pos;
		FIntVector parent;
		uint f;
		uint g;
		uint h;
	};

	namespace Heuristic
	{
		uint Manhattan(const FIntVector& v1, const FIntVector& v2, int weight);
		uint Euclidean(const FIntVector& v1, const FIntVector& v2, int weight);
	}

	// Reverse std::priority_queue to get the smallest element on top

	inline bool operator<(const Node& a, const Node& b) { return a.f > b.f; }

	class AStar
	{
	public:
		AStar(UCityGrid* CityGrid);

		std::vector<FIntVector> FindPath(const FIntVector& startPos, const FIntVector& targetPos,
		                                 HeuristicFunction heuristicFunc, int weight = 1);
		void SetDiagonalMovement(bool enable);

	private:
		std::vector<FIntVector> BuildPath();
		bool IsValid(const FIntVector& pos) const;
		bool IsBlocked(const FIntVector& pos) const;
		int ConvertTo1D(const FIntVector& pos) const;

		int _weight;
		int _size;
		uint _nrOfDirections;
		FIntVector _dimensions;
		FIntVector _startPos;
		FIntVector _targetPos;
		UCityGrid* _cityGrid;
		
		std::priority_queue<Node> _openList;
		TMap<FIntVector, bool> _closedList;
		TMap<FIntVector, Node> _cameFrom;
		std::vector<FIntVector> _directions;
		HeuristicFunction _heuristic;
	};
}
