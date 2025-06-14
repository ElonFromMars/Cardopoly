#pragma once

#include <iterator>

class RadiusIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = FIntVector;
	using difference_type = std::ptrdiff_t;
	using pointer = FIntVector*;
	using reference = FIntVector&;

	RadiusIterator(const FIntVector& center, int32 radius, bool isEnd = false)
		: _center(center), _radius(radius), _currentX(center.X - radius), _currentY(center.Y - radius)
	{
		if (isEnd)
		{
			_currentX = center.X + radius + 1;
			_currentY = center.Y + radius;
		}
		else
		{
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
	int32 _currentX;
	int32 _currentY;

	void MoveToNext()
	{
		_currentY++;
		if (_currentY > _center.Y + _radius)
		{
			_currentY = _center.Y - _radius;
			_currentX++;
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
	}

	bool IsCurrentCellValid() const
	{
		FIntVector currentCell(_currentX, _currentY, _center.Z);
		float distance = FVector::Dist(FVector(_center), FVector(currentCell));
		return distance <= _radius;
	}
};

class RadiusRange
{
public:
	RadiusRange(const FIntVector& center, int32 radius)
		: _center(center), _radius(radius)
	{
	}

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
