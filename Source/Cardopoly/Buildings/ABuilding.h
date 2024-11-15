#pragma once
#include "Cardopoly/View/AEntityView.h"
//#include "Cardopoly/Grid/IOccupyGrid.h"
#include "ABuilding.generated.h"

UCLASS(BlueprintType)
class ABuilding : public AEntityView//, public IOccupyGrid
{
	GENERATED_BODY()

public:
	UStaticMeshComponent *SphereMesh;
	// Sets default values for this actor's properties
	ABuilding();
	
};
