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
#include "Infrastructure/Core/Ticker.h"
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
	
	delete _gridObjectsDataProvider;
	delete _cityGrid;
	delete _gridLayout;
	delete _buildingService;
	delete _positionConversionService;

	delete _loadSequencePlayer;
	delete _serviceContainer;
	delete _ticker;
}

void ACardopolyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//TODO move to load sequence
	EventBus* eventBus = CreateEventBus();
	CreateInput();
	ConfigureCamera();
	
	
	_ticker = new Ticker();

	_serviceContainer = new ServiceContainer();

	_serviceContainer->Set<ULocalConfigHolder>(LocalConfigHolder);
	_serviceContainer->Set<EventBus>(eventBus);
	_serviceContainer->Set<UWorld>(GetWorld());
	_serviceContainer->Set<UGameplayAssetData>(GameplayAssetData);
	_serviceContainer->Set<UCityGeneratorConfig>(CityGeneratorConfig);
	_serviceContainer->Set<ULocalConfigHolder>(LocalConfigHolder);
	
	
	_serviceContainer->Set<CityGridService>(_cityGrid);
	_serviceContainer->Set<Ticker>(_ticker);
	_serviceContainer->Set<BuildingPrototypeService>(_buildingPrototypeService);

	CityGridService* cityGrid = CreateCityGrid();
	_serviceContainer->Set<GridLayout>(_gridLayout);
	_serviceContainer->Set<GridObjectsDataProvider>(_gridObjectsDataProvider);
	_serviceContainer->Set<CityGridService>(cityGrid);
	_serviceContainer->Set<PositionConversionService>(_positionConversionService);

	CreateUIWidgets();//TODO move to load sequence
	_serviceContainer->Set<UGameplayOverlayWidget>(GameplayOverlayWidgetInstance);
	_serviceContainer->Set<UHUDWidget>(HUDWidgetInstance);

	
	std::shared_ptr<LoadSequence> loadSequence = MainLoadSequence::CreateMainLoadingQueue(_serviceContainer);
	_loadSequencePlayer = new LoadSequencePlayer();
	_loadSequencePlayer->Execute(loadSequence);
}

void ACardopolyGameMode::Tick(float DeltaTime)
{
	_ticker->Update(DeltaTime);
	Super::Tick(DeltaTime);
}

EventBus* ACardopolyGameMode::CreateEventBus()
{
	_eventBus = new EventBus;
	
	return _eventBus;
}

void ACardopolyGameMode::CreateInput() const
{
	UWorld* World = GetWorld();
	ACardopolyPlayerController* CardopolyPlayerController = Cast<ACardopolyPlayerController>(World->GetFirstPlayerController());
	CardopolyPlayerController->Construct(LocalConfigHolder->InputLocalConfig);
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
}
