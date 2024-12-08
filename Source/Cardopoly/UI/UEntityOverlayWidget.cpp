#include "UEntityOverlayWidget.h"

#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"

void UEntityOverlayWidget::Construct(FEntityWrapper entity)
{
	_entity = entity;
}

void UEntityOverlayWidget::Close() const
{
	OnClose.ExecuteIfBound(_entity);
}
