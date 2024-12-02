#pragma once

class GridLayout;

class PositionConversionService
{
public:
	PositionConversionService(
		UWorld* viewWorld,
		GridLayout* gridLayout
		)
		: _gridLayout(gridLayout),
		_viewWorld(viewWorld)
	{}
	
	bool ScreenPointToGroundPosition(FVector2D screenPosition, FIntVector& cellPosition) const;

private:
	GridLayout* _gridLayout;
	UWorld* _viewWorld;
};
