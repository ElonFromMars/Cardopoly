#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/City/CityGrid.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "GameFramework/Actor.h"
#include "BuildingsController.generated.h"

class UGridSubsystem;

UCLASS()
class CARDOPOLY_API ABuildingsController : public AActor
{
	GENERATED_BODY()
	
public:
	ABuildingsController();
	void Construct(UCityGrid* cityGrid, BuildingEntityFactory* buildingEntityFactory);

	bool CreateBuildingUnderScreenPosition(FVector2D ScreenPosition, ABuilding*& Building) const;

	ABuilding* CreateBuilding(const FIntVector CellPosition) const;

	bool CanCreateBuildingUnderScreenPosition(FVector2D ScreenPosition) const;
	bool IsCellOccupied(FIntVector CellPosition) const;
	bool ScreenPointToGroundPosition(FVector2D ScreenPosition, FIntVector& CellPosition) const;

private:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGridSubsystem* GridSubsystem;
	UPROPERTY()
	UCityGrid* CityGrid;

	BuildingEntityFactory* _buildingEntityFactory;
};
