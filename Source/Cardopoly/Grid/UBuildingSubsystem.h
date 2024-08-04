// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGridSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "UBuildingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CARDOPOLY_API UBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	
	virtual void PostInitialize() override;
	void CreateBuildingUnderMouse();
	UFUNCTION(BlueprintCallable)
	void CreateBuilding(const FVector Position) const;

private:
	UPROPERTY()
	UGridSubsystem* GridSubsystem;
};
