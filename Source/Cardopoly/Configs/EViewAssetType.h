#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EViewAssetType.generated.h"

UENUM()
enum class EViewAssetType : uint16
{
	None = 0,
	Card = 1,
	Building = 2,
};