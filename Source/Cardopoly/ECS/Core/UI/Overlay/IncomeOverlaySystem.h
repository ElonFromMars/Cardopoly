#pragma once

#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class UGameplayAssetData;
class UGameplayOverlayWidget;

class IncomeOverlaySystem : public IGameplaySystem
{
public:
	IncomeOverlaySystem(
		flecs::world* flecsWorld,
		UGameplayAssetData* gameplayAssetData,
		UGameplayOverlayWidget* entityOverlayWidget
		) : IGameplaySystem(flecsWorld),
		_entityOverlayWidget(entityOverlayWidget),
		_gameplayAssetData(gameplayAssetData)
	{ }
	
	virtual void Initialize() override;

private:
	UGameplayOverlayWidget* _entityOverlayWidget;
	UGameplayAssetData* _gameplayAssetData;
};

