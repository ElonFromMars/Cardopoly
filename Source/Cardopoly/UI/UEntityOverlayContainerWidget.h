#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UEntityOverlayContainerWidget.generated.h"

struct FEntityWrapper;

DECLARE_DELEGATE_OneParam(FOnCloseDelegate, FEntityWrapper);

UCLASS()
class CARDOPOLY_API UEntityOverlayContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnCloseDelegate OnClose;
	
	void Construct(FEntityWrapper entity);
	
	void Close() const;

public:
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* Panel;
	
	UPROPERTY()
	TArray<UUserWidget*> Widgets;
	
private:
	FEntityWrapper _entity;
};
