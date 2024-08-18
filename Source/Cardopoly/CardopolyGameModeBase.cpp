#include "CardopolyGameModeBase.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingsController.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/CityGrid.h"
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

	UCityGrid* CityGrid = CreateCityGrid();
	
	ABuildingsController* BuildingsController = CreateBuildingController(CityGrid);
	CreateCity(BuildingsController);

	CreateInput();
	AHand* Hand = CreateHand(BuildingsController);
	TurnController = CreateTurnController(Hand);

	CreateUI();
}

void ACardopolyGameModeBase::CreateCity(ABuildingsController* BuildingsController) const
{
	UWorld* World = GetWorld();
	CityGenerator cityGenerator = CityGenerator(CityGeneratorConfig, World, BuildingsController);

	cityGenerator.Generate();
}

AHand* ACardopolyGameModeBase::CreateHand(ABuildingsController* BuildingsController) const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	
	AHand* Hand = World->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
	Hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	UCardFactory* CardFactory = NewObject<UCardFactory>();
	CardFactory->Construct(World, GameplayAssetData, BuildingsController);
	
	Hand->Construct(CardFactory);
	Hand->DrawCard();
	
	return Hand;
}

ATurnController* ACardopolyGameModeBase::CreateTurnController(AHand* Hand) const
{
	UWorld* World = GetWorld();
	ATurnController* turnController = World->SpawnActor<ATurnController>(FVector::ZeroVector, FRotator::ZeroRotator);
	turnController->Construct(Hand, LocalConfigHolder->HandLocalConfig);
	turnController->StartSession();

	return turnController;
}

void ACardopolyGameModeBase::CreateInput() const
{
	UWorld* World = GetWorld();
	ACardopolyPlayerController* CardopolyPlayerController = Cast<ACardopolyPlayerController>(World->GetFirstPlayerController());
	CardopolyPlayerController->Construct(LocalConfigHolder->InputLocalConfig);
}

ABuildingsController* ACardopolyGameModeBase::CreateBuildingController(UCityGrid* CityGrid) const
{
	UWorld* World = GetWorld();
	ABuildingsController* BuildingsController = World->SpawnActor<ABuildingsController>(FVector::ZeroVector, FRotator::ZeroRotator);
	BuildingsController->Construct(CityGrid);
	
	return BuildingsController;
}

UCityGrid* ACardopolyGameModeBase::CreateCityGrid() const
{
	UCityGrid* CityGrid = NewObject<UCityGrid>();
	return CityGrid;
}
