#pragma once

#include <memory>

#include "LoadSequence.h"

class LoadSequencePlayer
{
public:
	void Execute(const std::shared_ptr<LoadSequence>& loadSequence);
	void ExecuteStep(int stepIndex);
	
private:
	std::shared_ptr<LoadSequence> _loadSequence;
};
