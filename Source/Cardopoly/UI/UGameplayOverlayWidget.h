#pragma once

#include <map>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"
#include "UGameplayOverlayWidget.generated.h"

class UGameplayAssetData;
class PositionConversionService;
class UEntityOverlayContainerWidget;

UCLASS()
class CARDOPOLY_API UGameplayOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Construct(
		PositionConversionService* positionConversionService,
		UGameplayAssetData* gameplayAssetData
		);
	
	void AddWidgetForEntity(flecs::entity entity, UUserWidget* widget);
	void SyncWidgetsPositions();
	void SyncWidgetWithEntityPosition(flecs::entity, UUserWidget* widget);
	UEntityOverlayContainerWidget* GetContainerForEntity(flecs::entity);

public:
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* Panel;
	
	PositionConversionService* _positionConversionService;

private:
	std::map<flecs::entity, UEntityOverlayContainerWidget*> _widgetByEntity;
	UGameplayAssetData* _gameplayAssetData;
};
