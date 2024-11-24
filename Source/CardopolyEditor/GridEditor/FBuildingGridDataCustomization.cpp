#include "FBuildingGridDataCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "Cardopoly/Grid/FBuildingGridData.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Text/STextBlock.h"

TSharedRef<IPropertyTypeCustomization> FBuildingGridDataCustomization::MakeInstance()
{
    return MakeShareable(new FBuildingGridDataCustomization);
}

void FBuildingGridDataCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    UE_LOG(LogTemp, Warning, TEXT("%hs"), "CustomizeHeader");
    
    HeaderRow.NameContent()
    [
        PropertyHandle->CreatePropertyNameWidget()
    ]
    .ValueContent()
    [
        SNew(STextBlock).Text(FText::FromString("Grid Editor"))
    ];
}

void FBuildingGridDataCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, 
                                                       IDetailChildrenBuilder& ChildBuilder, 
                                                       IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    void* RawData = nullptr;
    PropertyHandle->GetValueData(RawData);
    if (FBuildingGridData* GridData = static_cast<FBuildingGridData*>(RawData))
    {
        GridData->Rows = FMath::Clamp(GridData->Rows, 1, 100);
        GridData->Columns = FMath::Clamp(GridData->Columns, 1, 100);
        
        int64 TotalGridSize = static_cast<int64>(GridData->Rows) * static_cast<int64>(GridData->Columns);
        
        if (TotalGridSize <= 0 || TotalGridSize > 10000)
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid grid size detected: Rows=%d, Columns=%d, TotalSize=%lld"), 
                GridData->Rows, GridData->Columns, TotalGridSize);
            return;
        }
        
        if (GridData->GridCells.Num() != TotalGridSize)
        {
            GridData->GridCells.Empty();
            GridData->GridCells.AddZeroed(TotalGridSize);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Resizing GridCells to %lld elements"), TotalGridSize);

        TSharedRef<SHorizontalBox> griContainer = SNew(SHorizontalBox);

        auto rebuildGrid = [this, GridData, griContainer]()
        {
            griContainer->ClearChildren();
            griContainer->AddSlot()
            [
                GenerateGridWidget(GridData)
            ];
        };
        
        FDetailWidgetRow rowsWidget = ChildBuilder
            .AddCustomRow(FText::FromString("Rows"))
            .NameContent()
            [
                SNew(STextBlock).Text(FText::FromString("Rows"))
            ]
            .ValueContent()
            [
                SNew(SNumericEntryBox<int32>)
                .Value_Lambda([GridData]() { return GridData->Rows; })
                .OnValueChanged_Lambda([GridData, PropertyHandle, rebuildGrid](int32 NewValue)
                {
                    GridData->Rows = FMath::Clamp(NewValue, 1, 100);
                    GridData->GridCells.SetNum(GridData->Rows * GridData->Columns);
                    PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
                    rebuildGrid();
                })
            ];
        
        FDetailWidgetRow columnsWidget = ChildBuilder
            .AddCustomRow(FText::FromString("Columns"))
            .NameContent()
            [
                SNew(STextBlock).Text(FText::FromString("Columns"))
            ]
            .ValueContent()
            [
                SNew(SNumericEntryBox<int32>)
                .Value_Lambda([GridData]() { return GridData->Columns; })
                .OnValueChanged_Lambda([GridData, PropertyHandle, rebuildGrid](int32 NewValue)
                {
                    GridData->Columns = FMath::Clamp(NewValue, 1, 100);
                    GridData->GridCells.SetNum(GridData->Rows * GridData->Columns);
                    PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
                    rebuildGrid();
                })
            ];

        FDetailWidgetRow gridEditorWidget = ChildBuilder
            .AddCustomRow(FText::FromString("Grid Editor"))
            .ValueContent()
            .MinDesiredWidth(500)
            [
                griContainer
            ];
        
        rebuildGrid();
    }
}

TSharedRef<SWidget> FBuildingGridDataCustomization::GenerateGridWidget(FBuildingGridData* gridData)
{
    TArray<bool>& cells = gridData->GridCells;
    int32 Rows = gridData->Rows;
    int32 Columns = gridData->Columns;
    
    UE_LOG(LogTemp, Warning, TEXT("GenerateGridWidget: Rows=%d, Columns=%d, GridDataSize=%d"), Rows, Columns, cells.Num());

    Rows = FMath::Clamp(Rows, 1, 100);
    Columns = FMath::Clamp(Columns, 1, 100);

    int32 TotalSize = Rows * Columns;
    if (cells.Num() != TotalSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("Resizing GridData array to %d"), TotalSize);
        cells.SetNum(TotalSize);
    }

    TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel);

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col)
        {
            int32 Index = Row * Columns + Col;

            if (Index >= cells.Num())
            {
                UE_LOG(LogTemp, Error, TEXT("Index %d is out of bounds for GridData of size %d"), Index, cells.Num());
                continue;
            }

            GridPanel->AddSlot(Col, Row)
            [
                SNew(SButton)
                .OnClicked_Lambda([Index, &cells]()
                {
                    if (Index < cells.Num())
                    {
                        cells[Index] = !cells[Index];
                    }
                    return FReply::Handled();
                })
                .ButtonColorAndOpacity_Lambda([Index, &cells]()
                {
                    return (Index < cells.Num() && cells[Index]) ? FLinearColor::Green : FLinearColor::Red;
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