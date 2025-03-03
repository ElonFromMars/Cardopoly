#pragma once

#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/Cards/CardFactory.h"
#include "Cardopoly/Cards/Hand/Hand.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/ECS/Factories/CoreGameplaySystemsFactory.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"

class UCityGeneratorConfig;
class IServiceContainer;

class CreateHandStep : LoadSequenceStep
{
public:
	CreateHandStep(IServiceContainer* serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual UE5Coro::TCoroutine<> Execute() override
	{
		UWorld* viewWorld = ServiceContainer->Get<UWorld>();
		UGameplayAssetData* GameplayAssetData = ServiceContainer->Get<UGameplayAssetData>();
		ULocalConfigHolder* LocalConfigHolder = ServiceContainer->Get<ULocalConfigHolder>();
		BuildingService* buildingService = ServiceContainer->Get<BuildingService>();
		BuildingPrototypeService* buildingPrototypeService = ServiceContainer->Get<BuildingPrototypeService>();
		EventBus* eventBus = ServiceContainer->Get<EventBus>();
		

		APawn* PlayerPawn = viewWorld->GetFirstPlayerController()->GetPawnOrSpectator();
	
		AHand* Hand = viewWorld->SpawnActor<AHand>(GameplayAssetData->Hand, FVector::ZeroVector, FRotator::ZeroRotator);
		Hand->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		UCardFactory* CardFactory = NewObject<UCardFactory>();
		CardFactory->Construct(viewWorld, GameplayAssetData, buildingService, buildingPrototypeService, LocalConfigHolder);
	
		Hand->Construct(CardFactory, eventBus);
	
	
		Hand->DrawCard();

		
		ServiceContainer->Set<AHand>(Hand);
		
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
};

