﻿#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/ECS/Core/Grid/Services/CityGridService.h"
#include "GameFramework/Actor.h"

class UBuildingConfigHolder;
class UGridSubsystem;

class BuildingService
{
public:
	BuildingService(
		CityGridService* cityGrid,
		BuildingEntityFactory* buildingEntityFactory,
		UGridSubsystem* gridSubsystem,
		UWorld* viewWorld,
		UBuildingConfigHolder* buildingConfigHolder
	)
		: _gridSubsystem(gridSubsystem),
		_cityGrid(cityGrid),
		_buildingEntityFactory(buildingEntityFactory),
		_viewWorld(viewWorld),
		_buildingConfigHolder(buildingConfigHolder)
	{
		
	}

	bool CreateBuildingUnderScreenPosition(const FVector2D screenPosition, const uint32 id, flecs::entity& building) const;

	flecs::entity CreateBuilding(const FIntVector cellPosition, const uint32 id) const;

	bool CanCreateBuildingUnderScreenPosition(const FVector2D screenPosition) const;
	bool IsCellOccupied(FIntVector cellPosition) const;
	bool ScreenPointToGroundPosition(FVector2D screenPosition, FIntVector& cellPosition) const;

private:
	UGridSubsystem* _gridSubsystem;
	CityGridService* _cityGrid;
	BuildingEntityFactory* _buildingEntityFactory;
	UWorld* _viewWorld;
	UBuildingConfigHolder* _buildingConfigHolder;
};