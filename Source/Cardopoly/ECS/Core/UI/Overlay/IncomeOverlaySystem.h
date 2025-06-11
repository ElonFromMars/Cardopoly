#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class LocalPlayerService;
class UGameplayAssetData;
class UGameplayOverlayWidget;

class IncomeOverlaySystem : public IGameplaySystem
{
public:
	IncomeOverlaySystem(
		flecs::world* flecsWorld,
		UGameplayAssetData* gameplayAssetData,
		UGameplayOverlayWidget* entityOverlayWidget,
		LocalPlayerService* localPlayerService
		) : IGameplaySystem(flecsWorld),
		_entityOverlayWidget(entityOverlayWidget),
		_gameplayAssetData(gameplayAssetData),
		_localPlayerService(localPlayerService)
	{ }
	
	virtual void Initialize() override;

private:
	UGameplayOverlayWidget* _entityOverlayWidget;
	UGameplayAssetData* _gameplayAssetData;
	LocalPlayerService* _localPlayerService;
};

