// Fill out your copyright notice in the Description page of Project Settings.

#include "ARTSCamera.h"

#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EventBus/EventBus.hpp"
#include "EventBus/Events/CreateCardEvent.h"
#include "EventBus/Events/DestroyCardEvent.h"


// Sets default values
ARTSCamera::ARTSCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RTSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RTSCamera"));
}

void ARTSCamera::Construct(EventBus* eventBus)
{
	m_eventBus = eventBus;
	m_eventBus->Subscribe<CreateCardEvent>(this, &ARTSCamera::CreateCardHandler);
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->bShowMouseCursor = true; 
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CameraMappingContext, 0);
		}
	}
}

void ARTSCamera::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	m_eventBus->Unsubscribe<CreateCardEvent>(this);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ARTSCamera::EnhancedMove);
	
	//enhancedInputComponent->BindAction(MouseClickInputAction, ETriggerEvent::Started, this, &ARTSCamera::EnhancedMouseClick);

	enhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Triggered, this,  &ARTSCamera::OnZoomInputTriggered);
}

void ARTSCamera::EnhancedMove(const FInputActionValue& Value)
{
	const FVector2D moveVector = Value.Get<FVector2D>();
	const FVector moveVector3d = FVector(moveVector.X, moveVector.Y, 0.0f);
	
	AddActorWorldOffset(moveVector3d * CameraSpeedMultiplier);
}

void ARTSCamera::OnZoomInputTriggered(const FInputActionValue& Value)//TODO move to separate input controller
{
	float ZoomValue = Value.Get<float>();
	Zoom(ZoomValue);
}

void ARTSCamera::Zoom(float Delta)
{
	FVector Location = GetActorLocation();
	FVector ForwardDirection = GetActorForwardVector();

	FVector NewLocation = Location + ForwardDirection * Delta * CameraZoomSpeedMultiplier;
	FVector ClampedLocation;
	if(NewLocation.Z < MinZPosition)
	{
		ClampedLocation = FMath::LinePlaneIntersection(Location, NewLocation, FVector(0, 0, MinZPosition), FVector::UpVector);	
	}
	else
	{
		ClampedLocation = NewLocation;
	}
	
	SetActorLocation(ClampedLocation);
}

void ARTSCamera::CreateCardHandler(CreateCardEvent createCardEvent) const
{
	auto sceneCapture2D = GetComponentByClass<USceneCaptureComponent2D>();
	sceneCapture2D->ShowOnlyActors.Add(reinterpret_cast<AActor*>(createCardEvent.Card));
}

void ARTSCamera::DestroyCardHandler(DestroyCardEvent destroyCardEvent) const
{
	auto sceneCapture2D = GetComponentByClass<USceneCaptureComponent2D>();
	sceneCapture2D->ShowOnlyActors.Remove(reinterpret_cast<AActor*>(destroyCardEvent.Card));
}
