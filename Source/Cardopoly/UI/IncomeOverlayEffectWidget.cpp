#include "IncomeOverlayEffectWidget.h"

#include "FCTween.h"
#include "Components/RichTextBlock.h"

void UIncomeOverlayEffectWidget::SetIncomeValue(int32 value)
{
	FText Pattern = FText::FromString(TEXT("{0}<MoneySign>$</>"));
	FText FormattedText = FText::Format(Pattern, FText::AsNumber(value));
	Text->SetText(FormattedText);

	FCTween::
}
