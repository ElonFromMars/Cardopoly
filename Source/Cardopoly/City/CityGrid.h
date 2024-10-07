#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CityGrid.generated.h"

class ABuilding;

UCLASS()
class CARDOPOLY_API UCityGrid : public UObject
{
	GENERATED_BODY()
private:
	TMap<FIntVector, ABuilding*> BuildingByCellPosition;

public:
	bool ContainsBuildingAtPosition(FIntVector Position) const;

	void PutBuildingAtPosition(FIntVector Position, ABuilding* Building);

	bool GetBuildingAtPosition(FIntVector Position, ABuilding*& Building);

	bool IsValidPosition(const FIntVector& Pos);
};
