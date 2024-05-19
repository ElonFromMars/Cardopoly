// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UGridSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CARDOPOLY_API UGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	double CellSize;

	UPROPERTY(BlueprintReadOnly)
	double HalfCellSize;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UFUNCTION(BlueprintCallable)
	FIntVector WorldPositionToGrid(const FVector WorldPosition) const;

	UFUNCTION(BlueprintCallable)
	FVector GetCellCenterWorldPosition(const FIntVector GridPosition) const;

	UFUNCTION(BlueprintCallable)
	FVector GetClosestCellCenterWorldPosition(const FVector WorldPosition) const;
};
