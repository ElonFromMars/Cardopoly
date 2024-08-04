// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputLocalConfig.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API UInputLocalConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Touches")
	UInputAction* BeginTouchInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Touches")
	UInputAction* MoveTouchInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Touches")
	UInputAction* EndTouchInputAction;
};
