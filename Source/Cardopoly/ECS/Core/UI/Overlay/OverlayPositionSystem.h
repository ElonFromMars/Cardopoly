#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGameplayOverlayWidget;

class OverlayPositionSystem : public IGameplaySystem
{
public:
	OverlayPositionSystem(
		flecs::world* flecsWorld,
		UGameplayOverlayWidget* entityOverlayWidget
		) : IGameplaySystem(flecsWorld),
		_entityOverlayWidget(entityOverlayWidget)
	{ }
	
	virtual void Initialize() override;

private:
	UGameplayOverlayWidget* _entityOverlayWidget;
};

