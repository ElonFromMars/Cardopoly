#include "GridObjectComponent.h"

void UGridObjectComponent::SetPosition(FIntVector position)
{
	m_position = position;
}

FIntVector UGridObjectComponent::GetPosition()
{
	return m_position;
}

IOccupyGridData* UGridObjectComponent::GetGridData()
{
	return nullptr;//TODO ASAP
}
