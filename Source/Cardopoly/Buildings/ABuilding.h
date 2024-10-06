#pragma once
#include "Cardopoly/Grid/IOccupyGridData.h"
#include "ABuilding.generated.h"

UCLASS(BlueprintType)
class ABuilding : public AActor
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
