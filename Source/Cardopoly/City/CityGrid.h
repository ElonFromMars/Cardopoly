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
	TMap<FIntVector, ABuilding*> m_buildingByCellPosition;
	TMap<FIntVector, ABuilding*> m_cellDataByPosition;

public:
	bool ContainsBuildingAtPosition(FIntVector position) const;

	void PutBuildingAtPosition(FIntVector position, ABuilding* building);

	bool TryGetBuildingAtPosition(FIntVector position, ABuilding*& outBuilding);
};
