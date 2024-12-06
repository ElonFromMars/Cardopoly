#include "BuildingPrototypeService.h"

#include "BuildingService.h"
#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/UMaterialsHolder.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Cardopoly/Configs/Buildings/GridObjectsDataProvider.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Cardopoly/View/AEntityView.h"

void BuildingPrototypeService::ShowBuildingPrototype(const uint32 id, const FVector2D screenPosition)
{
	FIntVector cellPosition = FIntVector::ZeroValue;
	if (!_positionConversionService->ScreenPointToGroundPosition(screenPosition, cellPosition))
	{
		return;
	}
	
	_prototypeId = id;
	
	TSubclassOf<AEntityView> viewActorClass = _gameplayAssetData->GetEntityViewClass(EViewAssetType::Building, id);

	_prototypeView = _viewWorld->
		SpawnActor<AEntityView>(viewActorClass, FVector::ZeroVector,FRotator::ZeroRotator);

	_isBlocked = _buildingService->IsBuildingOverlaps(cellPosition, id);
	UpdatePrototypeMaterials(_isBlocked);
}

void BuildingPrototypeService::UpdateBuildingPrototypePosition(const FVector2D screenPosition)
{
	FIntVector cellPosition = FIntVector::ZeroValue;
	if (!_positionConversionService->ScreenPointToGroundPosition(screenPosition, cellPosition))
	{
		return;
	}
	
	FVector centerOffset = _gridObjectsDataProvider->GetCenterOffset(_prototypeId);
	FVector position = _gridLayout->GetCellCenterWorldPosition(cellPosition);
	_prototypeView->SetActorLocation(position + centerOffset);

	bool updatedIsBlocked = _buildingService->IsBuildingOverlaps(cellPosition, _prototypeId);
	if (updatedIsBlocked != _isBlocked)
	{
		UpdatePrototypeMaterials(updatedIsBlocked);
		_isBlocked = updatedIsBlocked;
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

void BuildingPrototypeService::UpdatePrototypeMaterials(bool isBlocked) const
{
	if (!_prototypeView)
	{
		return;
	}

	EMaterialIdConfig materialIdConfig;
	if (isBlocked)
	{
		materialIdConfig = EMaterialIdConfig::BlockedBuildingPrototype;
	}
	else
	{
		materialIdConfig = EMaterialIdConfig::BuildingPrototype;
	}
	UMaterialInstance* material = _gameplayAssetData->MaterialsHolder->MaterialById[materialIdConfig];

	for (const auto meshComponentIt : _prototypeView->GetMeshComponents())
	{
		meshComponentIt->SetMaterial(0, material);	
	}
}
