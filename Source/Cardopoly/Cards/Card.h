﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FCEasing.h"
#include "flecs.h"
#include "UCardWidget.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

class PositionConversionService;
class ACard;
class BuildingService;
class FCTweenInstance;
class BuildingPrototypeService;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardAppliedSignature, ACard*, card);

UCLASS()
class CARDOPOLY_API ACard : public AActor
{
	GENERATED_BODY()

public:
	ACard();

	void Construct(
		BuildingService* buildingService,
		PositionConversionService* positionConversionService,
		BuildingPrototypeService* buildingPrototypeService,
		flecs::entity entity
	);

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool CanApply(FVector2D screenPosition);

	UFUNCTION(BlueprintCallable)
	void Apply(FVector2D screenPosition);

	UFUNCTION(BlueprintCallable)
	void ShowPrototype(FVector2D screenPosition);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePrototype(FVector2D screenPosition);

	UFUNCTION(BlueprintCallable)
	void HidePrototype();
	
	UFUNCTION(BlueprintCallable)
	void StopMovement();
	
	UFUNCTION(BlueprintCallable)
	void MoveToPosition(FVector Position, float Duration, EFCEase EaseType = EFCEase::Linear);

	UFUNCTION(BlueprintCallable)
	void MoveToLocalPosition(FVector LocalPosition, float Duration, EFCEase EaseType = EFCEase::Linear);

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetCardWidget()
	{
		return CardWidget;
	}

private:
	flecs::entity _entity;
	
	FCTweenInstance* Tween = nullptr;

	UPROPERTY()
	UCardWidget* CardWidget;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCardAppliedSignature OnCardAppliedDelegate;
	
private:
	BuildingPrototypeService* _buildingPrototypeService;
	BuildingService* _buildingsService;
	PositionConversionService* _positionConversionService;
};
