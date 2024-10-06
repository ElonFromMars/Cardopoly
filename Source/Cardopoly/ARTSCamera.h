// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EventBus/Events/CreateCardEvent.h"
#include "EventBus/Events/DestroyCardEvent.h"
#include "ARTSCamera.generated.h"

class EventBus;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CARDOPOLY_API ARTSCamera : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* RTSCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* MouseClickInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* ZoomInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputMappingContext* CameraMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraSpeedMultiplier = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraZoomSpeedMultiplier = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float MinZPosition = 1000.0f;

private:
	EventBus* m_eventBus;
	
public:
	ARTSCamera();

	void Construct(EventBus* eventBus);
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnhancedMove(const FInputActionValue& Value);

	void Zoom(float Delta);
	void CreateCardHandler(CreateCardEvent createCardEvent) const;
	void DestroyCardHandler(DestroyCardEvent destroyCardEvent) const;

private:
	void OnZoomInputTriggered(const FInputActionValue& Value);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
