#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UHUDWidget;

class HUDViewSystem : public IGameplaySystem
{
public:
	HUDViewSystem(flecs::world* flecsWorld, UHUDWidget* hudWidget)
		: IGameplaySystem(flecsWorld),
		_hudWidget(hudWidget)
	{
		
	}
	
	virtual void Initialize() override;

private:
	UHUDWidget* _hudWidget;
};
