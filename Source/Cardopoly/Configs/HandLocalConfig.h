// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HandLocalConfig.generated.h"

/**
 * 
 */
UCLASS()
class CARDOPOLY_API UHandLocalConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 CardsStartCount;
};
