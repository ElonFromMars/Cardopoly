#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/City/CityGridService.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "GameFramework/Actor.h"
#include "BuildingsController.generated.h"

class UGridSubsystem;

UCLASS()
class CARDOPOLY_API ABuildingsController : public AActor
{
	GENERATED_BODY()
	
public:
	void Construct(UCityGrid* cityGrid, BuildingEntityFactory* buildingEntityFactory);

	bool CreateBuildingUnderScreenPosition(const FVector2D ScreenPosition, const uint32 id, ABuilding*& Building) const;

	ABuilding* CreateBuilding(const FIntVector cellPosition, const uint32 id) const;

	bool CanCreateBuildingUnderScreenPosition(const FVector2D ScreenPosition) const;
	bool IsCellOccupied(FIntVector CellPosition) const;
	bool ScreenPointToGroundPosition(FVector2D ScreenPosition, FIntVector& CellPosition) const;

private:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGridSubsystem* _gridSubsystem;
	UPROPERTY()
	UCityGrid* CityGrid;

	BuildingEntityFactory* _buildingEntityFactory;
};
