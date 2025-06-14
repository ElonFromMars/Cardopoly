#pragma once

#include "BaseCardData.h"
#include "Cardopoly/Configs/LocalConfigHolder.h"

class CardConfigService
{
public:
	CardConfigService(ULocalConfigHolder* localConfigHolder)
		: _localConfigHolder(localConfigHolder)
	{ }

	TArray<FName> GetAllNames() const;

	template<typename T>
	T* GetCardData(FName cardId) const
	{
		if (_localConfigHolder->BuildingCardsConfig->RowStruct->IsChildOf(T::StaticStruct()))
		{
			return _localConfigHolder->BuildingCardsConfig->FindRow<T>(cardId, TEXT("CardConfigService::GetCardData"), false);
		}
		else if (_localConfigHolder->AbilityCardsConfig->RowStruct->IsChildOf(T::StaticStruct()))
		{
			return _localConfigHolder->AbilityCardsConfig->FindRow<T>(cardId, TEXT("CardConfigService::GetCardData"), false);
		}

		return nullptr;
	}

	BaseCardData GetBaseCardData(FName cardId) const;

private:
	ULocalConfigHolder* _localConfigHolder;
};
