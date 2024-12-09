#pragma once

#include "CoreMinimal.h"
#include "UBuildingsViewHolder.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Engine/DataAsset.h"
#include "GameplayAssetData.generated.h"

class UWidgetHolder;
class AEntityView;
class ATurnController;
class AHand;
class UCardsHolder;
class UMaterialsHolder;

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
	UMaterialsHolder* MaterialsHolder;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetHolder* WidgetHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHand> Hand;
};
