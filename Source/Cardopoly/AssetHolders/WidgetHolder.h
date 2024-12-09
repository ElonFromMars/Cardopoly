#pragma once

#include "CoreMinimal.h"
#include "Cardopoly/Configs/UI/EWidgetIdConfig.h"
#include "Engine/DataAsset.h"
#include "WidgetHolder.generated.h"

UCLASS()
class CARDOPOLY_API UWidgetHolder : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<EWidgetIdConfig, TSubclassOf<UUserWidget>> BuildingsById;
};
