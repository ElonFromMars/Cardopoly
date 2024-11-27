#pragma once

#include <vector>

#include "flecs.h"
#include "CoreMinimal.h"
#include "Buildings/BuildingService.h"
#include "Configs/UCityGeneratorConfig.h"
#include "ECS/Infrastructure/Systems/IGameplaySystem.h"
#include "EventBus/EventBus.hpp"
#include "GameFramework/GameModeBase.h"
#include "Pathfinding/AStar.h"
#include "CardopolyGameMode.generated.h"

class GridObjectsDataProvider;
class CityGridService;
class UHUDWidget;

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
	AHand* CreateHand(BuildingService* BuildingsController, EventBus* eventBus) const;

	void CreateInput() const;
	BuildingService* CreateBuildingService(CityGridService* CityGrid);
	CityGridService* CreateCityGrid();
	void ConfigureCamera() const;
	void CreateAndAddHUDWidget();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	UCityGeneratorConfig* CityGeneratorConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	ULocalConfigHolder* LocalConfigHolder;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AssetData")
	UGameplayAssetData* GameplayAssetData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD")
	TSubclassOf<UHUDWidget> WB_HUDClass;

	UPROPERTY()
	UHUDWidget* HUDWidgetInstance;

	UPROPERTY()
	AHand* Hand;

private:
	EventBus* _eventBus;
	flecs::world* _world;
	Pathfinding::AStar* _aStar;
	std::vector<IGameplaySystem*> _systems;
	BuildingEntityFactory* _buildingEntityFactory;
	BuildingService* _buildingService;
	CityGridService* _cityGrid;
	GridObjectsDataProvider* _gridObjectsDataProvider;
	GridLayout* _gridLayout;
};
