#include "IncomeOverlayEffectWidget.h"

#include "FCTween.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/RichTextBlock.h"

void UIncomeOverlayEffectWidget::Construct(int32 value)
{
	FText Pattern = FText::FromString(TEXT("{0}<MoneySign>$</>"));
	FText FormattedText = FText::Format(Pattern, FText::AsNumber(value));
	Text->SetText(FormattedText);
}

void UIncomeOverlayEffectWidget::BeginAnimation()
{
	UCanvasPanelSlot* canvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	
	FVector2D startPosition = canvasSlot->GetPosition();
	_tween = FCTween::Play(0.0f, 1.0f,
		[canvasSlot, startPosition, this](float t)
		{
			FVector2D position = startPosition + FVector2D(0, -t * 100);
			canvasSlot->SetPosition(position);
		}, 1,
	EFCEase::Linear);
	
	_tween->SetOnComplete([this]()
	{
		this->RemoveFromParent();
	});
}

void UIncomeOverlayEffectWidget::BeginDestroy()
{
	if (_tween != nullptr)
	{
		_tween->Destroy();
		_tween = nullptr;
	}
	
	Super::BeginDestroy();
}