#include "CardopolyEdiotr.h"
#include "GridEditor/FBuildingGridDataCustomization.h"

void CardopolyEditor::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "StartupModule");
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout("UBuildingGridData", FOnGetDetailCustomizationInstance::CreateStatic(&FBuildingGridDataCustomization::MakeInstance));

	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void CardopolyEditor::ShutdownModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.UnregisterCustomClassLayout("UBuildingGridData");
}

CardopolyEditor& CardopolyEditor::Get()
{
	return FModuleManager::LoadModuleChecked<CardopolyEditor>("CardopolyEditor");
}

IMPLEMENT_MODULE(CardopolyEditor, CardopolyEditor)
