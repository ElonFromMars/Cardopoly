#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UEntityOverlayContainerWidget.generated.h"

class UEntityOverlayWidget;
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
	TArray<UEntityOverlayWidget*> Widgets;
	
private:
	FEntityWrapper _entity;
};
