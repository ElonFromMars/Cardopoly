﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "ARTSCamera.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CARDOPOLY_API ARTSCamera : public APawn
{
	GENERATED_BODY()

public:
	ARTSCamera();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void EnhancedMove(const FInputActionValue& Value);
	
	void EnhancedMouseClick(const FInputActionValue& Value);
	void SpawnBuilding(const FVector& SpawnLocation);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* RTSCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UInputAction* MouseClickInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UInputMappingContext* CameraMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraSpeedMultiplier = 100.0f;
	
	virtual void BeginPlay() override;
};