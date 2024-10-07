#pragma once

#include <vector>
#include "CoreMinimal.h"

struct FGridPathComponent
{
	FIntVector CurrentGridTarget;
	int CurrentTargetIndex;
	
	std::vector<FIntVector> Path;
};
