#include "UHUDWidget.h"

#include "Cardopoly/GameplayFlow/TurnController.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"

void UHUDWidget::Construct(ATurnController* turnController)
{
	TurnController = turnController;
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndTurnButton->OnClicked.AddDynamic(this, &UHUDWidget::OnEndTurnButtonClicked);
}

void UHUDWidget::OnEndTurnButtonClicked()
{
	TurnController->EndTurn(0);
}

void UHUDWidget::SetMoney(int value) const
{
	MoneyText->SetText(FText::FromString(FString::FromInt(value)));
}
