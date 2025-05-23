﻿#include "HUDViewSystem.h"

#include "Cardopoly/ECS/Core/Economy/FMoneyComponent.hpp"
#include "Cardopoly/UI/UHUDWidget.h"

void HUDViewSystem::Initialize()
{
	_hudWidget->Construct(_world);
	_world->system<FMoneyComponent>("HUDViewSystem")
		.each([this](FMoneyComponent& money) {
			_hudWidget->SetMoney(money.Value);
		});
}
