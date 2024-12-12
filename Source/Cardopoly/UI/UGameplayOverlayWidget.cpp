#include "UGameplayOverlayWidget.h"

#include "UEntityOverlayContainerWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/WidgetHolder.h"
#include "Cardopoly/Configs/UI/EWidgetIdConfig.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"

void UGameplayOverlayWidget::Construct(
	PositionConversionService* positionConversionService,
	UGameplayAssetData* gameplayAssetData
)
{
	_positionConversionService = positionConversionService;
	_gameplayAssetData = gameplayAssetData;
}

void UGameplayOverlayWidget::AddWidgetForEntity(flecs::entity entity, UUserWidget* widget)
{
	UEntityOverlayContainerWidget* container = GetContainerForEntity(entity);

	container->Widgets.Add(widget);
	container->Panel->AddChild(widget);
}

void UGameplayOverlayWidget::SyncWidgetsPositions()
{
	for (auto& [entity, widget] : _widgetByEntity)
	{
		SyncWidgetWithEntityPosition(entity, widget);
	}
}

void UGameplayOverlayWidget::SyncWidgetWithEntityPosition(flecs::entity entity, UUserWidget* widget)
{
	auto position = entity.get<FPositionComponent>()->Value;

	FVector2D screenPosition;
	if (_positionConversionService->PositionToScreenPoint(position, screenPosition))
	{
		UCanvasPanelSlot* canvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(widget);
		
		float scaleFactor = UWidgetLayoutLibrary::GetViewportScale(this);
		FVector2D umgPosition = screenPosition / scaleFactor;
			
		canvasSlot->SetPosition(umgPosition);
	}
}

UEntityOverlayContainerWidget* UGameplayOverlayWidget::GetContainerForEntity(flecs::entity entity)
{
	if (!_widgetByEntity.contains(entity))
	{
		TSubclassOf<UUserWidget> entityOverlayWidgetClass = _gameplayAssetData->WidgetHolder->BuildingsById[EWidgetIdConfig::EntityOverlay];

		UEntityOverlayContainerWidget* entityOverlay = CreateWidget<UEntityOverlayContainerWidget>(this, entityOverlayWidgetClass);
		entityOverlay->Construct(entity);
		Panel->AddChild(entityOverlay);
		
		return _widgetByEntity.emplace(entity, entityOverlay).first->second;
	}
	else
	{
		return _widgetByEntity[entity];
	}
}
