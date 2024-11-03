#include "CitizensInitializeSystem.h"

#include "Cardopoly/ECS/Core/Citizens/Components/FCitizenTag.h"
#include "Cardopoly/ECS/Core/Movement/Components/FGridPositionComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FMaxSpeedComponent.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/ECS/Core/Pathfinding/Components/FSearchPathRequest.h"

void CitizensInitializeSystem::Initialize()
{
	for (int i = 0; i < 100; ++i) {
		auto gridPosition = FIntVector
		{
			FMath::RandRange(-10, 10),
			FMath::RandRange(-10, 10),
			0
		};
		auto worldPosition = _gridSubsystem->GetCellCenterWorldPosition(gridPosition);
		_world->entity()
			.add<FCitizenTag>()
			.add<FSearchPathRequest>()
			.set<FGridPositionComponent>({
				gridPosition
			})
			.set<FPositionComponent>({
				worldPosition
			})
			.set<FMaxSpeedComponent>({
				FMath::RandRange(50.0f, 300.0f)
			});
	}
}
