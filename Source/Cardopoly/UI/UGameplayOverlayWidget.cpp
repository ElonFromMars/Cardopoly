#include "UGameplayOverlayWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"

void UGameplayOverlayWidget::Construct(
	PositionConversionService* positionConversionService
)
{
	_positionConversionService = positionConversionService;
}

void UGameplayOverlayWidget::AddWidgetForEntity(flecs::entity entity, UUserWidget* widget)
{
	FEntityOverlayContainer& container = GetContainerForEntity(entity);

	container.Widgets.push_back(widget);
	
	UPanelSlot* slot = Panel->AddChild(widget);

	SyncWidgetWithEntityPosition(entity, slot);
}

void UGameplayOverlayWidget::SyncWidgetWithEntityPosition(flecs::entity entity, UPanelSlot* slot)
{
	auto position = entity.get<FPositionComponent>()->Value;

	FVector2D screenPosition;
	if (_positionConversionService->PositionToScreenPoint(position, screenPosition))
	{
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(slot);
		if (CanvasSlot)
		{
			float ScaleFactor = UWidgetLayoutLibrary::GetViewportScale(this);
			FVector2D umgPosition = screenPosition / ScaleFactor;
			
			CanvasSlot->SetPosition(umgPosition);
		}
	}
}

FEntityOverlayContainer& UGameplayOverlayWidget::GetContainerForEntity(flecs::entity entity)
{
	if (!_widgetByEntity.contains(entity))
	{
		return _widgetByEntity.emplace(entity, FEntityOverlayContainer()).first->second;
	}
	else
	{
		return _widgetByEntity[entity];
	}
}
