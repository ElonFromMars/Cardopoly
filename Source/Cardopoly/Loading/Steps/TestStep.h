#pragma once

#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Cardopoly/Infrastructure/Loading/LoadSequenceStep.h"
#include "Kismet/KismetMathLibrary.h"


class IServiceContainer;

class TestStep : LoadSequenceStep
{
public:
	TestStep(IServiceContainer* serviceContainer)
		: LoadSequenceStep(serviceContainer)
	{
		
	}
	
	virtual UE5Coro::TCoroutine<> Execute() override
	{
		ULocalConfigHolder* config = ServiceContainer->Get<ULocalConfigHolder>();

		TArray<FName> RowNames = config->BuildingCardsConfig->GetRowNames();
		int32 RandomIndex = UKismetMathLibrary::RandomInteger(RowNames.Num());
		FName RandomRowName = RowNames[RandomIndex];

	
		FString ContextString = "houses query";
		FBuildingCardDataRaw* CardData = config->BuildingCardsConfig->FindRow<FBuildingCardDataRaw>(RandomRowName, ContextString);
		
		UE_LOG(LogTemp, Error, TEXT("%s"), *CardData->Name.ToString());
		
		return UE5Coro::TCoroutine<>::CompletedCoroutine;
	}
};
