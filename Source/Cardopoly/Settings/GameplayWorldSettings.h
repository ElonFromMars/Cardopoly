// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWorldSettings.h"
#include "GameplayWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class CARDOPOLY_API UGameplayWorldSettings : public UBaseWorldSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double CellSize;
};
