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
	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Started, this, &UTouchInputDispatcherComponent::BeginTouch);

	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Triggered, this, &UTouchInputDispatcherComponent::TouchTriggered);
	EnhancedInputComponent->BindAction(InputLocalConfig->BeginTouchInputAction, ETriggerEvent::Completed, this, &UTouchInputDispatcherComponent::EndTouch);
}

void UTouchInputDispatcherComponent::SetupInputComponent(UInputComponent* inputComponent)
{
	InputComponent = inputComponent;
}

void UTouchInputDispatcherComponent::BeginTouch()
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "Begin Touch");
}

void UTouchInputDispatcherComponent::TouchTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "Touch Triggered");
}

void UTouchInputDispatcherComponent::EndTouch()
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "End Touch");
}

// Called every frame
void UTouchInputDispatcherComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTouchInputDispatcherComponent::TryGetObjectUnderMouse(UObject* result, )
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		FVector RayStart;
		FVector RayDirection;
		PlayerController->DeprojectMousePositionToWorld(RayStart, RayDirection); 
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		UWorld* World = GetWorld();
		if (World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams))
		{
			
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetHumanReadableName());
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.Location.ToString());


			UBuildingSubsystem* buildingSubsystem = World->GetSubsystem<UBuildingSubsystem>();
			buildingSubsystem->CreateBuilding(HitResult.Location);
		}
	}
}

