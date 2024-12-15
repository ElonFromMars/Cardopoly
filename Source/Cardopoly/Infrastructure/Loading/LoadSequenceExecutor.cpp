#include "LoadSequenceExecutor.h"

#include <FutureExtensions.h>

void LoadSequencePlayer::Execute(const std::shared_ptr<LoadSequence>& loadSequence)
{
	_loadSequence = loadSequence;

	if (_loadSequence->Steps.size() == 0)
	{
		return;
	}
	
	ExecuteStep(0);
}

void LoadSequencePlayer::ExecuteStep(int stepIndex)
{
	auto step = _loadSequence->Steps[stepIndex];
	SD::TExpectedFuture<void> stepResult = step->Execute();
	stepResult.Then([this, stepIndex](SD::TExpected<void> result)
	{
		if (result.IsError())
		{
			//TODO
		}
		if (stepIndex + 1 < _loadSequence->Steps.size())
		{
			ExecuteStep(stepIndex + 1);
		}
		else
		{
			//TODO
		}
		return SD::MakeReadyExpected();
	});
}
