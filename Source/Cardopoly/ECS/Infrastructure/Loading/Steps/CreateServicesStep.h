#pragma once

#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/ECS/Factories/CoreGameplaySystemsFactory.h"
#include "Cardopoly/Infrastructure/Core/Ticker.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class UCityGeneratorConfig;
class IServiceContainer;

class CreateServicesStep : LoadSequenceStep
{
public:
	CreateServicesStep(IServiceContainer& serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual SD::TExpectedFuture<void> Execute() override
	{
		UWorld* viewWorld = ServiceContainer.Get<UWorld>();
		UGameplayAssetData* GameplayAssetData = ServiceContainer.Get<UGameplayAssetData>();
		ULocalConfigHolder* LocalConfigHolder = ServiceContainer.Get<ULocalConfigHolder>();
		CityGridService* CityGrid = ServiceContainer.Get<CityGridService>();
		GridLayout* _gridLayout = ServiceContainer.Get<GridLayout>();
		flecs::world* _world = ServiceContainer.Get<flecs::world>();
		GridObjectsDataProvider* _gridObjectsDataProvider = ServiceContainer.Get<GridObjectsDataProvider>();
		PositionConversionService* _positionConversionService = ServiceContainer.Get<PositionConversionService>();
		
		auto buildingEntityFactory = new BuildingEntityFactory(_world, _gridObjectsDataProvider);
		
		auto buildingService = new BuildingService(
			CityGrid,
			buildingEntityFactory,
			_gridLayout,
			LocalConfigHolder->BuildingConfigHolder,
			_gridObjectsDataProvider,
			_positionConversionService
		);

		auto buildingPrototypeService = new BuildingPrototypeService(
			viewWorld,
			GameplayAssetData,
			_positionConversionService,
			_gridObjectsDataProvider,
			buildingService,
			_gridLayout
		);

		ServiceContainer
			.Set<BuildingEntityFactory>(buildingEntityFactory)
			.BindLifetimeToContainer();

		ServiceContainer
			.Set<BuildingService>(buildingService)
			.BindLifetimeToContainer();

		ServiceContainer
			.Set<BuildingPrototypeService>(buildingPrototypeService)
			.BindLifetimeToContainer();

		
		auto _aStar = new Pathfinding::AStar(CityGrid);
		ServiceContainer
			.Set<Pathfinding::AStar>(_aStar)
			.BindLifetimeToContainer();
		
		return SD::MakeReadyFuture();
	}
};
