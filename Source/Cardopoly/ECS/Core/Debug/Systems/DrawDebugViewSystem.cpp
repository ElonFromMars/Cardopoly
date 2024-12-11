#include "DrawDebugViewSystem.h"

#include "Cardopoly/ECS/Core/Citizens/Components/FCitizenTag.h"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"

void DrawDebugViewSystem::Initialize()
{
	_world->system<FPositionComponent>("DrawDebugViewSystem")
		.with<FCitizenTag>()
		.each([this](FPositionComponent& pos) {
			DrawDebugPoint(_viewWorld, FVector(pos.Value.X, pos.Value.Y, 10.0f), 10.0f, FColor::Red, false, 0.1f);
		});
}
