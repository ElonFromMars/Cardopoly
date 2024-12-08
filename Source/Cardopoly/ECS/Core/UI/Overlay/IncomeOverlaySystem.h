#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGameplayOverlayWidget;

class IncomeOverlaySystem : public IGameplaySystem
{
public:
	IncomeOverlaySystem(
		flecs::world* flecsWorld,
		UGameplayOverlayWidget* entityOverlayWidget
		) : IGameplaySystem(flecsWorld),
		_entityOverlayWidget(entityOverlayWidget)
	{ }
	
	virtual void Initialize() override;

private:
	UGameplayOverlayWidget* _entityOverlayWidget;
};

