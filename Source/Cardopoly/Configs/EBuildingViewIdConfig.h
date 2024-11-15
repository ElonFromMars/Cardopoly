#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EBuildingViewIdConfig.generated.h"

UENUM()
enum class EBuildingViewIdConfig : uint16
{
	None = 0,
	House = 1001,
	Cafe = 1002,
	Skyscraper = 1003
};