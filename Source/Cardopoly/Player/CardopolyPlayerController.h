// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/InputLocalConfig.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "GameFramework/PlayerController.h"
#include "CardopolyPlayerController.generated.h"

class UTouchInputDispatcherComponent;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API ACardopolyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UTouchInputDispatcherComponent* TouchInputDispatcherComponent;

public:
	ACardopolyPlayerController();
	
	void Construct(UInputLocalConfig* InputLocalConfig) const;

private:
	virtual void SetupInputComponent() override;
};
