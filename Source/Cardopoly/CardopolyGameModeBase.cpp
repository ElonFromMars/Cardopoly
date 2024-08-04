#include "CardopolyGameModeBase.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/Generator/CityGenerator.h"
#include "Configs/LocalConfigHolder.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameplayFlow/TurnController.h"
#include "Player/CardopolyPlayerController.h"

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
	CreateInput();
	CreateHand();
}

void ACardopolyGameModeBase::CreateCity() const
{
	UWorld* World = GetWorld();
	CityGenerator cityGenerator = CityGenerator(CityGeneratorConfig, World);

	cityGenerator.Generate();
}

void ACardopolyGameModeBase::CreateHand() const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	
	AHand* Hand = World->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
	Hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	UCardFactory* CardFactory = NewObject<UCardFactory>();
	CardFactory->Init(GameplayAssetData, World);
	
	Hand->Init(CardFactory);
	Hand->DrawCard();

	ATurnController* TurnController = World->SpawnActor<ATurnController>(ATurnController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	TurnController->Construct(Hand, LocalConfigHolder->HandLocalConfig);
	TurnController->StartSession();
}

void ACardopolyGameModeBase::CreateInput() const
{
	UWorld* World = GetWorld();
	ACardopolyPlayerController* CardopolyPlayerController = Cast<ACardopolyPlayerController>(World->GetFirstPlayerController());
	CardopolyPlayerController->Construct(LocalConfigHolder->InputLocalConfig);
}