// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/InputLocalConfig.h"
#include "Cardopoly/Player/CardopolyPlayerController.h"
#include "Components/ActorComponent.h"
#include "TouchInputDispatcherComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDOPOLY_API UTouchInputDispatcherComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UInputLocalConfig* InputLocalConfig;
	UPROPERTY()
	UInputComponent* InputComponent;

public:
	UTouchInputDispatcherComponent();

	void Construct(UInputLocalConfig* InputLocalConfig);
	void SetupInputComponent(UInputComponent* InputComponent);

protected:
	void BeginTouch();
	void TouchTriggered();
	void EndTouch();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
};
