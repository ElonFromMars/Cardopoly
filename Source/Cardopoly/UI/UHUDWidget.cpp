#include "UHUDWidget.h"

#include "flecs.h"
#include "Cardopoly/ECS/Core/GameplayFlow/FEndTurnRequest.hpp"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"


void UHUDWidget::Construct(flecs::world* ecsWorld)
{
	_ecsWorld = ecsWorld;
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndTurnButton->OnClicked.AddDynamic(this, &UHUDWidget::OnEndTurnButtonClicked);
}

void UHUDWidget::OnEndTurnButtonClicked()
{
	_ecsWorld->entity().add<FEndTurnRequest>();
}

void UHUDWidget::SetMoney(int value) const
{
	MoneyText->SetText(FText::FromString(FString::FromInt(value)));
}
