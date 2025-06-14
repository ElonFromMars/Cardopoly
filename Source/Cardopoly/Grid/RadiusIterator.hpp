#pragma once

#include <iterator>
#include "Math/IntVector.h"
#include "Math/Vector.h"

class RadiusIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = FIntVector;
	using difference_type = std::ptrdiff_t;
	using pointer = FIntVector*;
	using reference = FIntVector&;

	RadiusIterator(const FIntVector& center, int32 radius, bool isEnd = false)
		: _center(center), _radius(radius), _radiusSquared(radius * radius)
	{
		if (isEnd)
		{
			_currentX = _center.X + _radius + 1; // sentinel value
			_currentY = _center.Y - _radius;
		}
		else
		{
			_currentX = _center.X - _radius;
			_currentY = _center.Y - _radius;
			FindNextValidCell();
		}
	}

	FIntVector operator*() const
	{
		return FIntVector(_currentX, _currentY, _center.Z);
	}

	RadiusIterator& operator++()
	{
		MoveToNext();
		FindNextValidCell();
		return *this;
	}

	RadiusIterator operator++(int)
	{
		RadiusIterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const RadiusIterator& other) const
	{
		return _currentX == other._currentX && _currentY == other._currentY;
	}

	bool operator!=(const RadiusIterator& other) const
	{
		return !(*this == other);
	}

private:
	FIntVector _center;
	int32 _radius;
	int32 _radiusSquared;
	int32 _currentX;
	int32 _currentY;

	void MoveToNext()
	{
		++_currentY;
		if (_currentY > _center.Y + _radius)
		{
			_currentY = _center.Y - _radius;
			++_currentX;
		}
	}

	void FindNextValidCell()
	{
		while (_currentX <= _center.X + _radius)
		{
			if (IsCurrentCellValid())
				return;
			MoveToNext();
		}

		// Mark as end
		_currentX = _center.X + _radius + 1;
		_currentY = _center.Y - _radius;
	}

	bool IsCurrentCellValid() const
	{
		int32 dx = _currentX - _center.X;
		int32 dy = _currentY - _center.Y;
		return dx * dx + dy * dy <= _radiusSquared;
	}
};

class RadiusRange
{
public:
	RadiusRange(const FIntVector& center, int32 radius)
		: _center(center), _radius(radius) {}

	RadiusIterator begin() const
	{
		return RadiusIterator(_center, _radius);
	}

	RadiusIterator end() const
	{
		return RadiusIterator(_center, _radius, true);
	}

private:
	FIntVector _center;
	int32 _radius;
};

inline RadiusRange GetCellsInRadius(const FIntVector& centerPosition, int32 radius)
{
	return RadiusRange(centerPosition, radius);
}
