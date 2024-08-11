// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

class ACard;
class ABuildingsController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardAppliedSignature, ACard*, card);

UCLASS()
class CARDOPOLY_API ACard : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCardAppliedSignature OnCardAppliedDelegate;
	
private:
	UPROPERTY()
	ABuildingsController* BuildingsController;
	
public:
	ACard();

	void Construct(ABuildingsController* BuildingsController);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool CanApply(FVector2D ScreenPosition);

	UFUNCTION(BlueprintCallable)
	void Apply(FVector2D ScreenPosition);
};
