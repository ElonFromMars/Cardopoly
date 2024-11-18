#include "HandUISystem.h"

#include "Cardopoly/Cards/Hand/Hand.h"
#include "Cardopoly/Configs/HandLocalConfig.h"
#include "Cardopoly/ECS/Core/Cards/FDrawCardRequest.hpp"

void HandUISystem::Initialize()
{
	for (int i = 0; i < _handLocalConfig->CardsStartCount; ++i)
	{
		_hand->DrawCard();	
	}
	
	_world->system<const FDrawCardRequest>("HandUISystem")
		.each([this](flecs::entity entity, const FDrawCardRequest& request)
		{
			_hand->DrawCard();
			entity.destruct();
		});
}
