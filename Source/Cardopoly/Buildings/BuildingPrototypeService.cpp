#include "BuildingPrototypeService.h"

#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/UMaterialsHolder.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Cardopoly/Configs/Buildings/GridObjectsDataProvider.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Cardopoly/View/AEntityView.h"

void BuildingPrototypeService::ShowBuildingPrototype(const uint32 id)
{
	_prototypeId = id;
	
	TSubclassOf<AEntityView> viewActorClass = _gameplayAssetData->GetEntityViewClass(EViewAssetType::Building, id);

	_prototypeView = _viewWorld->
		SpawnActor<AEntityView>(viewActorClass, FVector::ZeroVector,FRotator::ZeroRotator);

	UMaterialInstance* material = _gameplayAssetData->
		MaterialsHolder->MaterialById[EMaterialIdConfig::BuildingPrototype];

	for (const auto meshComponentIt : _prototypeView->GetMeshComponents())
	{
		meshComponentIt->SetMaterial(0, material);	
	}
}

void BuildingPrototypeService::UpdateBuildingPrototypePosition(const FVector2D screenPosition) const
{
	FIntVector cellPosition = FIntVector::ZeroValue;
	if (_positionConversionService->ScreenPointToGroundPosition(screenPosition, cellPosition))
	{
		FVector centerOffset = _gridObjectsDataProvider->GetCenterOffset(_prototypeId);
		FVector position = _gridLayout->GetCellCenterWorldPosition(cellPosition);
		_prototypeView->SetActorLocation(position + centerOffset);
	}
}

void BuildingPrototypeService::HideBuildingPrototype()
{
	if (_prototypeView)
	{
		_prototypeView->Destroy();
		_prototypeView = nullptr;
	}
}
