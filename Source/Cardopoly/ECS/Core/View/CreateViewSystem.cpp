#include "CreateViewSystem.h"

#include "FCreateViewRequest.hpp"
#include "FViewComponent.hpp"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Cardopoly/ECS/Core/Id/FIdComponent.hpp"
#include "Cardopoly/View/AEntityView.h"

void CreateViewSystem::Initialize()
{
	_world->system<FIdComponent>("CreateViewSystem")
		.with<FCreateViewRequest>()
		.each([this](flecs::entity entity, FIdComponent& id)
		{
			TSubclassOf<AEntityView> viewActorClass = _gameplayAssetData->GetEntityViewClass(
				EViewAssetType::Building, id.Value);

			AEntityView* view = _viewWorld->SpawnActor<AEntityView>(viewActorClass, FVector::ZeroVector,FRotator::ZeroRotator);
			
			entity.set<FViewComponent>({view});

			entity.remove<FCreateViewRequest>();
		});
}
