#include "BuildingPrototypeService.h"

#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Cardopoly/View/AEntityView.h"

void BuildingPrototypeService::CreateBuildingPrototype(const uint32 id) const
{
	TSubclassOf<AEntityView> viewActorClass = _gameplayAssetData->GetEntityViewClass(EViewAssetType::Building, id);

	AEntityView* view = _viewWorld->
		SpawnActor<AEntityView>(viewActorClass, FVector::ZeroVector,FRotator::ZeroRotator);
}
