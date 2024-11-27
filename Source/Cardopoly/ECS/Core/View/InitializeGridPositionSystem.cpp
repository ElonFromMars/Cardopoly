#include "InitializeGridPositionSystem.h"

#include "FViewComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/View/AEntityView.h"

void InitializeGridPositionSystem::Initialize()
{
	_world->system<FViewComponent, const FGridPositionComponent>("InitializeGridPositionSystem")
		.each([this](FViewComponent view, const FGridPositionComponent& position)
		{
			const FVector cellWorldPosition = _gridLayout->GetCellCenterWorldPosition(position.Value);
			view.Value->SetActorLocation(cellWorldPosition);
		});
}
