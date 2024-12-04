#pragma once

class GridLayout;
class BuildingService;
class AEntityView;
class PositionConversionService;
class GridObjectsDataProvider;
class UGameplayAssetData;

class BuildingPrototypeService
{
public:
	BuildingPrototypeService(
		UWorld* viewWorld,
		UGameplayAssetData* gameplayAssetData,
		PositionConversionService* positionConversionService,
		GridObjectsDataProvider* gridObjectsDataProvider,
		BuildingService* buildingService,
		GridLayout* gridLayout
	) :
		_viewWorld(viewWorld),
		_gameplayAssetData(gameplayAssetData),
		_positionConversionService(positionConversionService),
		_gridObjectsDataProvider(gridObjectsDataProvider),
		_buildingService(buildingService),
		_gridLayout(gridLayout)
	{}

	void ShowBuildingPrototype(const uint32 id);

	void UpdateBuildingPrototypePosition(const FVector2D screenPosition) const;

	void HideBuildingPrototype();

private:
	UWorld* _viewWorld;
	UGameplayAssetData* _gameplayAssetData;
	PositionConversionService* _positionConversionService;
	GridObjectsDataProvider* _gridObjectsDataProvider;
	BuildingService* _buildingService;
	GridLayout* _gridLayout;
	
	uint32 _prototypeId = 0;
	AEntityView* _prototypeView = nullptr;
};
