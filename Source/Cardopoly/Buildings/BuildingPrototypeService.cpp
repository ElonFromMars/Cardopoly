#include "BuildingPrototypeService.h"

#include "Cardopoly/AssetHolders/GameplayAssetData.h"
#include "Cardopoly/AssetHolders/UMaterialsHolder.h"
#include "Cardopoly/Configs/EViewAssetType.h"
#include "Cardopoly/Grid/GridLayout.h"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Cardopoly/View/AEntityView.h"

void BuildingPrototypeService::ShowBuildingPrototype(const uint32 id)
{
	TSubclassOf<AEntityView> viewActorClass = _gameplayAssetData->GetEntityViewClass(EViewAssetType::Building, id);

	_prototypeView = _viewWorld->
		SpawnActor<AEntityView>(viewActorClass, FVector::ZeroVector,FRotator::ZeroRotator);

	auto MaterialInstance = _gameplayAssetData->MaterialsHolder->MaterialById[EMaterialIdConfig::BuildingPrototype];
	_prototypeView->MainMesh->SetMaterial(0, MaterialInstance);
}

void BuildingPrototypeService::UpdateBuildingPrototypePosition(const FVector2D screenPosition) const
{
	FIntVector cellPosition = FIntVector::ZeroValue;
	if (_positionConversionService->ScreenPointToGroundPosition(screenPosition, cellPosition))
	{
		FVector position = _gridLayout->GetCellCenterWorldPosition(cellPosition);
		_prototypeView->SetActorLocation(position);
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
