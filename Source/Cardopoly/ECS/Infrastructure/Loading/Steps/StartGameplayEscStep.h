﻿#pragma once

#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/ECS/Core/Cards/Components/CardInHandRelation.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/ExplodingCardComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Services/CitizenGridService.h"
#include "Cardopoly/ECS/Factories/CoreGameplaySystemsFactory.h"
#include "Cardopoly/ECS/Features/MainGameplayFeature.h"
#include "Cardopoly/Infrastructure/Core/Ticker.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"
#include "Cardopoly/ECS/Core/Player/Resources/Services/ResourcesService.h"

class UCityGeneratorConfig;
class IServiceContainer;

class StartGameplayEscStep : LoadSequenceStep
{
public:
	StartGameplayEscStep(IServiceContainer* serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual UE5Coro::TCoroutine<> Execute() override
	{
		Ticker* ticker = ServiceContainer->Get<Ticker>();
		UWorld* viewWorld = ServiceContainer->Get<UWorld>();
		AHand* Hand = ServiceContainer->Get<AHand>();
		UGameplayAssetData* GameplayAssetData = ServiceContainer->Get<UGameplayAssetData>();
		ULocalConfigHolder* LocalConfigHolder = ServiceContainer->Get<ULocalConfigHolder>();
		UGameplayOverlayWidget* GameplayOverlayWidgetInstance = ServiceContainer->Get<UGameplayOverlayWidget>();
		UHUDWidget* HUDWidgetInstance = ServiceContainer->Get<UHUDWidget>();
		CityGridService* CityGrid = ServiceContainer->Get<CityGridService>();
		GridLayout* _gridLayout = ServiceContainer->Get<GridLayout>();
		Pathfinding::AStar* _aStar = ServiceContainer->Get<Pathfinding::AStar>();
		flecs::world* _world = ServiceContainer->Get<flecs::world>();
		BuildingService* buildingService = ServiceContainer->Get<BuildingService>();
		CardEntityFactory* cardEntityFactory = ServiceContainer->Get<CardEntityFactory>();
		CardConfigService* cardConfigService = ServiceContainer->Get<CardConfigService>();
		
		LocalPlayerService* localPlayerService = new LocalPlayerService();
		ServiceContainer->Set(localPlayerService).BindLifetimeToContainer();
		ResourcesService* resourcesService = new ResourcesService(_world);
		ServiceContainer->Set<ResourcesService>(resourcesService).BindLifetimeToContainer();
		CitizenGridService* citizenGridService = new CitizenGridService();
		ServiceContainer->Set<CitizenGridService>(citizenGridService).BindLifetimeToContainer();

		auto factory = std::make_unique<CoreGameplaySystemsFactory>(
			_world,
			_gridLayout,
			CityGrid,
			_aStar,
			viewWorld,
			HUDWidgetInstance,
			GameplayOverlayWidgetInstance,
			GameplayAssetData,
			Hand,
			LocalConfigHolder->HandLocalConfig,
			localPlayerService,
			resourcesService,
			LocalConfigHolder,
			buildingService,
			citizenGridService,
			cardEntityFactory,
			cardConfigService
		);

		GameplayFeature* mainGameplayFeature = new MainGameplayFeature(std::move(factory), _world);

		mainGameplayFeature->Initialize();
		
		ticker->AddTickable([_world](float deltaTime)
		{
			_world->progress();
		});

		ServiceContainer->Set<GameplayFeature>(mainGameplayFeature)
			.BindLifetimeToContainer();
		
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
};