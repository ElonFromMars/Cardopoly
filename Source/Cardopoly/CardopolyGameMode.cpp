#include "CardopolyGameMode.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingsController.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/CityGrid.h"
#include "City/Generator/CityGenerator.h"
#include "Configs/LocalConfigHolder.h"
#include "ECS/Factories/CoreGameplaySystemsFactory.h"
#include "ECS/Features/MainGameplayFeature.h"
#include "EventBus/EventBus.hpp"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameplayFlow/TurnController.h"
#include "Grid/UGridSubsystem.h"
#include "Pathfinding/AStar.h"
#include "Player/CardopolyPlayerController.h"
#include "UI/UHUDWidget.h"

ACardopolyGameMode::ACardopolyGameMode()
{
	bNetLoadOnClient = false;
	bPauseable = true;
	bStartPlayersAsSpectators = false;
	PrimaryActorTick.bCanEverTick = true;

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

ACardopolyGameMode::~ACardopolyGameMode()
{
	delete _eventBus;
	delete _aStar;
	delete _world;
	delete _buildingEntityFactory;
	for (auto system : _systems)
	{
		delete system;
	}
}

void ACardopolyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	EventBus* eventBus = CreateEventBus();
	UCityGrid* CityGrid = CreateCityGrid();
	
	CreateInput();
	ConfigureCamera();
	
	CreateAndAddHUDWidget();
	CreatePathfinding(CityGrid);
	StartECS(CityGrid);
	
	ABuildingsController* BuildingsController = CreateBuildingController(CityGrid);
	//CreateCity(BuildingsController);
	AHand* Hand = CreateHand(BuildingsController, eventBus);
	TurnController = CreateTurnController(Hand);
}

void ACardopolyGameMode::Tick(float DeltaTime)
{
	_world->progress(DeltaTime);
	Super::Tick(DeltaTime);
}

void ACardopolyGameMode::CreatePathfinding(UCityGrid* CityGrid)
{
	_aStar = new Pathfinding::AStar(CityGrid);
}

void ACardopolyGameMode::StartECS(UCityGrid* CityGrid)
{
	_gridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
	_world = new flecs::world();


	_buildingEntityFactory = new BuildingEntityFactory(_world);
	
	auto factory = std::make_unique<CoreGameplaySystemsFactory>(
		_world,
		_gridSubsystem,
		CityGrid,
		_aStar,
		GetWorld(),
		HUDWidgetInstance,
		GameplayAssetData
	);

	auto mainGameplayFeature = std::make_unique<MainGameplayFeature>(std::move(factory));

	_systems = mainGameplayFeature->GetSystems();
	
	for (auto system : _systems)
	{
		if(system)
		{
			system->Initialize();	
		}
	}
}

EventBus* ACardopolyGameMode::CreateEventBus()
{
	_eventBus = new EventBus;
	
	return _eventBus;
}

void ACardopolyGameMode::CreateCity(ABuildingsController* BuildingsController) const
{
	UWorld* World = GetWorld();
	CityGenerator cityGenerator = CityGenerator(CityGeneratorConfig, World, BuildingsController);

	cityGenerator.Generate();
}

AHand* ACardopolyGameMode::CreateHand(ABuildingsController* BuildingsController, EventBus* eventBus) const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	
	AHand* Hand = World->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
	Hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	UCardFactory* CardFactory = NewObject<UCardFactory>();
	CardFactory->Construct(World, GameplayAssetData, BuildingsController, LocalConfigHolder);
	
	Hand->Construct(CardFactory, eventBus);
	
	
	Hand->DrawCard();
	
	return Hand;
}

ATurnController* ACardopolyGameMode::CreateTurnController(AHand* Hand) const
{
	UWorld* World = GetWorld();
	ATurnController* turnController = World->SpawnActor<ATurnController>(FVector::ZeroVector, FRotator::ZeroRotator);
	turnController->Construct(Hand, LocalConfigHolder->HandLocalConfig);
	turnController->StartSession();

	return turnController;
}

void ACardopolyGameMode::CreateInput() const
{
	UWorld* World = GetWorld();
	ACardopolyPlayerController* CardopolyPlayerController = Cast<ACardopolyPlayerController>(World->GetFirstPlayerController());
	CardopolyPlayerController->Construct(LocalConfigHolder->InputLocalConfig);
}

ABuildingsController* ACardopolyGameMode::CreateBuildingController(UCityGrid* CityGrid) const
{
	UWorld* World = GetWorld();
	ABuildingsController* BuildingsController = World->SpawnActor<ABuildingsController>(FVector::ZeroVector, FRotator::ZeroRotator);
	BuildingsController->Construct(CityGrid, _buildingEntityFactory);
	
	return BuildingsController;
}

UCityGrid* ACardopolyGameMode::CreateCityGrid() const
{
	UCityGrid* CityGrid = NewObject<UCityGrid>();
	return CityGrid;
}

void ACardopolyGameMode::ConfigureCamera() const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	auto Camera = StaticCast<ARTSCamera*>(PlayerPawn);
	Camera->Construct(_eventBus);
}

void ACardopolyGameMode::CreateAndAddHUDWidget()
{
	HUDWidgetInstance = CreateWidget<UHUDWidget>(GetWorld(), WB_HUDClass);
	HUDWidgetInstance->AddToViewport();
	HUDWidgetInstance->Construct(TurnController);
}
