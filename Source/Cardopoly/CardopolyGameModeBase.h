#pragma once

#include "CoreMinimal.h"
#include "Buildings/BuildingsController.h"
#include "City/CityGrid.h"
#include "Configs/UCityGeneratorConfig.h"
#include "GameFramework/GameModeBase.h"
#include "CardopolyGameModeBase.generated.h"

class ATurnController;
class ULocalConfigHolder;
class AHand;
class UGameplayAssetData;

UCLASS()
class CARDOPOLY_API ACardopolyGameModeBase : public AGameModeBase
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
	
	ACardopolyGameModeBase();

	virtual void BeginPlay() override;

	void CreateCity(ABuildingsController* BuildingsController) const;
	AHand* CreateHand(ABuildingsController* BuildingsController) const;
	ATurnController* CreateTurnController(AHand* Hand) const;
	void CreateInput() const;
	ABuildingsController* CreateBuildingController(UCityGrid* CityGrid) const;
	UCityGrid* CreateCityGrid() const;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateUI();
};
