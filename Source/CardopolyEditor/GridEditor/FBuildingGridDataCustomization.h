#pragma once

#include "CoreMinimal.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"

class SWidget;

class FBuildingGridDataCustomization : public IDetailCustomization
{
public:
	
	static TSharedRef<IDetailCustomization> MakeInstance();
	
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	// Helper method to generate grid
	TSharedRef<SWidget> GenerateGridWidget(TArray<bool>& GridData, int32 Rows, int32 Columns);
};
