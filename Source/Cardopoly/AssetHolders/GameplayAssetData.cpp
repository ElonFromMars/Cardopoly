#include "GameplayAssetData.h"

#include "Cardopoly/Buildings/ABuilding.h"
#include "Cardopoly/Configs/EViewAssetType.h"

TSubclassOf<AEntityView> UGameplayAssetData::GetEntityViewClass(EViewAssetType assetType, uint16 id) const
{
	switch (assetType)
	{
		case EViewAssetType::Building:
		{
			EBuildingViewIdConfig buildingId = static_cast<EBuildingViewIdConfig>(id);
			if (BuildingsViewHolder->BuildingsById.Contains(buildingId))
			{
				return BuildingsViewHolder->BuildingsById[buildingId];
			}
			break;
		}
	}
	return nullptr;
}
