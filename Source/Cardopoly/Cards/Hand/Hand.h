// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hand.generated.h"

class UCardFactory;

UCLASS()
class CARDOPOLY_API AHand : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHand();
	void Init(UCardFactory* cardFactory);
	void DrawCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateSlotPositions();

private:
	UPROPERTY()
	UCardFactory* CardFactory;
	
	TArray<FVector> CardSlots;
	float DistanceBetweenCards = 100;
	FVector BottomCenterPosition = FVector(500, 0, -130);
};
