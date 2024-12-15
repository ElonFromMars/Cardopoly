#pragma once

#include <vector>
#include "LoadSequenceStep.h"

class LoadSequence
{
	
public:
	template<typename TStep>
	LoadSequence& Sequential()
	{
		static_assert(std::is_base_of_v<LoadSequenceStep, TStep>, "TStep must inherit from LoadSequenceStep");
		
		LoadSequenceStep* step = reinterpret_cast<LoadSequenceStep*>(new TStep());
		Steps.push_back(step);
		return *this;
	}

	FORCEINLINE void End()
	{
		
	}
	
private:
	~LoadSequence()
	{
		for (auto step : Steps)
		{
			delete step;
		}
		Steps.clear();
	}

public:
	std::vector<LoadSequenceStep*> Steps;
};
