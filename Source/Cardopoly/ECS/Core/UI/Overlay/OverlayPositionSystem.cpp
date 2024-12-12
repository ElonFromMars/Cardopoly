#include "OverlayPositionSystem.h"
#include "Cardopoly/UI/UGameplayOverlayWidget.h"

void OverlayPositionSystem::Initialize()
{
	_world->system()
		.kind(flecs::OnUpdate)
		.each([this]() {
			_entityOverlayWidget->SyncWidgetsPositions();
		});
}
