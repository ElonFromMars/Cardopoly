#pragma once

#include <vector>
#include <functional>

class Ticker
{
public:
	using Tickable = std::function<void(float)>;

	void AddTickable(Tickable tickable)
	{
		_tickables.push_back(tickable);
	}

	void Update(float deltaTime)
	{
		for (auto& tickable : _tickables)
		{
			tickable(deltaTime);
		}
	}

private:
	std::vector<Tickable> _tickables;
};
