#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntityOverlayWidget.generated.h"


UCLASS()
class CARDOPOLY_API UEntityOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void BeginAnimation();
};
