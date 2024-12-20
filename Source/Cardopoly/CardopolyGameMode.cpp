#include "CardopolyGameMode.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingPrototypeService.h"
#include "Buildings/BuildingService.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "ProceduralGeneration/City/CityGeneratorService.h"
#include "Configs/LocalConfigHolder.h"
#include "Configs/Buildings/GridObjectsDataProvider.h"
#include "Configs/Buildings/UBuildingConfig.h"
#include "ECS/Core/Grid/Services/CityGridService.h"
#include "ECS/Factories/CoreGameplaySystemsFactory.h"
#include "ECS/Features/MainGameplayFeature.h"
#include "EventBus/EventBus.hpp"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"
#include "Grid/GridLayout.h"
#include "Grid/PositionConversionService.h"
#include "Infrastructure/DI/ServiceContainer.h"
#include "Infrastructure/Loading/LoadSequenceExecutor.h"
#include "Loading/Sequences/MainLoadSequence.h"
#include "Pathfinding/AStar.h"
#include "Player/CardopolyPlayerController.h"
#include "UI/UGameplayOverlayWidget.h"
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
	delete _gridObjectsDataProvider;
	delete _cityGrid;
	delete _gridLayout;
	delete _buildingService;
	delete _positionConversionService;
	delete _loadSequencePlayer;
	
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
	CityGridService* cityGrid = CreateCityGrid();
	
	
	CreateInput();
	CreateBuildingService(cityGrid);

	ConfigureCamera();

	CreateUIWidgets();
	//CreateCity(BuildingsController);
	Hand = CreateHand(_buildingService, eventBus);
	
	CreatePathfinding(cityGrid);
	StartECS(cityGrid);

	_serviceContainer = new ServiceContainer();
	_serviceContainer->Set<ULocalConfigHolder*>(LocalConfigHolder);
	std::shared_ptr<LoadSequence> loadSequence = MainLoadSequence::CreateMainLoadingQueue(*_serviceContainer);
	_loadSequencePlayer = new LoadSequencePlayer();
	_loadSequencePlayer->Execute(loadSequence);
}

void ACardopolyGameMode::Tick(float DeltaTime)
{
	_world->progress(DeltaTime);
	Super::Tick(DeltaTime);
}

void ACardopolyGameMode::CreatePathfinding(CityGridService* CityGrid)
{
	_aStar = new Pathfinding::AStar(CityGrid);
}

void ACardopolyGameMode::StartECS(CityGridService* CityGrid)
{
	auto factory = std::make_unique<CoreGameplaySystemsFactory>(
		_world,
		_gridLayout,
		CityGrid,
		_aStar,
		GetWorld(),
		HUDWidgetInstance,
		GameplayOverlayWidgetInstance,
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

void ACardopolyGameMode::CreateCity(BuildingService* BuildingsController) const
{
	UWorld* World = GetWorld();
	CityGeneratorService cityGenerator = CityGeneratorService(CityGeneratorConfig, World, BuildingsController);

	cityGenerator.Generate();
}

AHand* ACardopolyGameMode::CreateHand(BuildingService* buildingService, EventBus* eventBus) const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	
	AHand* hand = World->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
	hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	UCardFactory* CardFactory = NewObject<UCardFactory>();
	CardFactory->Construct(World, GameplayAssetData, buildingService, _buildingPrototypeService, LocalConfigHolder);
	
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

BuildingService* ACardopolyGameMode::CreateBuildingService(CityGridService* CityGrid)
{
	_buildingEntityFactory = new BuildingEntityFactory(_world, _gridObjectsDataProvider);
	
	UWorld* World = GetWorld();
	_buildingService = new BuildingService(
		CityGrid,
		_buildingEntityFactory,
		_gridLayout,
		World,
		LocalConfigHolder->BuildingConfigHolder,
		_gridObjectsDataProvider,
		_positionConversionService
	);

	_buildingPrototypeService = new BuildingPrototypeService(
		World,
		GameplayAssetData,
		_positionConversionService,
		_gridObjectsDataProvider,
		_buildingService,
		_gridLayout
	);
	
	return _buildingService;
}

CityGridService* ACardopolyGameMode::CreateCityGrid()
{
	_gridLayout = new GridLayout();
	_gridLayout->Construct(GetWorld());
	_gridObjectsDataProvider = new GridObjectsDataProvider(LocalConfigHolder->BuildingConfigHolder);
	_gridObjectsDataProvider->Initialize();
	_cityGrid = new CityGridService(_gridObjectsDataProvider);

	_positionConversionService = new PositionConversionService(GetWorld(), _gridLayout);

	return _cityGrid;
}

void ACardopolyGameMode::ConfigureCamera() const
{
	UWorld* World = GetWorld();
	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawnOrSpectator();
	auto Camera = StaticCast<ARTSCamera*>(PlayerPawn);
	Camera->Construct(_eventBus);
}

void ACardopolyGameMode::CreateUIWidgets()
{
	GameplayOverlayWidgetInstance = CreateWidget<UGameplayOverlayWidget>(GetWorld(), WB_GameplayOverlayClass);
	GameplayOverlayWidgetInstance->Construct(_positionConversionService, GameplayAssetData);
	GameplayOverlayWidgetInstance->AddToViewport();
	
	HUDWidgetInstance = CreateWidget<UHUDWidget>(GetWorld(), WB_HUDClass);
	HUDWidgetInstance->AddToViewport();
	HUDWidgetInstance->Construct(_world);
}
