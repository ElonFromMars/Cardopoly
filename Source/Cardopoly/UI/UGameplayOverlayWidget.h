#pragma once

#include <map>
#include "CoreMinimal.h"
#include "FEntityOverlayContainer.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UGameplayOverlayWidget.generated.h"

class PositionConversionService;
class UEntityOverlayWidget;

UCLASS()
class CARDOPOLY_API UGameplayOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Construct(PositionConversionService* positionConversionService);
	void AddWidgetForEntity(flecs::entity entity, UUserWidget* widget);
	void SyncWidgetWithEntityPosition(flecs::entity, UPanelSlot* slot);
	FEntityOverlayContainer& GetContainerForEntity(flecs::entity);

public:
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* Panel;
	PositionConversionService* _positionConversionService;

private:
	std::map<flecs::entity, FEntityOverlayContainer> _widgetByEntity;
};
