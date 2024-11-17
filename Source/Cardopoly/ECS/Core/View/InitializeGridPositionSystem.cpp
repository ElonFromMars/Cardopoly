#include "InitializeGridPositionSystem.h"

#include "FViewComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/Grid/UGridSubsystem.h"
#include "Cardopoly/View/AEntityView.h"

void InitializeGridPositionSystem::Initialize()
{
	_world->system<FViewComponent, const FGridPositionComponent>("InitializeGridPositionSystem")
		.each([this](FViewComponent view, const FGridPositionComponent& position)
		{
			const FVector cellWorldPosition = _gridSubsystem->GetCellCenterWorldPosition(position.Value);
			view.Value->SetActorLocation(cellWorldPosition);
		});
}
