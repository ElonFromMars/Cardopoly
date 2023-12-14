// Fill out your copyright notice in the Description page of Project Settings.

#include "ARTSCamera.h"

#include "ABuildingActor.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ARTSCamera::ARTSCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RTSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RTSCamera"));
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
	
	enhancedInputComponent->BindAction(MouseClickInputAction, ETriggerEvent::Started, this, &ARTSCamera::EnhancedMouseClick);
}

void ARTSCamera::EnhancedMove(const FInputActionValue& Value)
{
	const FVector2D moveVector = Value.Get<FVector2D>();
	const FVector moveVector3d = FVector(moveVector.X, moveVector.Y, 0.0f);
	
	AddActorWorldOffset(moveVector3d * CameraSpeedMultiplier);
}

void ARTSCamera::EnhancedMouseClick(const FInputActionValue& Value)
{
	UCameraComponent* Camera = FindComponentByClass<UCameraComponent>();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(Camera && PlayerController)
	{
		/*float mouseX;
		float mouseY;
		PlayerController->GetMousePosition(mouseX, mouseY);

		FVector2D MouseScreenPos = FVector2D(mouseX, mouseY);

		int32 ViewportSizeX, ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

		FVector2D ViewportSize = FVector2D(ViewportSizeX, ViewportSizeY);

		FVector2D NormalizedCoords = MouseScreenPos / ViewportSize * 2.0f - FVector2D(1.0f, 1.0f);
		NormalizedCoords.Y *= -1.0f;
		FVector RayStart = Camera->GetComponentLocation();
		FVector RayDirection = Camera->GetForwardVector() + NormalizedCoords.X * Camera->GetRightVector() + NormalizedCoords.Y * Camera->GetUpVector();
		*/
		FVector RayStart;
		FVector RayDirection;
		
		PlayerController->DeprojectMousePositionToWorld(RayStart, RayDirection); 
		
		// Create ray origin and direction
		
		RayDirection.Normalize();
		
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		// Cast the ray and check for hits
		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams))
		{
			// An object was hit, you can perform actions based on the hit result
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetHumanReadableName());
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.Location.ToString());

			SpawnBuilding(HitResult.Location);
		}
	}
}

void ARTSCamera::SpawnBuilding(const FVector& SpawnLocation)
{
	FRotator SpawnRotation = FRotator::ZeroRotator; // Set the spawn rotation

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABuildingActor>(ABuildingActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
}
