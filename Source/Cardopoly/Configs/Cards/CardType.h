#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM()
enum class ECardType : uint16
{
	None = 0,
	Building = 1,
	Ability = 2,
};