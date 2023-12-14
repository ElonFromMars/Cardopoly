#include "CardopolyGameModeBase.h"
#include "ABuildingActor.h"
#include "ARTSCamera.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"

ACardopolyGameModeBase::ACardopolyGameModeBase()
{
	bNetLoadOnClient = false;
	bPauseable = true;
	bStartPlayersAsSpectators = false;

	DefaultPawnClass = ARTSCamera::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
	PlayerStateClass = APlayerState::StaticClass();
	GameStateClass = AGameStateBase::StaticClass();
	HUDClass = AHUD::StaticClass();
	GameSessionClass = AGameSession::StaticClass();
	SpectatorClass = ASpectatorPawn::StaticClass();
	ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
	ServerStatReplicatorClass = AServerStatReplicator::StaticClass();
}

void ACardopolyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the sphere actor
	FVector SpawnLocation = FVector(0.0f, 0.0f, 2.0f); // Set the spawn location
	FRotator SpawnRotation = FRotator::ZeroRotator; // Set the spawn rotation

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABuildingActor>(ABuildingActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
}
