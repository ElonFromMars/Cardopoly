#include "CardConfigService.h"

#include "AbilityCardDataRaw.h"
#include "BuildingCardDataRaw.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"

TArray<FName> _cachedCardNames;

TArray<FName> CardConfigService::GetAllNames() const
{
	if (_cachedCardNames.Num() == 0)
	{
		_cachedCardNames.Append(_localConfigHolder->BuildingCardsConfig->GetRowNames());
		_cachedCardNames.Append(_localConfigHolder->AbilityCardsConfig->GetRowNames());
	}

	return _cachedCardNames;
}

BaseCardData CardConfigService::GetBaseCardData(FName cardId) const
{
	BaseCardData baseCardData;
	baseCardData.Id = cardId;

	if (auto buildingCardData = GetCardData<FBuildingCardDataRaw>(cardId))
	{
		baseCardData.Name = buildingCardData->Name;
		baseCardData.Description = buildingCardData->Description;
		baseCardData.Cost = buildingCardData->Cost;
		baseCardData.Type = ECardType::Building;
	}
	else if (auto abilityCardData = GetCardData<FAbilityCardDataRaw>(cardId))
	{
		baseCardData.Name = abilityCardData->Name;
		baseCardData.Description = abilityCardData->Description;
		baseCardData.Cost = abilityCardData->Cost;
		baseCardData.Type = ECardType::Ability;
	}

	return baseCardData;
}
