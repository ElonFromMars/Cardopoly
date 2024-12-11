#include "InitializeGridPositionSystem.h"

#include "FLocalOffsetComponent.hpp"
#include "FViewComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/View/AEntityView.h"

void InitializeGridPositionSystem::Initialize()
{
	_world->system<FViewComponent, FGridPositionComponent>("InitializeGridPositionSystem")
		.immediate()
		.each([this](flecs::entity entity, FViewComponent view, const FGridPositionComponent& position)
		{
			FVector offsetVector;
			if (entity.has<FLocalOffsetComponent>())
			{
				offsetVector = entity.get<FLocalOffsetComponent>()->Value;
			}
			const FVector cellWorldPosition = _gridLayout->GetCellCenterWorldPosition(position.Value) + offsetVector;
			entity.set<FPositionComponent>({cellWorldPosition});
			view.Value->SetActorLocation(cellWorldPosition);
		});
}
