#pragma once

#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/Cards/CardConfigService.h"
#include "Cardopoly/ECS/Core/Buildings/Factories/BuildingEntityFactory.h"
#include "Cardopoly/ECS/Core/Cards/Factories/CardEntityFactory.h"
#include "Cardopoly/ECS/Factories/CoreGameplaySystemsFactory.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class UCityGeneratorConfig;
class IServiceContainer;

class CreateServicesStep : LoadSequenceStep
{
public:
	CreateServicesStep(IServiceContainer* serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual UE5Coro::TCoroutine<> Execute() override
	{
		UWorld* viewWorld = ServiceContainer->Get<UWorld>();
		UGameplayAssetData* GameplayAssetData = ServiceContainer->Get<UGameplayAssetData>();
		ULocalConfigHolder* LocalConfigHolder = ServiceContainer->Get<ULocalConfigHolder>();
		CityGridService* CityGrid = ServiceContainer->Get<CityGridService>();
		GridLayout* _gridLayout = ServiceContainer->Get<GridLayout>();
		flecs::world* _world = ServiceContainer->Get<flecs::world>();
		GridObjectsDataProvider* _gridObjectsDataProvider = ServiceContainer->Get<GridObjectsDataProvider>();
		PositionConversionService* _positionConversionService = ServiceContainer->Get<PositionConversionService>();

		auto cardConfigService = new CardConfigService(LocalConfigHolder);
		ServiceContainer->Set<CardConfigService>(cardConfigService).BindLifetimeToContainer();
		
		auto buildingEntityFactory = new BuildingEntityFactory(_world, _gridObjectsDataProvider);
		ServiceContainer->Set<BuildingEntityFactory>(buildingEntityFactory).BindLifetimeToContainer();
		
		auto cardEntityFactory = new CardEntityFactory(_world, cardConfigService);
		ServiceContainer->Set<CardEntityFactory>(cardEntityFactory).BindLifetimeToContainer();
		
		auto buildingService = new BuildingService(
			CityGrid,
			buildingEntityFactory,
			_gridLayout,
			LocalConfigHolder->BuildingConfigHolder,
			_gridObjectsDataProvider,
			_positionConversionService
		);
		ServiceContainer->Set<BuildingService>(buildingService).BindLifetimeToContainer();

		auto buildingPrototypeService = new BuildingPrototypeService(
			viewWorld,
			GameplayAssetData,
			_positionConversionService,
			_gridObjectsDataProvider,
			buildingService,
			_gridLayout
		);
		ServiceContainer->Set<BuildingPrototypeService>(buildingPrototypeService).BindLifetimeToContainer();
		
		auto _aStar = new Pathfinding::AStar(CityGrid);
		ServiceContainer->Set<Pathfinding::AStar>(_aStar)
			.BindLifetimeToContainer();
		
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
};
