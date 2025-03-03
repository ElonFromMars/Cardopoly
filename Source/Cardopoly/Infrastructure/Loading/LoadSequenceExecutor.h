#pragma once

#include <memory>

#include "LoadSequence.h"

class LoadSequencePlayer
{
public:
	UE5Coro::TCoroutine<> Execute(const std::shared_ptr<LoadSequence>& loadSequence);
	void ExecuteStep(int stepIndex);
	
private:
	std::shared_ptr<LoadSequence> _loadSequence;
};
