#include "CardopolyGameMode.h"
#include "ECS/Movement/Components/FPositionComponent.h"
#include "ARTSCamera.h"
#include "AssetHolders/GameplayAssetData.h"
#include "Buildings/BuildingsController.h"
#include "Cards/CardFactory.h"
#include "Cards/Hand/Hand.h"
#include "City/CityGrid.h"
#include "City/Generator/CityGenerator.h"
#include "Configs/LocalConfigHolder.h"
#include "ECS/Movement/Components/FCitizenTag.h"
#include "ECS/Movement/Components/FGridPathComponent.h"
#include "ECS/Movement/Components/FSearchPathRequest.h"
#include "ECS/Movement/Components/FGridPositionComponent.h"
#include "ECS/Movement/Components/FMaxSpeedComponent.h"
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
	
	_world->system<FPositionComponent, FGridPositionComponent, FGridPathComponent, FMaxSpeedComponent>("MoveSystem")
		.each([this](flecs::entity entity, FPositionComponent& pos, FGridPositionComponent& gridPos, FGridPathComponent& gridPath, FMaxSpeedComponent& speed) {

				auto deltaTime = _world->delta_time();
				FVector targetWorldPos = _gridSubsystem->GetCellCenterWorldPosition(gridPath.CurrentGridTarget);
			    FVector difference = (targetWorldPos - pos.Value).GetSafeNormal() * speed.Value * deltaTime;
				FVector newWorldPos = pos.Value + difference;
			    pos.Value = newWorldPos;
				auto newGridPos = _gridSubsystem->WorldPositionToGrid(newWorldPos);
				gridPos.Value = newGridPos;

				auto size = gridPath.Path.size();
				if((newWorldPos -targetWorldPos).Size() < 20.0f)
				{
					if(gridPath.CurrentTargetIndex >= size - 1)
                    {
                        entity.remove<FGridPathComponent>();
                        entity.add<FSearchPathRequest>();
                    }
					else
                    {
                        gridPath.CurrentTargetIndex++;
                        gridPath.CurrentGridTarget = gridPath.Path[gridPath.CurrentTargetIndex];
                    }
				}
		});

	_world->system<FPositionComponent>("DrawDebugViewSystem")
		.each([this](FPositionComponent& pos) {
			DrawDebugPoint(GetWorld(), FVector(pos.Value.X, pos.Value.Y, 10.0f), 10.0f, FColor::Red, false, 0.1f);
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
