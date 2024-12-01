#pragma once

class AEntityView;
class PositionConversionService;
class UGameplayAssetData;

class BuildingPrototypeService
{
public:
	BuildingPrototypeService(
		UWorld* viewWorld,
		UGameplayAssetData* gameplayAssetData,
		PositionConversionService* positionConversionService
		)
		: _viewWorld(viewWorld),
		_gameplayAssetData(gameplayAssetData),
		_positionConversionService(positionConversionService)
	{}

	void CreateBuildingPrototype(const uint32 id) const;

private:
	UWorld* _viewWorld;
	UGameplayAssetData* _gameplayAssetData;
	PositionConversionService* _positionConversionService;

	uint32 _prototypeId = 0;
	AEntityView* _prototypeView = nullptr;
};
