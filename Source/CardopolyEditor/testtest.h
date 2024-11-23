#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Grid/FBuildingGridData.h"
#include "Engine/DataAsset.h"
#include "testtest.generated.h"


UCLASS()
class CARDOPOLYEDITOR_API UTestAs : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FBuildingGridData GridData;
};
