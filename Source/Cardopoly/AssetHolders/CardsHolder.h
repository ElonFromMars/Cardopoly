// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardsHolder.generated.h"

class ACard;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API UCardsHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TSubclassOf<ACard>> CardByName;
};
