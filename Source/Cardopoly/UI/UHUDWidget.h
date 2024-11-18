#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include "Blueprint/UserWidget.h"
#include "UHUDWidget.generated.h"

class ATurnController;

UCLASS()
class CARDOPOLY_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Construct(flecs::world* ecsWorld);
	
	virtual void NativeConstruct() override;

	void SetMoney(int value) const;

private:
	UFUNCTION()
	void OnEndTurnButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* MoneyText;

	UPROPERTY(meta = (BindWidget))
	class UButton* EndTurnButton;

	flecs::world* _ecsWorld;
};
