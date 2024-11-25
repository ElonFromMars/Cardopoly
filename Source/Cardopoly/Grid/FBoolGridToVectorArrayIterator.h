#pragma once

class FBoolGridToVectorArrayIterator
{
public:
	explicit FBoolGridToVectorArrayIterator(const TArray<bool>& inArray, int32 rowLength)
		: _array(inArray), _rowLength(rowLength)
	{}
	
	class Iterator
	{
	public:
		Iterator(const TArray<bool>& inArray, const int32 rowLength = 0, int32 index = 0)
			: _array(inArray), _rowLength(rowLength), _index(index)
		{
			MoveToValidPosition();
		}

		const FIntVector& operator*() const
		{
			return FIntVector(_index % _rowLength, _index / _rowLength, 0);
		}
		
		Iterator& operator++()
		{
			++_index;
			MoveToValidPosition();
			return *this;
		}
		
		bool operator==(const Iterator& other) const
		{
			return &_array == &other._array && _index == other._index;
		}
		
		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}

	private:
		void MoveToValidPosition()
		{
			while (_index < _array.Num() && _array[_index] == false)
			{
				++_index;
			}
		}
		
		const TArray<bool>& _array;

		const int32 _rowLength;
		int32 _index;
	};

	Iterator begin() const
	{
		return Iterator(_array, _rowLength);
	}
	
	Iterator end() const
	{
		return Iterator(_array, _rowLength, _array.Num());
	}

private:
	const TArray<bool>& _array;
	int32 _rowLength;
};