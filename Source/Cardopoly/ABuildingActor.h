#pragma once
#include "ABuildingActor.generated.h"

UCLASS()
class ABuildingActor : public AActor
{
	GENERATED_BODY()

public:
	UStaticMeshComponent *SphereMesh;
	// Sets default values for this actor's properties
	ABuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
