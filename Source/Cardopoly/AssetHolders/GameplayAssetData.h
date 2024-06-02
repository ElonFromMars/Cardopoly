// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAssetData.generated.h"

class UCardsHolder;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API UGameplayAssetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCardsHolder* CardsHolder;
};
