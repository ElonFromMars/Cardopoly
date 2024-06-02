#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UCityGeneratorConfig.generated.h"

class ABuilding;

UCLASS(BlueprintType)
class UCityGeneratorConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	uint8 GridSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	uint8 GridSizeY;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	float HouseProbability;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuilding> Building;
};
