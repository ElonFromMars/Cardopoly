﻿#include "HUDViewSystem.h"

#include "Cardopoly/ECS/Core/Player/Resources/FMoneyComponent.hpp"
#include "Cardopoly/UI/UHUDWidget.h"

void HUDViewSystem::Initialize()
{
	_world->system<FMoneyComponent>("HUDViewSystem")
		.each([this](FMoneyComponent& money) {
			_hudWidget->SetMoney(money.Value);
		});
}