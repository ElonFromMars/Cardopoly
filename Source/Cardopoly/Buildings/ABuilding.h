#pragma once
#include "Cardopoly/View/AEntityView.h"
//#include "Cardopoly/Grid/IOccupyGrid.h"
#include "ABuilding.generated.h"

UCLASS(BlueprintType)
class ABuilding : public AEntityView//, public IOccupyGrid
{
	GENERATED_BODY()

public:
	ABuilding();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MainMesh;
};
