#pragma once

#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class TestStep : LoadSequenceStep
{
public:
	virtual SD::TExpectedFuture<void> Execute() override
	{
		UE_LOG(LogTemp, Error, TEXT("TestStep executed"));
		
		return SD::MakeReadyFuture();
	}
};
