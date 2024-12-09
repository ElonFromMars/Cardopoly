#pragma once

#include <map>
#include "CoreMinimal.h"
#include "FEntityOverlayContainer.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UGameplayOverlayWidget.generated.h"

class UEntityOverlayWidget;

UCLASS()
class CARDOPOLY_API UGameplayOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddWidgetForEntity(flecs::entity entity, UEntityOverlayWidget* widget);

public:
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* Panel;
	
private:
	std::map<flecs::entity, FEntityOverlayContainer> _widgetByEntity;
};
