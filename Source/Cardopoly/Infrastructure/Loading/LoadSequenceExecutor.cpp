#include "LoadSequenceExecutor.h"

#include <FutureExtensions.h>

UE5Coro::TCoroutine<> LoadSequencePlayer::Execute(const std::shared_ptr<LoadSequence>& loadSequence)
{
	_loadSequence = loadSequence;

	if (_loadSequence->Steps.size() == 0)
	{
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
	
	ExecuteStep(0);

	return UE5Coro::TCoroutine<>::CompletedCoroutine;
}

void LoadSequencePlayer::ExecuteStep(int stepIndex)
{
	auto step = _loadSequence->Steps[stepIndex];
	UE5Coro::TCoroutine<> stepResult = step->Execute();
	if (stepResult.IsDone())
	{
		if (stepIndex + 1 < _loadSequence->Steps.size())
		{
			ExecuteStep(stepIndex + 1);
		}
	}
	else
	{
		stepResult.ContinueWith([this, stepIndex]()
		{
			if (stepIndex + 1 < _loadSequence->Steps.size())
			{
				ExecuteStep(stepIndex + 1);
			}
			else
			{
				//TODO
			}
		});
	}
}
