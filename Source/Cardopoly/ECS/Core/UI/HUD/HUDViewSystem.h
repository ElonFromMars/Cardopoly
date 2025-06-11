#pragma once

#include "Cardopoly/ECS/Core/Player/Common/Services/LocalPlayerService.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UHUDWidget;

class HUDViewSystem : public IGameplaySystem
{
public:
	HUDViewSystem(
		flecs::world* flecsWorld,
		UHUDWidget* hudWidget,
		LocalPlayerService* localPlayerService
		) : IGameplaySystem(flecsWorld),
		_hudWidget(hudWidget),
		_localPlayerService(localPlayerService)
	{ }
	
	virtual void Initialize() override;

private:
	UHUDWidget* _hudWidget;
	LocalPlayerService* _localPlayerService;
};
