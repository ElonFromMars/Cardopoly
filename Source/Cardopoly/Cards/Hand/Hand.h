﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Cards/Card.h"
#include "Cardopoly/EventBus/EventBus.hpp"
#include "GameFramework/Actor.h"
#include "Hand.generated.h"

class ACard;
class UCardFactory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrawCardSignature, ACard*, card);

UCLASS()
class CARDOPOLY_API AHand : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UCardFactory* CardFactory;
	
	EventBus* _eventBus;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDrawCardSignature OnDrawCardDelegate;
	
	AHand();
	void Construct(UCardFactory* cardFactory, EventBus* eventBus);
	void DrawCard(flecs::entity entity);

	UFUNCTION(BlueprintCallable)
	TArray<ACard*> GetCards() const;

protected:
	virtual void BeginPlay() override;

private:
	TArray<FVector> CardSlots;
	float DistanceBetweenCards = 100;
	FVector BottomCenterPosition = FVector(500, 0, -130);

	UPROPERTY(BlueprintGetter=GetCards, VisibleInstanceOnly)
	TArray<ACard*> Cards;

	UFUNCTION()
	void OnCardApplied(ACard* Card);
};
