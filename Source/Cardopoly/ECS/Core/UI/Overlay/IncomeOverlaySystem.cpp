#include "IncomeOverlaySystem.h"

#include "Blueprint/UserWidget.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/WidgetHolder.h"
#include "Cardopoly/Configs/UI/EWidgetIdConfig.h"
#include "Cardopoly/ECS/Core/Economy/FIncomeEvent.hpp"
#include "Cardopoly/UI/IncomeOverlayEffectWidget.h"
#include "Cardopoly/UI/UGameplayOverlayWidget.h"
#include "Components/PanelWidget.h"

class UIncomeOverlayEffectWidget;

void IncomeOverlaySystem::Initialize()
{
	_world->observer<FIncomeEvent>()
	.event<FIncomeEvent>()
	.each([this](flecs::entity e, FIncomeEvent& incomeEvent)
	{
		TSubclassOf<UUserWidget> incomeWidgetClass = _gameplayAssetData->WidgetHolder->BuildingsById[EWidgetIdConfig::IncomeEffect];

		UIncomeOverlayEffectWidget* incomeOverlay = CreateWidget<UIncomeOverlayEffectWidget>(_entityOverlayWidget->GetWorld(), incomeWidgetClass);
		if (incomeOverlay)
		{
			_entityOverlayWidget->Panel->AddChild(incomeOverlay);
			incomeOverlay->SetIncomeValue(incomeEvent.Value);
		}
	});
}
