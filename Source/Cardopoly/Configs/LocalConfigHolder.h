// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocalConfigHolder.generated.h"

class UInputLocalConfig;
class UHandLocalConfig;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API ULocalConfigHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHandLocalConfig* HandLocalConfig;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputLocalConfig* InputLocalConfig;
};
