#pragma once

#include "CardType.h"

class BaseCardData
{
public:
	FName Id;
	FText Name;
	FText Description;
	int32 Cost;
	ECardType Type;
};
