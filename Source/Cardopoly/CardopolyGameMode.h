#pragma once

#include <vector>

#include "flecs.h"
#include "CoreMinimal.h"
#include "Buildings/BuildingService.h"
#include "Configs/UCityGeneratorConfig.h"
#include "ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "EventBus/EventBus.hpp"
#include "GameFramework/GameModeBase.h"
#include "Infrastructure/Loading/LoadSequenceExecutor.h"
#include "Pathfinding/AStar.h"
#include "CardopolyGameMode.generated.h"

class IServiceContainer;
class BuildingPrototypeService;
class GridObjectsDataProvider;
class CityGridService;
class UHUDWidget;
class UGameplayOverlayWidget;

namespace Pathfinding
{
	class AStar;
}


class ULocalConfigHolder;
class AHand;
class UGameplayAssetData;

UCLASS()
class CARDOPOLY_API ACardopolyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACardopolyGameMode();

	virtual ~ACardopolyGameMode() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	void CreatePathfinding(CityGridService* CityGrid);

	void StartECS(CityGridService* CityGrid);
	
	EventBus* CreateEventBus();
	
	void CreateCity(BuildingService* BuildingsController) const;
	AHand* CreateHand(BuildingService* buildingService, EventBus* eventBus) const;

	void CreateInput() const;
	BuildingService* CreateBuildingService(CityGridService* CityGrid);
	CityGridService* CreateCityGrid();
	void ConfigureCamera() const;
	void CreateUIWidgets();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	UCityGeneratorConfig* CityGeneratorConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	ULocalConfigHolder* LocalConfigHolder;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AssetData")
	UGameplayAssetData* GameplayAssetData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UHUDWidget> WB_HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UGameplayOverlayWidget> WB_GameplayOverlayClass;

	UPROPERTY()
	UHUDWidget* HUDWidgetInstance;

	UPROPERTY()
	UGameplayOverlayWidget* GameplayOverlayWidgetInstance;

	UPROPERTY()
	AHand* Hand;

private:
	EventBus* _eventBus;
	flecs::world* _world;
	Pathfinding::AStar* _aStar;
	std::vector<IGameplaySystem*> _systems;
	BuildingEntityFactory* _buildingEntityFactory;
	BuildingService* _buildingService;
	BuildingPrototypeService* _buildingPrototypeService;
	CityGridService* _cityGrid;
	GridObjectsDataProvider* _gridObjectsDataProvider;
	GridLayout* _gridLayout;
	PositionConversionService* _positionConversionService;
	LoadSequencePlayer* _loadSequencePlayer;
	IServiceContainer* _serviceContainer;
};
