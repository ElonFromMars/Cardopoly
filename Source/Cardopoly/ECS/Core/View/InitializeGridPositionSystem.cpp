#include "InitializeGridPositionSystem.h"

#include "FCreateViewRequest.hpp"
#include "FLocalOffsetComponent.hpp"
#include "FViewComponent.hpp"
#include "Cardopoly/ECS/Core/Grid/Components/FGridPositionComponent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/View/AEntityView.h"

void InitializeGridPositionSystem::Initialize()
{
	_world->system<FGridPositionComponent>("InitializeGridPositionSystem")
		.with<FCreateViewRequest>()
		.each([this](flecs::entity entity, const FGridPositionComponent& position)
		{
			auto view = entity.get<FViewComponent>();
			FVector offsetVector;
			if (entity.has<FLocalOffsetComponent>())
			{
				offsetVector = entity.get<FLocalOffsetComponent>()->Value;
			}
			const FVector cellWorldPosition = _gridLayout->GetCellCenterWorldPosition(position.Value) + offsetVector;
			entity.set<FPositionComponent>({cellWorldPosition});
			view->Value->SetActorLocation(cellWorldPosition);

			UE_LOG(LogTemp, Warning, TEXT("InitializeGridPositionSystem_________Current frame: %llu"), GFrameCounter);
		});
}
