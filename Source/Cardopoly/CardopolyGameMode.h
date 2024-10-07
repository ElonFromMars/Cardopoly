#pragma once

#include "flecs.h"
#include "CoreMinimal.h"
#include "Buildings/BuildingsController.h"
#include "City/CityGrid.h"
#include "Configs/UCityGeneratorConfig.h"
#include "EventBus/EventBus.hpp"
#include "GameFramework/GameModeBase.h"
#include "CardopolyGameMode.generated.h"

namespace Pathfinding
{
	class AStar;
}

class ATurnController;
class ULocalConfigHolder;
class AHand;
class UGameplayAssetData;

UCLASS()
class CARDOPOLY_API ACardopolyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	UCityGeneratorConfig* CityGeneratorConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	ULocalConfigHolder* LocalConfigHolder;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AssetData")
	UGameplayAssetData* GameplayAssetData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controllers")
	ATurnController* TurnController;

private:
	EventBus* _eventBus;
	flecs::world* _world;
	Pathfinding::AStar* _aStar;
	UGridSubsystem* _gridSubsystem;

public:
	ACardopolyGameMode();

	virtual ~ACardopolyGameMode() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	void CreatePathfinding(UCityGrid* CityGrid);

	void StartECS(UCityGrid* CityGrid);
	
	EventBus* CreateEventBus();
	
	void CreateCity(ABuildingsController* BuildingsController) const;
	AHand* CreateHand(ABuildingsController* BuildingsController, EventBus* eventBus) const;
	ATurnController* CreateTurnController(AHand* Hand) const;
	void CreateInput() const;
	ABuildingsController* CreateBuildingController(UCityGrid* CityGrid) const;
	UCityGrid* CreateCityGrid() const;
	void ConfigureCamera() const;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateUI();
};
