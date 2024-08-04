// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandAnimationComponent.generated.h"


class ACard;
class AHand;

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class CARDOPOLY_API UHandAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	AHand* Hand;

public:
	// Sets default values for this component's properties
	UHandAnimationComponent();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDrawCard(ACard* card);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
