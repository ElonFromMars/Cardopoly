#pragma once

#include "flecs.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"
#include "Cardopoly/ECS/Infrastructure/Systems/IGameplaySystem.h"

class HandSystem : public IGameplaySystem
{
public:
	HandSystem(
		flecs::world* flecsWorld,
		ULocalConfigHolder* localConfigHolder
	)
		: IGameplaySystem(flecsWorld),
		_localConfigHolder(localConfigHolder)
	{
	}

	virtual void Initialize() override;

private:
	void DrawCard(flecs::entity playerEntity);

private:
	ULocalConfigHolder* _localConfigHolder;
};
