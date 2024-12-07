#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UGameplayOverlayWidget.generated.h"

class UEntityOverlayWidget;

UCLASS()
class CARDOPOLY_API UGameplayOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<FEntityWrapper, UEntityOverlayWidget*> _entityToWidgetMap;
};
