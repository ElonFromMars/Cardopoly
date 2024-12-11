#include "IncomeOverlaySystem.h"

#include "Blueprint/UserWidget.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/WidgetHolder.h"
#include "Cardopoly/Configs/UI/EWidgetIdConfig.h"
#include "Cardopoly/ECS/Core/Economy/FIncomeEvent.hpp"
#include "Cardopoly/ECS/Core/Movement/Components/FPositionComponent.h"
#include "Cardopoly/UI/IncomeOverlayEffectWidget.h"
#include "Cardopoly/UI/UGameplayOverlayWidget.h"

class UIncomeOverlayEffectWidget;

void IncomeOverlaySystem::Initialize()
{
	_world->observer<FIncomeEvent>()
			.event(flecs::OnSet)
			.each([this](flecs::entity e, const FIncomeEvent& incomeEvent)
			{
				if (!e.has<FPositionComponent>())
				{
					return;
				}
				TSubclassOf<UUserWidget> incomeWidgetClass = _gameplayAssetData->WidgetHolder->BuildingsById[EWidgetIdConfig::IncomeEffect];

				UIncomeOverlayEffectWidget* incomeOverlay = CreateWidget<UIncomeOverlayEffectWidget>(_entityOverlayWidget->GetWorld(), incomeWidgetClass);
				_entityOverlayWidget->AddWidgetForEntity(e, incomeOverlay);
				
				incomeOverlay->SetIncomeValue(incomeEvent.Value);
			});
}
