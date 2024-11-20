#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/ECS/Core/Grid/Services/CityGridService.h"
#include "GameFramework/Actor.h"
#include "BuildingsController.generated.h"

class ABuilding;
class UGridSubsystem;

UCLASS()
class CARDOPOLY_API ABuildingsController : public AActor
{
	GENERATED_BODY()
	
public:
	void Construct(CityGridService* cityGrid, BuildingEntityFactory* buildingEntityFactory);

	bool CreateBuildingUnderScreenPosition(const FVector2D ScreenPosition, const uint32 id, ABuilding*& Building) const;

	ABuilding* CreateBuilding(const FIntVector cellPosition, const uint32 id) const;

	bool CanCreateBuildingUnderScreenPosition(const FVector2D ScreenPosition) const;
	bool IsCellOccupied(FIntVector CellPosition) const;
	bool ScreenPointToGroundPosition(FVector2D ScreenPosition, FIntVector& CellPosition) const;

private:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGridSubsystem* _gridSubsystem;

	CityGridService* _cityGrid;
	BuildingEntityFactory* _buildingEntityFactory;
};
