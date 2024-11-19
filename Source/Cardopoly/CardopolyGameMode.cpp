#include "CardopolyGameMode.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingsController.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/CityGridService.h"
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
	
	_world = new flecs::world();
	EventBus* eventBus = CreateEventBus();
	UCityGrid* CityGrid = CreateCityGrid();

	CreateInput();
	ABuildingsController* BuildingsController = CreateBuildingController(CityGrid);

	ConfigureCamera();

	CreateAndAddHUDWidget();
	//CreateCity(BuildingsController);
	Hand = CreateHand(BuildingsController, eventBus);
	
	CreatePathfinding(CityGrid);
	StartECS(CityGrid);
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
	
	auto factory = std::make_unique<CoreGameplaySystemsFactory>(
		_world,
		_gridSubsystem,
		CityGrid,
		_aStar,
		GetWorld(),
		HUDWidgetInstance,
		GameplayAssetData,
		Hand,
		LocalConfigHolder->HandLocalConfig
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
	
	AHand* hand = World->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
	hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	UCardFactory* CardFactory = NewObject<UCardFactory>();
	CardFactory->Construct(World, GameplayAssetData, BuildingsController, LocalConfigHolder);
	
	hand->Construct(CardFactory, eventBus);
	
	
	hand->DrawCard();
	
	return hand;
}



void ACardopolyGameMode::CreateInput() const
{
	UWorld* World = GetWorld();
	ACardopolyPlayerController* CardopolyPlayerController = Cast<ACardopolyPlayerController>(World->GetFirstPlayerController());
	CardopolyPlayerController->Construct(LocalConfigHolder->InputLocalConfig);
}

ABuildingsController* ACardopolyGameMode::CreateBuildingController(UCityGrid* CityGrid)
{
	_buildingEntityFactory = new BuildingEntityFactory(_world);
	
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
	HUDWidgetInstance->Construct(_world);
}
