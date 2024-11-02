#include "CardopolyGameMode.h"
#include "ECS/Core/Movement/Components/FPositionComponent.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingsController.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/CityGrid.h"
#include "City/Generator/CityGenerator.h"
#include "Configs/LocalConfigHolder.h"
#include "ECS/Core/Movement/Components/FCitizenTag.h"
#include "ECS/Core/Movement/Components/FGridPathComponent.h"
#include "ECS/Core/Movement/Components/FSearchPathRequest.h"
#include "ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "ECS/Core/Movement/Components/FMaxSpeedComponent.h"
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
}

void ACardopolyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	EventBus* eventBus = CreateEventBus();
	UCityGrid* CityGrid = CreateCityGrid();
	StartECS(CityGrid);
	
	CreatePathfinding(CityGrid);
	
	ABuildingsController* BuildingsController = CreateBuildingController(CityGrid);
	CreateCity(BuildingsController);

	CreateInput();
	ConfigureCamera();
	
	AHand* Hand = CreateHand(BuildingsController, eventBus);
	TurnController = CreateTurnController(Hand);

	CreateUI();
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

	
	for (int i = 0; i < 100; ++i) {
		auto gridPosition = FIntVector
		{
			FMath::RandRange(-10, 10),
			FMath::RandRange(-10, 10),
			0
		};
		auto worldPosition = _gridSubsystem->GetCellCenterWorldPosition(gridPosition);
		_world->entity()
			.add<FCitizenTag>()
		    .add<FSearchPathRequest>()
			.set<FGridPositionComponent>({
				gridPosition
			})
			.set<FPositionComponent>({
				worldPosition
			})
			.set<FMaxSpeedComponent>({
				FMath::RandRange(50.0f, 300.0f)
			});
	}

	_world->system<FGridPositionComponent>("PathfindingSystem")
		.with<FPositionComponent>()
		.with<FSearchPathRequest>()
		.each([this, CityGrid](flecs::entity entity, FGridPositionComponent& gridPos) {

			int xOffset = FMath::RandRange(-5, 5);
			int yOffset = FMath::RandRange(-5, 5);
			
			FIntVector targetGridPos ={
				gridPos.Value.X + xOffset,
				gridPos.Value.Y + yOffset,
				0
			};
			if(CityGrid->ContainsBuildingAtPosition(targetGridPos))
			{
				return;
			}
			std::vector<FIntVector> path = _aStar->FindPath(gridPos.Value, targetGridPos,
			                                                Pathfinding::Heuristic::Euclidean);
			if(path.size() > 1)
			{
				entity.remove<FSearchPathRequest>();
				entity.set<FGridPathComponent>({
					path[0],
					0,
					path
				});
			}
		});
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
	BuildingsController->Construct(CityGrid);
	
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
