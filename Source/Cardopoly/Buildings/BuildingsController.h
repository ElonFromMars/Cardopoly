#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/City/CityGrid.h"
#include "GameFramework/Actor.h"
#include "BuildingsController.generated.h"

class UGridSubsystem;

UCLASS()
class CARDOPOLY_API ABuildingsController : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UGridSubsystem* GridSubsystem;
	UPROPERTY()
	UCityGrid* CityGrid;

public:
	ABuildingsController();
	void Construct(UCityGrid* CityGrid);

	bool CreateBuildingUnderScreenPosition(FVector2D ScreenPosition, ABuilding*& Building) const;

	ABuilding* CreateBuilding(const FIntVector CellPosition) const;

	bool CanCreateBuildingUnderScreenPosition(FVector2D ScreenPosition) const;
	bool IsCellOccupied(FIntVector CellPosition) const;
	bool ScreenPointToGroundPosition(FVector2D ScreenPosition, FIntVector& CellPosition) const;

private:
	virtual void BeginPlay() override;
};
