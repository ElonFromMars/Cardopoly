#include "CardopolyGameModeBase.h"
#include "ABuildingActor.h"

void ACardopolyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the sphere actor
	FVector SpawnLocation = FVector(0.0f, 0.0f, 2.0f); // Set the spawn location
	FRotator SpawnRotation = FRotator::ZeroRotator; // Set the spawn rotation

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABuildingActor>(ABuildingActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
}
