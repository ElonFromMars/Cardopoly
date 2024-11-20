#pragma once

#include "CoreMinimal.h"
#include "EBuildingIdConfig.generated.h"

UENUM()
enum class EBuildingIdConfig : uint32
{
	None = 0,
	House = 1001,
	Cafe = 1002,
	Skyscraper = 1003
};