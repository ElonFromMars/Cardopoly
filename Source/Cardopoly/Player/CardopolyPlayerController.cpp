// Fill out your copyright notice in the Description page of Project Settings.


#include "CardopolyPlayerController.h"

#include "Cardopoly/InputHandling/TouchInputDispatcherComponent.h"

ACardopolyPlayerController::ACardopolyPlayerController()
{
	// Create the component
	TouchInputDispatcherComponent = CreateDefaultSubobject<
		UTouchInputDispatcherComponent>(TEXT("Touch Input Dispatcher Component"));
}

void ACardopolyPlayerController::Construct(UInputLocalConfig* InputLocalConfig) const
{
	TouchInputDispatcherComponent->Construct(InputLocalConfig);
}

void ACardopolyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	TouchInputDispatcherComponent->SetupInputComponent(InputComponent);
}
