#pragma once
#include "Grid/IOccupyGrid.h"
#include "ABuilding.generated.h"

UCLASS()
class ABuilding : public AActor, public IOccupyGrid
{
	GENERATED_BODY()

public:
	UStaticMeshComponent *SphereMesh;
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
