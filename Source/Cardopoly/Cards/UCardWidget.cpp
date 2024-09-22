#include "UCardWidget.h"

#include "Components/TextBlock.h"

void UCardWidget::SetName(const FText Name)
{
	if (CardNameText)
	{
		CardNameText->SetText(Name);
	}
}

void UCardWidget::SetDescription(const FText Description)
{
	if (CardDescriptionText)
	{
		CardDescriptionText->SetText(Description);
	}
}

void UCardWidget::SetCost(const FText& Text)
{
	
}
