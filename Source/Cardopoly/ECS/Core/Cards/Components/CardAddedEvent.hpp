#pragma once
#include "flecs.h"

struct CardAddedEvent
{
	flecs::entity CardEntity;
	int32 PlayerIndex;
};
