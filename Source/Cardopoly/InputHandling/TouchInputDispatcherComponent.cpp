// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchInputDispatcherComponent.h"

#include "EnhancedInputComponent.h"


// Sets default values for this component's properties

UTouchInputDispatcherComponent::UTouchInputDispatcherComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTouchInputDispatcherComponent::Construct(UInputLocalConfig* inputLocalConfig)
{
	InputLocalConfig = inputLocalConfig;
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "InputLocalConfig initialization");

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Started, this, &UTouchInputDispatcherComponent::OnTouchStarted);

	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Triggered, this, &UTouchInputDispatcherComponent::OnTouchTriggered);
	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Canceled, this, &UTouchInputDispatcherComponent::OnTouchEnded);
	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Completed, this, &UTouchInputDispatcherComponent::OnTouchEnded);
}

void UTouchInputDispatcherComponent::SetupInputComponent(UInputComponent* inputComponent)
{
	InputComponent = inputComponent;
}

void UTouchInputDispatcherComponent::OnTouchStarted(const FInputActionValue& Value)
{
	AActor* HitActor = nullptr;
	FVector HitPosition;
	if(TryGetObjectUnderMouse(HitActor, HitPosition))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(HitActor->GetHumanReadableName()));
		
		FVector2D ScreenPosition = GetScreenPosition();
		OnObjectTouchStartedDelegate.Broadcast(HitActor, HitPosition, ScreenPosition);
	}
}

void UTouchInputDispatcherComponent::OnTouchTriggered(const FInputActionValue& Value)
{
	FVector2D ScreenPosition = GetScreenPosition();
	AActor* HitActor = nullptr;
	FVector HitPosition = FVector::Zero();

	TryGetObjectUnderMouse(HitActor, HitPosition);
	
	OnOnTouchTriggeredDelegate.Broadcast(HitPosition, ScreenPosition);
}

void UTouchInputDispatcherComponent::OnTouchEnded(const FInputActionValue& Value)
{
	FVector2D ScreenPosition = GetScreenPosition();
	AActor* HitActor = nullptr;
	FVector HitPosition = FVector::Zero();

	TryGetObjectUnderMouse(HitActor, HitPosition);
	
	OnOnTouchEndedDelegate.Broadcast(HitPosition, ScreenPosition);
}

void UTouchInputDispatcherComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTouchInputDispatcherComponent::TryGetObjectUnderMouse(AActor*& HitActor, FVector& HitPosition) const
{
	bool IsFound = false;
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FVector RayStart;
		FVector RayDirection;
		PlayerController->DeprojectMousePositionToWorld(RayStart, RayDirection); 
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f;//TODO add constant

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		UWorld* World = GetWorld();
		if (World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams)
			&&  HitResult.GetActor())
		{
			HitActor = HitResult.GetActor();
			HitPosition = HitResult.Location;
			
			IsFound = true;
		}
	}
	return IsFound;
}

FVector2D UTouchInputDispatcherComponent::GetScreenPosition() const
{
	float MouseX;
	float MouseY;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(MouseX, MouseY);
	return FVector2D(MouseX, MouseY);
}

