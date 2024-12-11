#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IncomeOverlayEffectWidget.generated.h"


UCLASS()
class CARDOPOLY_API UIncomeOverlayEffectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetIncomeValue(int32 value);

private:
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* Text;
};
