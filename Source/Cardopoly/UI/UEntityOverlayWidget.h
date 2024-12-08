#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UEntityOverlayWidget.generated.h"

struct FEntityWrapper;

DECLARE_DELEGATE_OneParam(FOnCloseDelegate, FEntityWrapper);

UCLASS()
class CARDOPOLY_API UEntityOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnCloseDelegate OnClose;
	
	void Construct(FEntityWrapper entity);
	
	void Close() const;

private:
	FEntityWrapper _entity;
};
