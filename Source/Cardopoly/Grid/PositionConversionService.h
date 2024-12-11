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
	bool PositionToScreenPoint(const FVector& worldPosition, FVector2D& screenPosition) const;

private:
	GridLayout* _gridLayout;
	UWorld* _viewWorld;
};
