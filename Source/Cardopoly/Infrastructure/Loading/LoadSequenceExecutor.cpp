#include "LoadSequenceExecutor.h"

UE5Coro::TCoroutine<> LoadSequencePlayer::Execute(const std::shared_ptr<LoadSequence>& loadSequence)
{
	_loadSequence = loadSequence;
	
	for (auto step : _loadSequence->Steps)
	{
		co_await step->Execute();
	}
}
