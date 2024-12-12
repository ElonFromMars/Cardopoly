#include "UEntityOverlayContainerWidget.h"

#include "Cardopoly/ECS/Infrastructure/Extensions/FEntityWrapper.h"

void UEntityOverlayContainerWidget::Construct(FEntityWrapper entity)
{
	_entity = entity;
}

void UEntityOverlayContainerWidget::Close() const
{
	OnClose.ExecuteIfBound(_entity);
}
