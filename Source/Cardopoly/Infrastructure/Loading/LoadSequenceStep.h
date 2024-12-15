#pragma once

#include "ExpectedFuture.h"

class LoadSequenceStep
{
public:
	virtual SD::TExpectedFuture<void> Execute();

	virtual ~LoadSequenceStep() = default;
};
