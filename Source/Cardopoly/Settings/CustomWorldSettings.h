// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayWorldSettings.h"
#include "GameFramework/WorldSettings.h"
#include "CustomWorldSettings.generated.h"

class UGameplayWorldSettings;
class UBaseWorldSettings;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API ACustomWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Instanced, EditAnywhere)
	UBaseWorldSettings* LevelSpecificSettings;

	static UGameplayWorldSettings* GetGameplayWorldSettings(const UWorld& InWorld);
};
