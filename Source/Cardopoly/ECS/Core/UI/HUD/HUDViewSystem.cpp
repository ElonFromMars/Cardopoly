#include "HUDViewSystem.h"

#include "Cardopoly/ECS/Core/Economy/FMoneyComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/UI/UHUDWidget.h"

void HUDViewSystem::Initialize()
{
	_hudWidget->Construct(_world);
	_world->system<FMoneyComponent, const PlayerIndexComponent>("HUDViewSystem")
		.each([this](FMoneyComponent& money, const PlayerIndexComponent& playerIndex) {
			if (_localPlayerService->GetLocalPlayerIndex() != playerIndex.Value)
			{
				return;
			}
			_hudWidget->SetMoney(money.Value);
		});
}
