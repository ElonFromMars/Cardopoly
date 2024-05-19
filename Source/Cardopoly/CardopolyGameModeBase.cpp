#include "CardopolyGameModeBase.h"
#include "ARTSCamera.h"
#include "City/Generator/CityGenerator.h"
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

	CreateCity();
}

void ACardopolyGameModeBase::CreateCity()
{
	UWorld* world = GetWorld();
	auto cityGenerator = CityGenerator(cityGeneratorConfig, world);

	cityGenerator.Generate();
}
