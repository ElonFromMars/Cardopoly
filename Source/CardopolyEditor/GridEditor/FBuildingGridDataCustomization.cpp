#include "FBuildingGridDataCustomization.h"

#include "DetailWidgetRow.h"
#include "Cardopoly/Grid/UBuildingGridData.h"
#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/Slate/Public/Widgets/Layout/SGridPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/SlateCore/Public/Input/Reply.h"
#include "Runtime/SlateCore/Public/Widgets/DeclarativeSyntaxSupport.h"

TSharedRef<IDetailCustomization> FBuildingGridDataCustomization::MakeInstance()
{
	return MakeShareable(new FBuildingGridDataCustomization);
}

void FBuildingGridDataCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "CustomizeDetails");
	
	// Get the object being customized
	TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
	DetailBuilder.GetObjectsBeingCustomized(CustomizedObjects);

	if (CustomizedObjects.Num() > 0)
	{
		if (UBuildingGridData* gridData = static_cast<UBuildingGridData*>(CustomizedObjects[0].Get()))
		{
			// Add a custom widget to display the grid
			IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Grid");
			Category.AddCustomRow(FText::FromString("Grid Editor"))
				.NameContent()
				[
					SNew(STextBlock).Text(FText::FromString("Grid Editor"))
				]
				.ValueContent()
				.MinDesiredWidth(500)
				[
					GenerateGridWidget(gridData->GridCells, gridData->Rows, gridData->Columns)
				];
		}
	}
}

TSharedRef<SWidget> FBuildingGridDataCustomization::GenerateGridWidget(TArray<bool>& GridData, int32 Rows, int32 Columns)
{
	TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel);

	// Loop through the grid and create buttons
	for (int32 Row = 0; Row < Rows; ++Row)
	{
		for (int32 Col = 0; Col < Columns; ++Col)
		{
			int32 Index = Row * Columns + Col;

			// Add a slot for each cell
			GridPanel->AddSlot(Col, Row)
			[
				SNew(SButton)
				.OnClicked_Lambda([Index, &GridData]()
				{
					// Toggle cell state
					GridData[Index] = !GridData[Index];

					// Force UI refresh
					return FReply::Handled();
				})
				.ButtonColorAndOpacity_Lambda([Index, &GridData]()
				{
					// Change color based on state
					return GridData[Index] ? FLinearColor::Green : FLinearColor::Red;
				})
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(" "))
				]
			];
		}
	}

	return GridPanel;
}