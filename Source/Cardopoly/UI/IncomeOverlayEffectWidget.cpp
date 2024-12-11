#include "IncomeOverlayEffectWidget.h"
#include "Components/RichTextBlock.h"

void UIncomeOverlayEffectWidget::SetIncomeValue(int32 value)
{
	Text->SetText(FText::AsNumber(value));
}
