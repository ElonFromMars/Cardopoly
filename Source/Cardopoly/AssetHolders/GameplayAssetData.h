// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UBuildingsViewHolder.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Engine/DataAsset.h"
#include "GameplayAssetData.generated.h"

class AEntityView;
class ATurnController;
class AHand;
class UCardsHolder;
class UMaterialsHolder;
/**
 * 
 */
UCLASS()
class CARDOPOLY_API UGameplayAssetData : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<AEntityView> GetEntityViewClass(EViewAssetType assetType, uint16 id) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCardsHolder* CardsHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBuildingsViewHolder* BuildingsViewHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialsHolder* MaterialsViewHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHand> Hand;
};
