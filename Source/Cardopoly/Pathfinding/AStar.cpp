#include "AStar.h"
#include <fstream>
#include <algorithm>

#include "Cardopoly/ECS/Core/Grid/Services/CityGridService.h"


using namespace std::placeholders;

namespace Pathfinding
{
	AStar::AStar(CityGridService* CityGrid) :
		_cityGrid(CityGrid),
		_weight(1),
		_dimensions(0, 0, 0),
		_startPos(0, 0, 0),
		_targetPos(0, 0, 0),
		_size(0),
		_nrOfDirections(4)
	{
		_directions = {
			{-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, -1, 0}
			/*,{-1, -1, 0}, {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}*/
		};
	}

	std::vector<FIntVector> AStar::FindPath(const FIntVector& startPos, const FIntVector& targetPos,
	                                        HeuristicFunction heuristicFunc, int weight)
	{
		constexpr int maxIterations = 1000;
		int iterations = 0;
		
		std::priority_queue<Node> empty{};
		std::swap(_openList, empty);
		
		_closedList.Empty();
		_cameFrom.Empty();
		
		_startPos = startPos;
		_targetPos = targetPos;
		_weight = weight;
		_heuristic = std::bind(heuristicFunc, _1, _2, _3);

		Node firstNode;
		firstNode.pos = startPos;
		firstNode.parent = _startPos;
		firstNode.f = _heuristic(_startPos, _targetPos, _weight);
		
		_cameFrom.Add(_startPos, firstNode);
		
		_openList.push(firstNode);

		uint fNew, gNew, hNew;
		FIntVector currentPos;

		while (!_openList.empty())
		{
			// Get the node with the least f value
			currentPos = _openList.top().pos;

			if (currentPos == _targetPos)
			{
				return BuildPath();
			}

			_openList.pop();
			_closedList.Add(currentPos) = true;

			// Check the neighbors of the current node
			for (uint i = 0; i < _nrOfDirections; ++i)
			{
				const auto neighborPos = currentPos + _directions[i];

				if (!IsValid(neighborPos) || IsBlocked(neighborPos) || _closedList.Contains(neighborPos))
				{
					continue;
				}
				gNew = _cameFrom[currentPos].g + 1;
				hNew = _heuristic(neighborPos, _targetPos, _weight);
				fNew = gNew + hNew;

				if (!_cameFrom.Contains(neighborPos) || fNew < _cameFrom[neighborPos].f)
				{
					_openList.push(Node(neighborPos, fNew));
					_cameFrom.Add(neighborPos, {neighborPos, currentPos, fNew, gNew, hNew});
				}
			}
			if(iterations > maxIterations)
			{
				return {};
			}
			iterations++;
		}
		
		return {};
	}

	std::vector<FIntVector> AStar::BuildPath()
	{
		std::vector<FIntVector> path;
		FIntVector currentPos = _targetPos;
		
		while (!(_cameFrom[currentPos].parent == currentPos))
		{
			path.push_back(currentPos);
			currentPos = _cameFrom[currentPos].parent;
		}

		std::reverse(path.begin(), path.end());

		return path;
	}

	void AStar::SetDiagonalMovement(bool enable)
	{
		_nrOfDirections = (enable) ? 8 : 4;
	}

	inline bool AStar::IsValid(const FIntVector& pos) const
	{
		return _cityGrid->IsValidPosition(pos);
	}

	bool AStar::IsBlocked(const FIntVector& pos) const
	{
		bool bContainsBuildingAtPosition = _cityGrid->ContainsBuildingAtPosition(pos);

		return bContainsBuildingAtPosition;
	}

	// Returns a 1D index based on a 2D coordinate using row-major layout
	int AStar::ConvertTo1D(const FIntVector& pos) const
	{
		return (pos.Y * _dimensions.X) + pos.X;
	}

	static FIntVector getDelta(const FIntVector& v1, const FIntVector& v2)
	{
		return FIntVector(FMath::Abs(v1.X - v2.X), FMath::Abs(v1.Y - v2.Y), 0);
	}

	uint Heuristic::Manhattan(const FIntVector& v1, const FIntVector& v2, int weight)
	{
		const auto delta = getDelta(v1, v2);
		return static_cast<uint>(weight * (delta.X + delta.Y));
	}

	uint Heuristic::Euclidean(const FIntVector& v1, const FIntVector& v2, int weight)
	{
		//const auto delta = getDelta(v1, v2);
		return (v1 -v2).Size();
	}
}
