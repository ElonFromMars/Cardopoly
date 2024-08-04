// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/InputLocalConfig.h"
#include "Components/ActorComponent.h"
#include "TouchInputDispatcherComponent.generated.h"

struct FInputActionValue;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectTouchStartedSignature, AActor*, actor, FVector, location,
                                               FVector2D, screenPosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTouchTriggeredSignature, FVector, location, FVector2D, screenPosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTouchEndedSignature, FVector, location, FVector2D, screenPosition);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDOPOLY_API UTouchInputDispatcherComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnObjectTouchStartedSignature OnObjectTouchStartedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnTouchTriggeredSignature OnOnTouchTriggeredDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnTouchEndedSignature OnOnTouchEndedDelegate;
	
private:
	UPROPERTY()
	UInputLocalConfig* InputLocalConfig;
	UPROPERTY()
	UInputComponent* InputComponent;

public:
	UTouchInputDispatcherComponent();

	void Construct(UInputLocalConfig* InputLocalConfig);
	void SetupInputComponent(UInputComponent* InputComponent);
	FVector2D GetScreenPosition() const;

protected:
	void OnTouchStarted(const FInputActionValue& Value);
	void OnTouchTriggered(const FInputActionValue& Value);
	void OnTouchEnded(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	bool TryGetObjectUnderMouse(AActor*& HitActor, FVector& HitPosition) const;
};
